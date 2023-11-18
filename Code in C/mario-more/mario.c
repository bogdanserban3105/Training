#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);
//i trece prin coloane
    for (int i = 0; i < n; i++)
    {
        // j trece prin randuri
        //trebuie sa printez n-i randuri cu ' ' si i cu '#'
        for (int j = 0; j < n * 2 + 2; j++)
        {
            //if(j>n-i-1) conditie partea dreapta
            //if(j<n-i-1) conditie zerouri stanga
            if (j < n - i - 1)
            {
                printf(" ");
            }
            else if (j == n)
            {
                printf(" ");
            }
            else if (j == n + 1)
            {
                printf(" ");
            }
            else
            {
                if (j < n + i + 3)
                {
                    printf("#");
                }
            }
        }
        printf("\n");
    }
}