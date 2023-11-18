#include <cs50.h>
#include <stdio.h>
#include <math.h>

int lenght(long card_number);
int sum(long card_number);
int brand(long card_number);

int main(void)
{
    long card_number = get_long("Number: ");
    int rest = 0;
    int hold = 0;
    int card = lenght(card_number);
    int suma = sum(card_number);
    //check if lenght and sum conditions are true
    if (card == 1 && suma == 1)
    {
        //if true print the brand
        int type = brand(card_number);
    }
    else
    {
        //else print invalid
        printf("INVALID\n");
    }


}

int lenght(long int card_number)
{
    //card lenght
    int i = 1;
    long x = card_number;
    while (x > 9)
    {
        //removes a digit from the card number everytime it loops and counter it with i
        i += 1;
        x = x / 10;
    }

    if (i < 13 || i > 16)
    {
        return 0;
    }
    //return 1 or 0 , true or false
    else
    {
        return 1;
    }
}

int sum(long card_number)
{
    int n = 0;
    int save, save1, save2;
    int even = 0;
    int odd = 0;
    long num = card_number;

    while (num)
    {
        //i saved the the last digit of number
        save = num % 10;
        n++;
        // i deleted the last digit of number
        num = num / 10;
        //i check if the digit its in the even sport
        if (n % 2 == 0)
        {
            //if the number has double digits i sum them
            save1 = save * 2;
            while (save1 > 9)
            {
                save1 = save1 / 10 + save1 % 10;
            }
            even += save1;
        }
        else
        {
            //for odd number we dont double them
            save2 = save;
            odd += save2;
        }
        //sum the even and odd numbers in save
    }
    save = even + odd;

    return (save % 10) == 0;
}

int brand(long card_number)
{
    //all the if below compare the first digits of the number with the wanted values but multiplied by 10 at the power of the digit place
    if ((card_number >= 34 * pow(10, 13) && card_number < 35 * pow(10, 13)) || (card_number >= 37 * pow(10, 13)
            && card_number < 38 * pow(10, 13)))
    {
        return printf("AMEX\n");
    }
    //all the else if below compare the first digits of the number
    else if ((card_number >= 51 * pow(10, 14) && card_number < 56 * pow(10, 14)))
    {
        return printf("MASTERCARD\n");
    }
    else if ((card_number >= 4 * pow(10, 12) && card_number < 5 * pow(10, 12)) || (card_number >= 4 * pow(10, 15)
             && card_number < 5 * pow(10, 15)))
    {
        return printf("VISA\n");
    }
    else
    {
        return printf("INVALID\n");
    }
}
