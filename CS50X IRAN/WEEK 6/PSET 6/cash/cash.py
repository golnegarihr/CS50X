from cs50 import get_float

# cash calculate program;
# After get dollar then change to cent
# then calculate how many coins u need to pay
# and finally show the number of coins u must pay


dollar = 0
coins = 0

while (dollar <= 0):
    dollar = get_float("please enter your Dollar: ")

cents = round(dollar * 100)

while (cents >= 25):
    cents = cents - 25
    coins = coins+1

while (cents >= 10):
    cents = cents - 10
    coins = coins+1

while (cents >= 5):
    cents = cents - 5
    coins = coins+1

while (cents > 0):
    cents = cents - 1
    coins = coins+1

print(coins)
