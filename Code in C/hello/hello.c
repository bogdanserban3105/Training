#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //The string prints a message before being inputed at the keyboard
    string name = get_string("What is your name?\n ");
    //The %s\n allows a string to be printed along with the message "hello, "
    printf("hello, %s\n", name);
}