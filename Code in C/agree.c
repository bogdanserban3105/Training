#include<cs50.h>
#include<stdio.h>

int main(void)
{
    char c = get_char("Do you agree? ");
    if(c == 'y' || c == 'Y')
    {
        printf("The use agreed.\n");
    }
    else if(c == 'n' || c == 'N')
    {
        printf("The use didn't agreed.\n");
    }
    else
    {
        printf("Wrong answer.\n");
    }
}