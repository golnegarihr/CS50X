#include "helpers.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
// Convert image to grayscale
// image[0].rgbtBlue
// image[0].rgbtGreen
// image[0].rgbtRed
void swap(int *a, int *b);

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int blue ;
    int green ;
    int red ;
    float calc = 0.0;
    int output;

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            blue =     image[i][j].rgbtBlue;
            green =    image[i][j].rgbtGreen;
            red =      image[i][j].rgbtRed;
            calc = (blue + green + red) / (float) 3 ;
            output =  round(calc) ;
            image[i][j].rgbtBlue =  output ;
            image[i][j].rgbtGreen = output ;
            image[i][j].rgbtRed =   output ;
        }
    }
    return;
}

// Convert image to sepia
// sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
//sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
//sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int blue ;
    int green ;
    int red ;
    float sepiaBlue ;
    float sepiaGreen ;
    float sepiaRed ;

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            blue =     image[i][j].rgbtBlue;
            green =    image[i][j].rgbtGreen;
            red =      image[i][j].rgbtRed;
            sepiaBlue   = (0.272 * red) + (0.534 * green) + (0.131 * blue) ;
            sepiaRed    = (0.393 * red) + (0.769 * green) + (0.189 * blue) ;
            sepiaGreen  = (0.349 * red) + (0.686 * green) + (0.168 * blue) ;

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255 ;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255 ;
            }

            if (sepiaRed > 255)
            {
                sepiaRed = 255 ;
            }

            blue  = round(sepiaBlue)  ;
            green = round(sepiaGreen) ;
            red   = round(sepiaRed)   ;

            image[i][j].rgbtBlue =  blue ;
            image[i][j].rgbtGreen = green ;
            image[i][j].rgbtRed =   red ;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int bluest  ;
    int greenst ;
    int redst   ;

    int blueend  ;
    int greenend ;
    int redend   ;
    int temp = width;

    //width = width / 2;
    //  int endw = abs (1-width);

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            bluest =     image[i][j].rgbtBlue;
            greenst =    image[i][j].rgbtGreen;
            redst =      image[i][j].rgbtRed;

            blueend =     image[i][width - 1].rgbtBlue;
            greenend =    image[i][width - 1].rgbtGreen;
            redend =      image[i][width - 1].rgbtRed;

            swap(&bluest, &blueend);
            swap(&greenst, &greenend);
            swap(&redst, &redend);

            image[i][j].rgbtBlue =  bluest ;
            image[i][j].rgbtGreen = greenst ;
            image[i][j].rgbtRed =   redst ;

            image[i][width - 1].rgbtBlue =  blueend ;
            image[i][width - 1].rgbtGreen = greenend ;
            image[i][width - 1].rgbtRed =   redend ;

            width--;
        }
        width = temp;
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int bluecntr  ;
    int greencntr ;
    int redcntr   ;

    int tmpheight = height ;
    int tmpwidth = width ;

//   0,0
//      bluecntr  =  (image[0][0].rgbtBlue   + image[0][1].rgbtBlue   +image[1][0].rgbtBlue  + image[1][1].rgbtBlue )   / 4.0 ;
//      greencntr =  (image[0][0].rgbtGreen  + image[0][1].rgbtGreen  +image[1][0].rgbtGreen + image[1][1].rgbtGreen)  / 4.0 ;
//      redcntr   =  (image[0][0].rgbtRed    + image[0][1].rgbtRed    +image[1][0].rgbtRed   + image[1][1].rgbtRed)    /4.0 ;

//      image[0][0].rgbtBlue  =  round ( bluecntr )  ;
//      image[0][0].rgbtGreen =  round ( greencntr ) ;
//      image[0][0].rgbtRed   =  round ( redcntr )   ;

// // //----  0,width
//      bluecntr  = (image[0][width].rgbtBlue   + image[0][width-1].rgbtBlue  +  image[1][width].rgbtBlue   + image[1][width-1].rgbtBlue )  /4.0 ;
//      greencntr = (image[0][width].rgbtGreen  + image[0][width-1].rgbtGreen +  image[1][width].rgbtGreen  + image[1][width-1].rgbtGreen)  /4.0 ;
//      redcntr   = (image[0][width].rgbtRed    + image[0][width-1].rgbtRed   +  image[1][width].rgbtRed    + image[1][width-1].rgbtRed  )  /4.0 ;

