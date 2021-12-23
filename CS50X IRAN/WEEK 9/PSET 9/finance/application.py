import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    saham = db.execute(
        "SELECT symbol , name , price ,SUM ( shares) as totalShares FROM tarakoneshha WHERE user_id=? GROUP BY symbol",user_id)

    naghdi = db.execute("SELECT cash  FROM users WHERE id = ? ", user_id)

    naghdi = naghdi[0]['cash']

    total = naghdi

    for stock in saham:
        total += stock["price"] * stock["totalShares"]

    return render_template("index.html",saham=saham,naghdi=naghdi,usd=usd,total=total)




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        getsymbol = lookup(symbol)

        if not symbol:
            return apology("Enter Name of Symbol")
        if not getsymbol:
            return apology("Invalid symbol!")
        try:
            shares = int (request.form.get("shares"))
        except:
            return apology("Enter Number of shares ")

        if shares <= 0:
            return apology("shares must be more than zero ")

        user_id = session["user_id"]
        naghdi = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        naghdi = naghdi[0]['cash']
        field_name = getsymbol["name"]
        field_price = getsymbol["price"]
        total_price = field_price * shares

        if naghdi < total_price:
            return apology(" Not enough money")

        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", naghdi - total_price, user_id)

            db.execute("INSERT INTO tarakoneshha (user_id,name,shares,price,type,symbol) VALUES ( ?,?,?,?,?,?)",

                        user_id, field_name, shares, field_price, 'buy', symbol)
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    tarakonesh = db.execute("SELECT type,symbol,price,shares,time FROM tarakoneshha WHERE user_id=?", user_id)

    return render_template("history.html", tarakonesh=tarakonesh, usd=usd)


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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Enter A Symbol Please")

        getdata = lookup(symbol)

        if not getdata:
            return apology("invalid symbol ! ")

        return render_template("quoted.html", getdata=getdata, usd_routin=usd)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology(" Please Enter Username")

        elif not password:
            return apology("Please Enter Password")

        elif not confirmation:
            return apology("Please Enter confirmation password")

        if password != confirmation:
            return apology("Password Not Matched")

        hashconv = generate_password_hash(password)
       # Insert username into database
        try:
            id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", username, hashconv)
            return redirect("/")
        except:
            return apology("username already exists")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares <= 0:
            return apology("share must be more  than zero  !")

        field_price = lookup(symbol)["price"]
        field_name = lookup(symbol)["name"]
        sumprice = shares * field_price
        my_shares = db.execute("SELECT shares FROM tarakoneshha WHERE user_id=? AND symbol = ? GROUP BY symbol ", user_id, symbol)[
            0]["shares"]

        if my_shares < shares:
            return apology("you dont have enough shares for selling")
        naghdi_jari = db.execute("SELECT cash FROM users WHERE id = ? ", user_id)[0]["cash"]

        db.execute("UPDATE users SET cash=? WHERE id=?", naghdi_jari + sumprice, user_id)

        db.execute("INSERT INTO tarakoneshha (user_id , name      , shares  , price      , type   , symbol) VALUES ( ?,?,?,?,?,?)",
                   user_id, field_name, -shares, field_price, "sell", symbol)
        return redirect("/")

    else:
        user_id = session["user_id"]
        symbols = db.execute("SELECT symbol FROM  tarakoneshha WHERE user_id =? GROUP BY symbol ", user_id)
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
