#include <cs50.h>
#include <stdio.h>

void print_hashes(int n);
void print_spaces(int n);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0);

    for (int i = height; i > 0; i--)
    {
        print_spaces(i - 1);
        print_hashes(height - i + 1);
        printf("  ");
        print_hashes(height - i + 1);
        printf("\n");
    }
}

void print_hashes(int n)
{
    for (int j = 1; j <= n; j++)
    {
        printf("#");
    }
}

void print_spaces(int n)
{
    for (int j = n; j > 0; j--)
    {
        printf(" ");
    }
}
