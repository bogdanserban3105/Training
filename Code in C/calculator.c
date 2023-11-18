#include<cs50.h>
#include<stdio.h>

int main(void)
{
    int number = get_int("The number is: ");
    if (number%2==0)
    {
        printf("The number its even.\n");
    }
    else
    {
        printf("The number its odd.\n");
    }
}