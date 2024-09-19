#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // User inputs their Credit Card Number - CCN

    long ccn = get_long("What is your credit card number?\n");
    long number = ccn;
    long ccnsaved = ccn;
    long ccntemp = ccn;

    // Counting the digits to get a digit count

    int count = 0;
    while (number != 0)
    {
        number = number / 10;
        count++;
    }

    // Luhn's algorithm

    int current;
    int total_sum = 0;

    for (int i = 0; i < count; i++)
    {
        current = ccn % 10;
        if (i % 2 != 0)
        {
            current = current * 2;
            if (current > 9)
            {
                current = current % 10 + current / 10;
            }
        }
        total_sum = total_sum + current;
        ccn = ccn / 10;
    }

    // Finding the card type

    int first_digit;
    int second_digit;
    if (total_sum % 10 == 0)
    {
        do
        {
            ccntemp = ccntemp / 10;
        }
        while (ccntemp >= 100);

        first_digit = ccntemp / 10;
        second_digit = ccntemp % 10;

        if ((first_digit == 4) && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }

        else if ((first_digit == 5) && (second_digit >= 1) && (second_digit <= 5) && (count == 16))
        {
            printf("MASTERCARD\n");
        }

        else if ((first_digit == 3) && ((second_digit == 4) || (second_digit == 7)) &&
                 (count == 15))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}
