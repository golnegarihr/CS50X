#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// this project cipher a text
// hash a text by caesar algorythm
// first u send 2 arguman
// then check if were ok then get your text
// finaly acoording to your key and text
// produce cipher text and show
// ci = (pi + k) % 26    PI=CHAR FOR SIPHERING & K = KEY
// program
int main(int argc, string argv[])
{
// check arguman
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string key = argv[1];

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isalpha((char)key[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int keyint =  atoi(key);

    if (keyint < 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


// get text

    string text = get_string("plaintext : ");

    char lowtbl[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    char uptbl[]  = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    int sipherrow = 0 ;
    int textrow = 0 ;
    char chipher[strlen(text)];
    char ch = ' ';
    bool figure = false;

// clear memory
    for (int i = 0, n1 = strlen(chipher); i < n1 ; i++)
    {
        chipher[i] = 0;
    }


// run and compute cipher text

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        ch = text[i];

        for (int j = 0  ; j < 26; j++)
        {
            if (ch == lowtbl[j] ||  ch == uptbl[j])
            {
                break;

            }
            else if (ch == '!' || ch == ' ' || ch == ',')
            {
                figure = true;
                break;
            }
            else
            {
                textrow++;
            }
        }
        if (figure == false)
        {
            sipherrow = (textrow + keyint) % 26 ;
            textrow = 0 ;

            if (islower(ch))

            {
                chipher[i] = lowtbl[sipherrow] ;
            }

            else

            {
                chipher[i] = uptbl[sipherrow] ;

            }

        }

        else
        {
            chipher[i] = ch;
            figure = false;
        }

        sipherrow = 0 ;

    }


    printf("ciphertext: ");
    for (int i = 0,  n = strlen(chipher); i < n ; i++)
    {
        printf("%c", chipher[i]);

    }
    printf("\n");

}