import csv
import sys
from sys import argv
import re

# this pprogram find DNA of person according to thier dayabase
# first of all , get name of database and file for check match bettween together
# if find matches so, show their name and not fine show No match


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")


dbs = []
csvname = argv[1]

with open(argv[1], 'r') as csvfile:
    getfile = csv.DictReader(csvfile)

    if (csvname == "databases/small.csv"):
        csvname = "small"
        for row in getfile:
            # copy row selected from csvfile to a dicttionary as name is  smallcsv
            # for example {name:Alice, AGATC:2,AATG:8,TATC:3}
            smallcsv = row
            smallcsv["AGATC"] = int(smallcsv["AGATC"])
            smallcsv["AATG"] = int(smallcsv["AATG"])
            smallcsv["TATC"] = int(smallcsv["TATC"])
            # add a member of dict to a list[]
            dbs.append(smallcsv)

    else:
        csvname = "large"
        for row in getfile:
            # copy row selected from csvfile to a dicttionary as name is  bigcsv
            bigcsv = row
            bigcsv["AGATC"] = int(bigcsv["AGATC"])
            bigcsv["TTTTTTCT"] = int(bigcsv["TTTTTTCT"])
            bigcsv["AATG"] = int(bigcsv["AATG"])
            bigcsv["TCTAG"] = int(bigcsv["TCTAG"])
            bigcsv["GATA"] = int(bigcsv["GATA"])
            bigcsv["TATC"] = int(bigcsv["TATC"])
            bigcsv["GAAA"] = int(bigcsv["GAAA"])
            bigcsv["TCTG"] = int(bigcsv["TCTG"])
            # add a member of dict to a list[]
            dbs.append(bigcsv)


lines = []
# open sample file for find person
with open(argv[2]) as csvfile:
    lines = csvfile.read()

if (csvname == "small"):
    # count any parameter of DNA in small database

    substr = "TATC"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    TATC = int((len(findmaxstr) / len(substr)))

    substr = "AATG"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    AATG = int((len(findmaxstr) / len(substr)))

    substr = "AGATC"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    AGATC = int((len(findmaxstr) / len(substr)))

else:
    # count any parameter of DNA in large database

    substr = "AGATC"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    AGATC = int((len(findmaxstr) / len(substr)))

    substr = "TTTTTTCT"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    TTTTTTCT = int((len(findmaxstr) / len(substr)))

    substr = "AATG"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    AATG = int((len(findmaxstr) / len(substr)))

    substr = "TCTAG"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    TCTAG = int((len(findmaxstr) / len(substr)))

    substr = "GATA"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    GATA = int((len(findmaxstr) / len(substr)))

    substr = "TATC"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    TATC = int((len(findmaxstr) / len(substr)))

    substr = "GAAA"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    GAAA = int((len(findmaxstr) / len(substr)))

    substr = "TCTG"
    findmaxstr = max(re.findall('((?:' + re.escape(substr) + ')*)', lines), key=len)
    TCTG = int((len(findmaxstr) / len(substr)))


notmatch = True
# check number of parameter of DNa and find person from small database

if (csvname == "small"):
    for j in range(len(dbs)):
        check = dbs[j]
        if (check['AGATC'] == AGATC and check['AATG'] == AATG and check['TATC'] == TATC):
            print(check['name'])
            notmatch = False

else:
    # check number of parameter of DNa and find person from large database

    for k in range(len(dbs)):
        check = dbs[k]

        if (check['AGATC'] == AGATC and check['TTTTTTCT'] == TTTTTTCT and check['AATG'] == AATG and check['TCTAG'] == TCTAG):
            if (check['GATA'] == GATA and check['TATC'] == TATC and check['GAAA'] == GAAA and check['TCTG'] == TCTG):
                print(check['name'])
                notmatch = False

if (notmatch == True):
    print("No match")

if __name__ == "__main__":
    main()