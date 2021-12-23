#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t  block[512] ;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    // if u enter more than 2 parameter , show u  fail and correct format
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Open RAW file and checking state
    FILE *readfile = fopen(argv[1], "r");
    if (readfile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
// create 2 variables for counting of picture and made file names
    int counter = 0 ;
    char filename[13] ;
// made a file with save name and dont have any things inside it
// becuase u can control in any condition for instance if
    FILE *save = NULL ;

//  run program for reading file and then copy each jpeg file into seprated file
    while (fread(&block, 1, 512, readfile))
    {

        if (block[0] == 0xff &&  block[1] == 0xd8 &&  block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {


            sprintf(filename, "%03i.jpg", counter);
            save = fopen(filename, "w");
            counter++;
        }

        if (save != NULL)
        {

            fwrite(&block, 1, 512, save) ;
        }

    }
    fclose(readfile);
    fclose(save);

}