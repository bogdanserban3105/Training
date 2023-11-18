#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float grayscale;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //greyscale its when all r g b value are equal
            //so we calculate the average
            grayscale = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0 ;
            image[i][j].rgbtBlue = round(grayscale);
            image[i][j].rgbtRed = round(grayscale);
            image[i][j].rgbtGreen = round(grayscale);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //we flip the image
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*blurred)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    RGBTRIPLE blur;
    int h = height;
    int w = width;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //check if array is in left upper corner
            if (i == 0 && j == 0)
            {
                blurred[i][j].rgbtRed = round((image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                blurred[i][j].rgbtGreen = round((image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen + image[i][j].rgbtGreen) /
                                                4.0);
                blurred[i][j].rgbtBlue = round((image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
            }
            //check if array is in right upper corner
            else if (i == 0 && j == width - 1)
            {
                blurred[i][j].rgbtRed = round((image[0][j - 1].rgbtRed + image[1][j - 1].rgbtRed + image[1][j].rgbtRed + image[i][j].rgbtRed) /
                                              4.0);
                blurred[i][j].rgbtGreen = round((image[0][j - 1].rgbtGreen + image[1][j - 1].rgbtGreen + image[1][j].rgbtGreen +
                                                 image[i][j].rgbtGreen) / 4.0);
                blurred[i][j].rgbtBlue = round((image[0][j - 1].rgbtBlue + image[1][j - 1].rgbtBlue + image[1][j].rgbtBlue + image[i][j].rgbtBlue) /
                                               4.0);

            }
            //check if array is in left lower corner
            else if (i == height - 1 && j == 0)
            {
                blurred[i][j].rgbtRed = round((image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed + image[height - 1][1].rgbtRed +
                                               image[i][j].rgbtRed) / 4.0);
                blurred[i][j].rgbtGreen = round((image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen + image[height - 1][1].rgbtGreen +
                                                 image[i][j].rgbtGreen) / 4.0);
                blurred[i][j].rgbtBlue = round((image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue + image[height - 1][1].rgbtBlue +
                                                image[i][j].rgbtBlue) / 4.0);

            }
            //check if array is in right lower corner
            else if (i == height - 1 && j == width - 1)
            {
                blurred[i][j].rgbtRed = round((image[height - 2][width - 1].rgbtRed + image[height - 2][width - 2].rgbtRed + image[height - 1][width
                                               - 2].rgbtRed + image[i][j].rgbtRed) / 4.0);
                blurred[i][j].rgbtGreen = round((image[height - 2][width - 1].rgbtGreen + image[height - 2][width - 2].rgbtGreen + image[height -
                                                 1][width - 2].rgbtGreen + image[i][j].rgbtGreen) / 4.0);
                blurred[i][j].rgbtBlue = round((image[height - 2][width - 1].rgbtBlue + image[height - 2][width - 2].rgbtBlue + image[height -
                                                1][width - 2].rgbtBlue + image[i][j].rgbtBlue) / 4.0);

            }
            // check if array its on the upper part
            else if (i == 0)
            {
                blurred[i][j].rgbtRed = round((image[0][j - 1].rgbtRed + image[1][j - 1].rgbtRed + image[1][j].rgbtRed + image[1][j + 1].rgbtRed + image[0][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0); blurred[i][j].rgbtGreen = round((image[0][j - 1].rgbtGreen + image[1][j - 1].rgbtGreen + image[1][j].rgbtGreen + image[1][j + 1].rgbtGreen + image[0][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0); blurred[i][j].rgbtBlue = round((image[0][j - 1].rgbtBlue + image[1][j - 1].rgbtBlue + image[1][j].rgbtBlue + image[1][j + 1].rgbtBlue + image[0][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);

            }
            // check if array its on left part
            else if (j == 0)
            {
                blurred[i][j].rgbtRed = round((image[i - 1][0].rgbtRed + image[i - 1][1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j +
                                               1].rgbtRed + image[i + 1][0].rgbtRed + image[i][j].rgbtRed) / 6.0);
                blurred[i][j].rgbtGreen = round((image[i - 1][0].rgbtGreen + image[i - 1][1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j
                                                 + 1].rgbtGreen + image[i + 1][0].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
                blurred[i][j].rgbtBlue = round((image[i - 1][0].rgbtBlue + image[i - 1][1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j +
                                                1].rgbtBlue + image[i + 1][0].rgbtBlue + image[i][j].rgbtBlue) / 6.0);

            }
            // check if array its on the lower part
            else if (i == h - 1)
            {
                blurred[i][j].rgbtRed = round((image[h - 1][j - 1].rgbtRed + image[h - 2][j - 1].rgbtRed + image[h - 2][j].rgbtRed + image[h - 2][j
                                               + 1].rgbtRed + image[h - 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                blurred[i][j].rgbtGreen = round((image[h - 1][j - 1].rgbtGreen + image[h - 2][j - 1].rgbtGreen + image[h - 2][j].rgbtGreen + image[h
                                                 - 2][j + 1].rgbtGreen + image[h - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
                blurred[i][j].rgbtBlue = round((image[h - 1][j - 1].rgbtBlue + image[h - 2][j - 1].rgbtBlue + image[h - 2][j].rgbtBlue + image[h -
                                                2][j + 1].rgbtBlue + image[h - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);

            }
            //check if array its on right part
            else if (j == w - 1)
            {
                blurred[i][j].rgbtRed = round((image[i - 1][w - 1].rgbtRed + image[i - 1][w - 2].rgbtRed + image[i][w - 2].rgbtRed + image[i + 1][w
                                               - 2].rgbtRed + image[i + 1][w - 1].rgbtRed + image[i][j].rgbtRed) / 6.0);
                blurred[i][j].rgbtGreen = round((image[i - 1][w - 1].rgbtGreen + image[i - 1][w - 2].rgbtGreen + image[i][w - 2].rgbtGreen + image[i
                                                 + 1][w - 2].rgbtGreen + image[i + 1][w - 1].rgbtGreen + image[i][j].rgbtGreen) / 6.0);
                blurred[i][j].rgbtBlue = round((image[i - 1][w - 1].rgbtBlue + image[i - 1][w - 2].rgbtBlue + image[i][w - 2].rgbtBlue + image[i +
                                                1][w - 2].rgbtBlue + image[i + 1][w - 1].rgbtBlue + image[i][j].rgbtBlue) / 6.0);

            }
            else
            {
                blurred[i][j].rgbtRed = round((image[i  -  1][j  -  1].rgbtRed + image[i  -  1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                               image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j +
                                                       1].rgbtRed + image[i][j].rgbtRed) / 9.0);
                blurred[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen  +
                                                 image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                                 image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 9.0);
                blurred[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                                image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                                image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 9.0);

            }
        }
    }
    //return the modified image to the first one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred[i][j];
        }
    }
    free(blurred);
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edgy[height][width];
    int h = height;
    int w = width;
    //create a copy of the image for it to be procesed, so the original image its not poluted
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            edgy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_rgbtRed = 0;
            int Gx_rgbtGreen = 0;
            int Gx_rgbtBlue = 0;
            int Gy_rgbtRed = 0;
            int Gy_rgbtGreen = 0;
            int Gy_rgbtBlue = 0;
            for (int n = 0; n < 3; n++)
            {
                for (int m = 0; m < 3; m++)
                {

                    int GX[3][3] =
                    {
                        { -  1, 0, 1},
                        { -  2, 0, 2},
                        { -  1, 0, 1},
                    };
                    int GY[3][3] =
                    {
                        { -  1,  -  2,  -  1},
                        {0,   0,  0},
                        {1,   2,  1},
                    };
                    int position_i[3] = {i  -  1, i, i + 1};
                    int position_j[3] = {j - 1, j, j + 1};

                    int pn = position_i[n];
                    int pm = position_j[m];
                    //check if array is in left upper corner
                    if (i == 0 && j == 0)
                    {
                        GX[0][0] = GY[0][0] = 0;
                        GX[0][1] = GY[0][1] = 0;
                        GX[1][0] = GY[1][0] = 0;
                        GX[2][0] = GY[2][0] = 0;
                        GX[0][2] = GY[0][2] = 0;
                    }
                    //check if array is in right upper corner
                    else if (i == 0 && j == width - 1)
                    {
                        GX[0][1] = GY[0][1] = 0;
                        GX[1][2] = GY[1][2] = 0;
                        GX[0][2] = GY[0][2] = 0;
                        GX[0][0] = GY[0][0] = 0;
                        GX[2][2] = GY[2][2] = 0;
                    }
                    //check if array is in left lower corner
                    else if (i == height - 1 && j == 0)
                    {
                        GX[1][0] = GY[1][0] = 0;
                        GX[2][0] = GY[2][0] = 0;
                        GX[2][1] = GY[2][1] = 0;
                        GX[0][0] = GY[0][0] = 0;
                        GX[2][2] = GY[2][2] = 0;
                    }
                    //check if array is in right lower corner
                    else if (i == height - 1 && j == width - 1)
                    {
                        GX[0][2] = GY[0][2] = 0;
                        GX[1][2] = GY[1][2] = 0;
                        GX[2][2] = GY[2][2] = 0;
                        GX[2][1] = GY[2][1] = 0;
                        GX[2][0] = GY[2][0] = 0;
                    }
                    //array up
                    else if (i == 0)
                    {
                        GX[0][0] = GY[0][0] = 0;
                        GX[0][1] = GY[0][1] = 0;
                        GX[0][2] = GY[0][2] = 0;
                    }
                    //array right
                    else if (j == 0)
                    {
                        GX[0][0] = GY[0][0] = 0;
                        GX[1][0] = GY[1][0] = 0;
                        GX[2][0] = GY[2][0] = 0;
                    }
                    //array down
                    else if (i == h - 1)
                    {
                        GX[2][0] = GY[2][0] = 0;
                        GX[2][1] = GY[2][1] = 0;
                        GX[2][2] = GY[2][2] = 0;
                    }
                    //array left
                    else if (j == w - 1)
                    {
                        GX[0][2] = GY[0][2] = 0;
                        GX[1][2] = GY[1][2] = 0;
                        GX[2][2] = GY[2][2] = 0;
                    }
                    //for the gx matrix, multiply with edge array
                    Gx_rgbtRed += GX[n][m] * edgy[pn][pm].rgbtRed;
                    Gx_rgbtGreen += GX[n][m] * edgy[pn][pm].rgbtGreen;
                    Gx_rgbtBlue += GX[n][m] * edgy[pn][pm].rgbtBlue;
                    //for the gy matrix, multiply with edge array
                    Gy_rgbtRed += GY[n][m] * edgy[pn][pm].rgbtRed;
                    Gy_rgbtGreen += GY[n][m] * edgy[pn][pm].rgbtGreen;
                    Gy_rgbtBlue += GY[n][m] * edgy[pn][pm].rgbtBlue;

                }
            }
            //calculate the rounded value of square root
            //of gx^2 + gy^2
            int red =   round(sqrt((Gx_rgbtRed * Gx_rgbtRed) + (Gy_rgbtRed *  Gy_rgbtRed)));
            int green = round(sqrt((Gx_rgbtGreen * Gx_rgbtGreen) + (Gy_rgbtGreen * Gy_rgbtGreen)));
            int blue =  round(sqrt((Gx_rgbtBlue * Gx_rgbtBlue) + (Gy_rgbtBlue * Gy_rgbtBlue)));
            //return value calculated above to the image
            //only if the value its lower than 255
            image[i][j].rgbtRed = (red > 255) ? 255 : red;
            image[i][j].rgbtGreen = (green > 255) ? 255 : green;
            image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    return;
}

