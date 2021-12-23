#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(int n, string namein);
void print_winner(int x);

int main(int argc, string argv[])

{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count =  argc-1 ;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0 ; i < candidate_count ; i++)
    {
        candidates[i].name = argv[i + 1];
    }


 //for (int i = 0 ; i < candidate_count ; i++)
//    {//
//         printf("%s %i\n", candidates[i].name,candidates[i].votes);
//    }


    int voter_count = get_int("Number of voters: ");

    // Loop over all voters

    for (int i = 0 ; i < voter_count; i++)
    {
       string  namein = get_string("Vote: ");


        // Check for invalid vote

          if (!vote(candidate_count,namein))
        {
            printf("Invalid vote.\n");
        }
    }


//  for (int i = 0 ; i < candidate_count ; i++)
        //{
           //printf("%s %i\n", candidates[i].name,candidates[i].votes);
//        }


    // Display winner of election
    print_winner(candidate_count);

}
// Update vote totals given a new vote
//------------------------------------------------------------------------------
bool vote(int n, string nameinn)
{

    bool check;
    int counter=0;
    // TODO

     for (int j = 0 ; j < n ; j++)
      {
                if (strcmp(candidates[j].name, nameinn  )==0)
             {
                  counter++;
                  candidates[j].votes=candidates[j].votes + counter ;
                  check = false;
                  //place =j;
                  counter=0;
                  goto s;
             }
                else
            {
                  check = true;
            }
       }
       //counter=0;

s:
        if (check)
        {
          //printf("Invalid vote.\n");
          return false;
         // check=0;
        }
  return true ;


}
//------------------------------------------------------------------------

// Print the winner (or winners) of the election

void print_winner(int x)
{
    // TODO
    int a = 0 ;
    int b = 0 ;
    int strplc1 = 0 ;
    int strplc2 = 0 ;
    int count;
    bool candid2 = false;

        a = candidates[0].votes;
    for (int i = 1 ; i < x ; i++)
    {
              b = candidates[i].votes;

         if  ( b > a  )
         {
            a = b  ;
            count = i ;
            strplc1 = i ;

         }
        else if ( b == a  )
        {
              strplc2 = i ;
              candid2=true;
        }
    }

    if (candid2 == true)
    {
            printf("%s\n",candidates[strplc1].name);
            printf("%s\n",candidates[strplc2].name);
    }
    else
    {
            printf("%s\n",candidates[strplc1].name);
    }

    return;
}

