#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// ci = (pi + k) % 26    PI=CHAR FOR SIPHERING & K = KEY
   int main(void )
{
     // compute
    char lowtbl[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    char uptbl[]  = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

   // char c = 'a' +1 ;
  //  printf ("%c\n",c);
    string text="daH";
    int keyint =2;
    float sipherrow = 0 ;
    int textrow = 0 ;
    char chipher[strlen(text)];
    char ch = ' ' ;
    char ch2 = ' ' ;
    char ch3 = ' ' ;

    sipherrow=  (textrow) +  (keyint )  %   (26) ;
    printf("%f\n",sipherrow);

    for (int i=0,n= strlen(text); i<n ; i++)

      {
            ch=text[i];
      for (int j = 0  ; j < 26; j++)
            {
                ch2=lowtbl[j];
                ch3=uptbl[j];

                  if (ch == lowtbl[j] || ch == uptbl[j]  )
                  {
                      break ;
                  }

                //  else if ( ch == uptbl[j]  )
               //   {
                //      break ;
                //  }

                  else
                  {
                      textrow++;

                  }
            }

              if (islower (ch))

             {
                   printf("%c\n",lowtbl[textrow]);
             }

             else

             {
                   printf("%c\n",uptbl[textrow]);

             }
             textrow=0;


      }


}