//      image[0][width].rgbtBlue  =  round ( bluecntr )  ;
//      image[0][width].rgbtGreen =  round ( greencntr ) ;
//      image[0][width].rgbtRed   =  round ( redcntr )   ;

// // //--- height ,0
//      bluecntr  = (image[height][0].rgbtBlue   + image[height][1].rgbtBlue   + image[height-1][0].rgbtBlue  + image[height-1][1].rgbtBlue ) /4.0 ;
//      greencntr = (image[height][0].rgbtGreen  + image[height][1].rgbtGreen  + image[height-1][0].rgbtGreen + image[height-1][1].rgbtGreen) /4.0 ;
//      redcntr   = (image[height][0].rgbtRed    + image[height][1].rgbtRed    + image[height-1][0].rgbtRed   + image[height-1][1].rgbtRed  ) /4.0 ;

//      image[height][0].rgbtBlue  =  round ( bluecntr )  ;
//      image[height][0].rgbtGreen =  round ( greencntr ) ;
//      image[height][0].rgbtRed   =  round ( redcntr )   ;

// // //--- height ,width
//       bluecntr  = (image[height][width].rgbtBlue  + image[height][width-1].rgbtBlue  + image[height-1][width].rgbtBlue  + image[height-1][width-1].rgbtBlue ) /4.0 ;
//       greencntr = (image[height][width].rgbtGreen + image[height][width-1].rgbtGreen + image[height-1][width].rgbtGreen + image[height-1][width-1].rgbtGreen) /4.0 ;
//       redcntr   = (image[height][width].rgbtRed   + image[height][width-1].rgbtRed   + image[height-1][width].rgbtRed   + image[height-1][width-1].rgbtRed  ) /4.0 ;

//       image[height][width].rgbtBlue  =  round ( bluecntr )  ;
//       image[height][width].rgbtGreen =  round ( greencntr ) ;
//       image[height][width].rgbtRed   =  round ( redcntr )   ;

//      int state=1 ;

// //   state 1
    // height = tmpheight;
    // width = tmpwidth ;
    for (int i = 0 ; i < 1 ; i++)
    {
        for (int j = 1 ; j < width ; j++)
        {

            bluecntr  = (image[i][j - 1].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i][j].rgbtBlue  + image[i + 1][j - 1].rgbtBlue   +
                         image[i + 1][j].rgbtBlue +  image[i + 1][j + 1].rgbtBlue) ;
            greencntr = (image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen  +
                         image[i + 1][j].rgbtGreen +  image[i + 1][j + 1].rgbtGreen) ;
            redcntr   = (image[i][j - 1].rgbtRed   + image[i][j + 1].rgbtRed   + image[i][j].rgbtRed   + image[i + 1][j - 1].rgbtRed    +
                         image[i + 1][j].rgbtRed +  image[i + 1][j + 1].rgbtRed);

            bluecntr =   round(bluecntr / 6.0) ;
            greencntr =  round(greencntr / 6.0) ;
            redcntr =    round(redcntr / 6.0) ;

            image[i][j].rgbtBlue  = (bluecntr)  ;
            image[i][j].rgbtGreen = (greencntr) ;
            image[i][j].rgbtRed   = (redcntr)   ;
        }

    }

//   state 2
    for (int i = height ; i <= height ; i++)
    {
        for (int j = 1 ; j < width ; j++)
        {

            bluecntr  = image[i][j - 1].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i][j].rgbtBlue  + image[i + 1][j - 1].rgbtBlue   +
                        image[i + 1][j].rgbtBlue +  image[i + 1][j + 1].rgbtBlue ;
            greencntr = image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen  +
                        image[i + 1][j].rgbtGreen +  image[i + 1][j + 1].rgbtGreen ;
            redcntr   = image[i][j - 1].rgbtRed   + image[i][j + 1].rgbtRed   + image[i][j].rgbtRed   + image[i + 1][j - 1].rgbtRed    +
                        image[i + 1][j].rgbtRed +  image[i + 1][j + 1].rgbtRed ;

            bluecntr =   round(bluecntr / 6.0) ;
            greencntr =  round(greencntr / 6.0) ;
            redcntr =    round(redcntr / 6.0) ;

            image[i][j].rgbtBlue  = (bluecntr)  ;
            image[i][j].rgbtGreen = (greencntr) ;
            image[i][j].rgbtRed   = (redcntr)   ;
        }

    }

