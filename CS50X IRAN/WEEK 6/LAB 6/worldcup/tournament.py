# Simulate a sports tournament

import csv
import sys
from sys import argv
import random

# this program simulate a world cup tournament by get file that
# contain a team by rating in the world
# finally show each that how much may be have chance to win
# Number of simluations to run

N = 1000


def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []

    # TODO: Read teams into memory from file
    with open(argv[1]) as csvfile:
        getfile = csv.DictReader(csvfile)
        for row in getfile:
            # copy row selected from csvfile to a dicttionary as name is  team
            # for example {'team':hungray,'rating':976}

            team = row
            team["rating"] = int(team["rating"])
            # add a member of dict to a list[]
            teams.append(team)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # until n times  run do loop and check condition
    for gozero in range(N):
        # get winner team by runing  simulate_tournament function

        winner = simulate_tournament(teams)

        if winner in counts:
            # then check and add x times winning  to specific team
            counts[winner] = counts[winner] + 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # Get teams remaining and then check for runing simulate tournament

    getrounds = len(teams)
    # this is a recurion function so runing until condition rounds==1

    if getrounds == 1:

        return teams[0]['team']
    else:
        teams = simulate_round(teams)

        return simulate_tournament(teams)


if __name__ == "__main__":
    main()
