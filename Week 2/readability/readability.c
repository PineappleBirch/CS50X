#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int lettercount;
    int wordcount;
    int sentencecount;
} Count;

Count count(string a);

int main(void)
{
    string input = get_string("What is your input? ");

    Count myCount = count(input);

    float lvalue = ((float) myCount.lettercount / myCount.wordcount) * 100;
    float svalue = ((float) myCount.sentencecount / myCount.wordcount) * 100;

    int index = round((0.0588 * lvalue - 0.296 * svalue - 15.8));

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }
}

Count count(string a)
{
    Count counts = {0, 1, 0};
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (isalpha(a[i]))
        {
            counts.lettercount++;
        }
        else if (isspace(a[i]))
        {
            counts.wordcount++;
        }
        else if (a[i] == '.' || a[i] == '!' || a[i] == '?')
        {
            counts.sentencecount++;
        }
    }
    return counts;
}
