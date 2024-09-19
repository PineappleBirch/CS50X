#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Checking for correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw");
        return 1;
    }

    // Opening the memory card file & Checking if the file can be opened

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("This file cannot be opened for reading.");
        return 1;
    }

    // Creating a buffer for blocks
    uint8_t buffer[512];

    // Declaring variables
    int counter = 0;

    FILE *img = NULL;

    char filename[8];

    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", counter);

            img = fopen(filename, "w");

            counter++;
        }
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    fclose(img);
    fclose(card);
}
