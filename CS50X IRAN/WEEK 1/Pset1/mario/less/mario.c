#include <cs50.h>
#include <stdio.h>

// First get height and then check number so, if was not between 1 and 8  then repet  this step ;
// then show the sharp sing and space according to number of height ;
//
// for instance if get 4 height show this result:
// #
// ##
// ###
// ####

int main(void)
{
    int height;

    do

    {
        height = get_int("enter height  Size : ");

    }
    while (height <= 0 || height > 8);

    int dot = 0;
    int sharp = 0;
    dot = height - 1;
    sharp = height - dot ;


    dot = height - 1;
    sharp = height - dot ;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < dot ; j++)
        {
            printf(" ");

        }
        for (int k = 0; k < sharp ; k++)
        {
            printf("#");
        }
        printf("\n");
        sharp += 1 ;
        dot -= 1 ;
    }

}