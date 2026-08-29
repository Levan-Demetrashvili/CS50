#include "helpers.h"
#include <math.h>
#include <stdio.h>

const int MAX_VALUE = 255;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round(
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tmpBlue = image[i][j].rgbtBlue;
            int tmpGreen = image[i][j].rgbtGreen;
            int tmpRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtBlue = tmpBlue;
            image[i][width - 1 - j].rgbtGreen = tmpGreen;
            image[i][width - 1 - j].rgbtRed = tmpRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_original[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_original[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_original[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumBlue = 0, sumGreen = 0;
            int box_count = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                if (k < 0 || k > height - 1)
                {
                    continue;
                }
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (l < 0 || l > width - 1)
                    {
                        continue;
                    }
                    sumRed += image_original[k][l].rgbtRed;
                    sumGreen += image_original[k][l].rgbtGreen;
                    sumBlue += image_original[k][l].rgbtBlue;
                    box_count++;
                }
            }

            int avgBlue = round(sumBlue / (float) box_count);
            int avgGreen = round(sumGreen / (float) box_count);
            int avgRed = round(sumRed / (float) box_count);

            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_bordered[height][width];
    int Gx_table[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy_table[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_bordered[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_bordered[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_bordered[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxRed = 0, GxBlue = 0, GxGreen = 0;
            int GyRed = 0, GyBlue = 0, GyGreen = 0;
            int box_count = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                // check if k(height) is out of the border
                if (k < 0 || k > height - 1)
                {
                    box_count += 3;
                    continue;
                }
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // Check if l(width) is out of the border
                    if (l < 0 || l > width - 1)
                    {
                        box_count++;
                        continue;
                    }

                    // Calculate Gx
                    GxRed += Gx_table[box_count] * image_bordered[k][l].rgbtRed;
                    GxGreen += Gx_table[box_count] * image_bordered[k][l].rgbtGreen;
                    GxBlue += Gx_table[box_count] * image_bordered[k][l].rgbtBlue;
                    // Calculate Gy
                    GyRed += Gy_table[box_count] * image_bordered[k][l].rgbtRed;
                    GyGreen += Gy_table[box_count] * image_bordered[k][l].rgbtGreen;
                    GyBlue += Gy_table[box_count] * image_bordered[k][l].rgbtBlue;
                    // printf("box: %i gy: %i\n", box_count,Gy_table[box_count]);
                    box_count++;
                }
            }

            image[i][j].rgbtBlue = ((int) round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)))) > MAX_VALUE
                                       ? MAX_VALUE
                                       : (int) round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            image[i][j].rgbtGreen =
                ((int) round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)))) > MAX_VALUE
                    ? MAX_VALUE
                    : (int) round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            image[i][j].rgbtRed = ((int) round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)))) > MAX_VALUE
                                      ? MAX_VALUE
                                      : (int) round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
        }
    }

    return;
}
