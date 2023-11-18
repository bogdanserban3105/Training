#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = get_string("Name: ");

    int i = strlen(name);
    printf("%i\n ", i);
} 