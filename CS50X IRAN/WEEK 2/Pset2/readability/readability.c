#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// this program detect difficulty of sentence
// compute number of letters , words  and sentences .
// then according to formula find grade of difficulty
// finally show correct grade

int main(void)
{
    // Get input sample
    string sample = get_string("Please type your Text : ");


    // TODO: compute Grade
    float letter = 0;
    float word = 0;
    float sentence = 0;
    float letter2 = 0;
    float sentence2 = 0;
    int grade = 0;

    for (int i = 0, n = strlen(sample); i < n; i++)
    {

        if (sample[i] == '.' || sample[i] == '!' || sample[i] == '?')

        {
            sentence++;

        }
        else if (sample[i] == ' ')

        {
            word++;

        }

        else if (sample[i] == '-'  || sample[i] == ',' || sample[i] == 39 ||  sample[i] == 34) //  - ,  , , ' , " , `

        {

            grade++;
        }

        else

        {
            letter++;
        }
    }

    grade = 0 ;
    letter2 = (letter * 100) / word;
    sentence2 = (sentence * 100) / word;
    grade  = round(0.0588 * letter2 - 0.296 * sentence2 - 15.8);

    if (grade < 1)

    {
        printf("Before Grade 1\n") ;
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("%s%i\n", "Grade ", grade);
    }

}