//   state 3
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < 1 ; j++)
        {

            bluecntr  = image[i][j - 1].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i][j].rgbtBlue  + image[i + 1][j - 1].rgbtBlue   +
                        image[i + 1][j].rgbtBlue +  image[i + 1][j + 1].rgbtBlue ;
            greencntr = image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen  +
                        image[i + 1][j].rgbtGreen +  image[i + 1][j + 1].rgbtGreen ;
            redcntr   = image[i][j - 1].rgbtRed   + image[i][j + 1].rgbtRed   + image[i][j].rgbtRed   + image[i + 1][j - 1].rgbtRed    +
                        image[i + 1][j].rgbtRed +  image[i + 1][j + 1 ].rgbtRed ;

            bluecntr =   round(bluecntr / 6.0) ;
            greencntr =  round(greencntr / 6.0) ;
            redcntr =    round(redcntr / 6.0) ;

            image[i][j].rgbtBlue  = (bluecntr)  ;
            image[i][j].rgbtGreen = (greencntr) ;
            image[i][j].rgbtRed   = (redcntr)   ;

        }

    }

//   state 4
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = width ; j <= width ; j++)
        {

            bluecntr  = image[i][j - 1].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i][j].rgbtBlue  + image[i + 1][j - 1].rgbtBlue   +
                        image[i + 1][j].rgbtBlue +  image[i + 1][j + 1 ].rgbtBlue ;
            greencntr = image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen  +
                        image[i + 1][j].rgbtGreen +  image[i + 1][j + 1].rgbtGreen ;
            redcntr   = image[i][j - 1].rgbtRed   + image[i][j + 1].rgbtRed   + image[i][j].rgbtRed   + image[i + 1][j - 1].rgbtRed    +
                        image[i + 1][j].rgbtRed +  image[i + 1][j + 1].rgbtRed ;

            bluecntr =   round(bluecntr / 6.0) ;
            greencntr =  round(greencntr / 6.0) ;
            redcntr =    round(redcntr / 6.0) ;

            image[i][j].rgbtBlue  = (bluecntr)  ;
            image[i][j].rgbtGreen = (greencntr) ;
            image[i][j].rgbtRed   = (redcntr)   ;

        }

    }

// final stage ----------------------------------------------------------------
    for (int k = 1 ; k < height - 1 ; k++)
    {
        for (int l = 1 ; l < width - 1 ; l++)
        {

            bluecntr  = image[k - 1][l - 1].rgbtBlue   + image[k - 1][l].rgbtBlue   + image[k - 1 ][l + 1].rgbtBlue   + image[k][l - 1].rgbtBlue
                        + image[k][l].rgbtBlue  +  image[k][l + 1].rgbtBlue  + image[k + 1][l - 1].rgbtBlue   + image[k + 1][l].rgbtBlue   +
                        image[k + 1][l + 1].rgbtBlue;
            greencntr = image[k - 1][l - 1].rgbtGreen  + image[k - 1][l].rgbtGreen  + image[k - 1][l + 1].rgbtGreen  + image[k][l - 1].rgbtGreen
                        + image[k][l].rgbtGreen +  image[k][l + 1].rgbtGreen + image[k + 1][l - 1].rgbtGreen  + image[k + 1][l].rgbtGreen  +
                        image[k + 1][l + 1].rgbtGreen;
            redcntr   = image[k - 1][l - 1].rgbtRed    + image[k - 1][l].rgbtRed    + image[k - 1][l + 1].rgbtRed    + image[k][l - 1].rgbtRed
                        + image[k][l].rgbtRed   +  image[k][l + 1].rgbtRed   + image[k + 1][l - 1].rgbtRed    + image[k + 1][l].rgbtRed    +
                        image[k + 1][l + 1].rgbtRed;

            if (bluecntr > 255)
            {
                bluecntr = 255 ;
            }

            if (greencntr > 255)
            {
                greencntr = 255 ;
            }

            if (redcntr > 255)
            {
                redcntr = 255 ;
            }

            bluecntr =   round(bluecntr / 9.0) ;
            greencntr =  round(greencntr / 9.0) ;
            redcntr =    round(redcntr / 9.0) ;

            image[k][l].rgbtBlue  = (bluecntr)  ;
            image[k][l].rgbtGreen = (greencntr) ;
            image[k][l].rgbtRed   = (redcntr)   ;

        }

    }

    return;
}
// function for swaping -----------------------------------------------------
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}