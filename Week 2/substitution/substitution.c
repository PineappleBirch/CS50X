#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Checking to ensure the user typed in their KEY
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    // Storing KEY inside a variable
    string KEY = argv[1];

    // Storing KEY in all lowercase inside a variable
    string lowerkey = malloc(strlen(KEY) + 1);
    for (int i = 0; i < strlen(KEY); i++)
    {
        lowerkey[i] = tolower(KEY[i]);
    }

    // Checking if the KEY contains the appropriate amount of characters
    if (strlen(argv[1]) != 26)
    {
        printf("The KEY must contain 26 characters\n");
        return 1;
    }

    // Checking if the KEY contains only alphabetical characters
    for (int i = 0, len = strlen(argv[1]); len > i; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("The key must only contain alphabetical characters\n");
            return 1;
        }
    }

    // Checking if the KEY contains no duplicate characters
    for (int i = 0, len = strlen(lowerkey); len > i; i++)
    {
        for (int j = i + 1; len > j; j++)
        {
            if (lowerkey[i] == lowerkey[j])
            {
                printf("The key must not contain duplicate characters.\n");
                return 1;
            }
        }
    }

    // Getting user input stored in "plaintext" variable
    string plaintext = get_string("plaintext: ");

    // Defining "ciphertext" variable
    string ciphertext = malloc(strlen(plaintext) + 1);

    // Ciphering the input
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(lowerkey[plaintext[i] - 'A']);
            }

            else
            {
                ciphertext[i] = lowerkey[plaintext[i] - 'a'];
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // Freeing memory stored in lowerkey
    free(lowerkey);

    // Printing the ciphered output
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
