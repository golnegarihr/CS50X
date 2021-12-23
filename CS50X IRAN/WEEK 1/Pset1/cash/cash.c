#include <stdio.h>
#include <cs50.h>
#include <math.h>

// cash calculate program;
// After get dollar then change to cent
// then calculate how many coins u need to pay
// and finally show the number of coins u must pay

int main(void)

{
    float dollar ;
    int coins = 0 ;
    do
    {
        dollar = get_float("please enter your Dollar: ");

    }
    while (dollar < 0);

    int cents = round(dollar * 100);

    while (cents >= 25)
    {
        cents = cents - 25;
        coins ++ ;
    }

    while (cents >= 10)
    {
        cents = cents - 10;
        coins ++ ;
    }

    while (cents >= 5)
    {
        cents = cents - 5;
        coins ++ ;
    }

    while (cents > 0)
    {
        cents = cents - 1;
        coins ++ ;
    }

    printf("%i\n", coins);

}