#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = get_int("Number of grades: ");
    int scores[n];
    int score = 0;
    for( int i = 0;i<n;i++)
    {
        scores[i] = get_int("Your grade is: ");
        score += scores[i];
    }
    printf("Your average score is: %f\n", score/ (float)n);
}