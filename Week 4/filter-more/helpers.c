#include "helpers.h"
#include <math.h>

typedef struct GVALUE
{
    int blue;
    int green;
    int red;
} GVALUE;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avrgvalue = round(
                (float) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avrgvalue;
            image[i][j].rgbtGreen = avrgvalue;
            image[i][j].rgbtRed = avrgvalue;
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
        for (int j = 0; j < (width / 2); j++)
        {
            temp = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height][width];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            imagecopy[x][y] = image[x][y];
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;

            int count = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (row + i >= 0 && col + j >= 0 && row + i <= (height - 1) &&
                        col + j <= (width - 1))
                    {
                        count++;

                        sumBlue = sumBlue + image[row + i][col + j].rgbtBlue;
                        sumGreen = sumGreen + image[row + i][col + j].rgbtGreen;
                        sumRed = sumRed + image[row + i][col + j].rgbtRed;
                    }
                }
            }
            imagecopy[row][col].rgbtBlue = round((float) sumBlue / count);
            imagecopy[row][col].rgbtGreen = round((float) sumGreen / count);
            imagecopy[row][col].rgbtRed = round((float) sumRed / count);
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = imagecopy[x][y];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of image
    RGBTRIPLE imagecopy[height][width];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            imagecopy[x][y] = image[x][y];
        }
    }

    // Define Gx and Gy matrices as 2D arrays
    const int GxCon[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int GyCon[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterate over the image's pixels
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Define variables and set them to 0
            GVALUE GxVal = {0, 0, 0};
            GVALUE GyVal = {0, 0, 0};

            // Iterate over 3x3 grid surrounding the pixel
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    // calculate Gx and Gy values for the pixel
                    if (row + i >= 0 && col + j >= 0 && row + i <= (height - 1) &&
                        col + j <= (width - 1))
                    {
                        GxVal.blue += image[row + i][col + j].rgbtBlue * GxCon[i + 1][j + 1];
                        GxVal.green += image[row + i][col + j].rgbtGreen * GxCon[i + 1][j + 1];
                        GxVal.red += image[row + i][col + j].rgbtRed * GxCon[i + 1][j + 1];

                        GyVal.blue += image[row + i][col + j].rgbtBlue * GyCon[i + 1][j + 1];
                        GyVal.green += image[row + i][col + j].rgbtGreen * GyCon[i + 1][j + 1];
                        GyVal.red += image[row + i][col + j].rgbtRed * GyCon[i + 1][j + 1];
                    }
                }
            }

            imagecopy[row][col].rgbtBlue =
                fmin(255, round((float) sqrt(pow(GxVal.blue, 2) + pow(GyVal.blue, 2))));
            imagecopy[row][col].rgbtGreen =
                fmin(255, round((float) sqrt(pow(GxVal.green, 2) + pow(GyVal.green, 2))));
            imagecopy[row][col].rgbtRed =
                fmin(255, round((float) sqrt(pow(GxVal.red, 2) + pow(GyVal.red, 2))));
        }
    }

    // Rewrite the original image file with the imagecopy data
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = imagecopy[x][y];
        }
    }
    return;
}
