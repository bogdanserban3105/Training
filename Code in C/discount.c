#include<cs50.h>
#include<stdio.h>

float discounte(float regular, int discount);

int main(void)
{
    float regular = get_float("Regular Price: ");
    int discount = get_int("The discount is: ");
    float sale = discounte(regular, discount);
    printf("Sale Price: %.2f\n", sale);
}

float discounte(float regular, int discount)
{
    return regular * (100-discount)/100;
}