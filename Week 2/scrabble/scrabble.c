#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score(string input);

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string input1 = get_string("Player 1: ");
    string input2 = get_string("Player 2: ");

    int score1 = compute_score(input1);
    int score2 = compute_score(input2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("It's a tie!\n");
    }
}

int compute_score(string input)
{
    int score = 0;

    for (int i = 0, len = strlen(input); i < len; i++)
    {
        if (isupper(input[i]))
        {
            score += POINTS[input[i] - 'A'];
        }
        else if (islower(input[i]))
        {
            score += POINTS[input[i] - 'a'];
        }
    }

    return score;
}
