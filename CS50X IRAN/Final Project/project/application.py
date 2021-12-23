import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, success

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///myproject.db")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    userid = session["user_id"]
    profile = db.execute("SELECT fname, lname, email, city, state, zipcode, tel FROM profile WHERE userid=? ", userid)
    username = db.execute("SELECT username FROM users WHERE id = ? ", userid)
    username = username[0]['username']
    return render_template("index.html", profile=profile, username=username)


@app.route("/savechange", methods=["GET", "POST"])
@login_required
def savechange():

    if request.method == "POST":

        userid = session["user_id"]
        print(userid)
        fname = request.form.get("fname")
        lname = request.form.get("lname")
        email = request.form.get("email")
        city = request.form.get("city")
        state = request.form.get("state")
        zipcode = request.form.get("zipcode")
        tel = request.form.get("tel")

        db.execute("UPDATE profile SET fname = ?, lname =? , email=?, city=?, state =?, zipcode=?, Tel=?  WHERE userid = ?",
                   fname, lname, email, city, state, zipcode, tel, userid)
        return success(" Your profile was update")

        # return redirect("/")
    else:
        return redirect("/")


@app.route("/home", methods=["GET", "POST"])
@login_required
def buy():
    return render_template("home.html")


@app.route("/info", methods=["GET", "POST"])
@login_required
def info():
    return render_template("info.html")


@app.route("/place", methods=["GET", "POST"])
@login_required
def place():
    return render_template("place.html")


@app.route("/souvenir", methods=["GET", "POST"])
@login_required
def souvenir():
    return render_template("souvenir.html")


@app.route("/contact", methods=["GET", "POST"])
@login_required
def contact():
    return render_template("contact.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/contactme", methods=["GET", "POST"])
@login_required
def contactme():
    if request.method == "POST":
        userid = session["user_id"]
        email = request.form.get("email")
        password = request.form.get("password")
        opininion = request.form.get("opininion")
        hashconv = generate_password_hash(password)
        origpass = db.execute("SELECT hash  FROM users WHERE id=? ", userid)
        origpass = origpass[0]["hash"]

        if not check_password_hash(origpass, password):
            return apology("password incorrect")

        fname = db.execute("SELECT fname  FROM profile WHERE userid=? ", userid)
        fname = fname[0]["fname"]

        lname = db.execute("SELECT lname  FROM profile WHERE userid=? ", userid)
        lname = lname[0]["lname"]

        family = fname+" "+lname

        db.execute("INSERT INTO contactme (user_id,name,email,opininion) VALUES (?,?,?,?)",
                   userid, family, email, opininion)

        return success(" Your Message was sent")

    else:
        return redirect("/contactme")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        fname = request.form.get("fname")
        lname = request.form.get("lname")
        email = request.form.get("email")
        city = request.form.get("city")
        state = request.form.get("state")
        zipcode = request.form.get("zipcode")
        tel = request.form.get("tel")

        hashconv = generate_password_hash(password)

       # Insert username into database
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashconv)

        except:
            return apology("username already exists")
        userid = db.execute("SELECT id FROM users WHERE username = ?", username)
        userid = userid[0]["id"]
        db.execute("INSERT INTO profile (userid,fname,lname,email,city,state,zipcode,tel) VALUES (?,?,?,?,?,?,?,?)",
                   userid, fname, lname, email, city, state, zipcode, tel)

        return success("your account registerd")
        # return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)