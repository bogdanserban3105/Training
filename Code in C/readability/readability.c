#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text, int len);
int count_words(string text, int len);
int count_sentences(string text, int len);

int main(void)
{
    //string input for the text
    string text = get_string("Text: ");
    //get the length of the text
    int len = strlen(text);
    //loop, while there is text
    if (count_words(text, len))
    {
        // calculate the %
        float procent = count_words(text, len) / 100.0;
        // imparte la numarul de procente
        float letters = count_letters(text, len) / procent;
        //imparte la procente
        float sentences = count_sentences(text, len) / procent;
        //the ecuation of grade equivalent
        float index = 0.0588 * letters - 0.296 * sentences - 15.8;
        //round only possible with math.h
        float grade = round(index);
        //conditions for the grade output
        if (grade > 0 && grade < 16)
        {
            printf("Grade %i\n", (int)grade);
        }
        else if (grade > 16)
        {
            printf("Grade 16+\n");
        }
        else
        {
            printf("Before Grade 1\n");
        }

    }

}
//function for counting the letters
int count_letters(string text, int len)
{
    int L = 0;
    for (int i = 0 ; i < len ; i++)
    {
        //isalnum checks if the char belongs to the alphabet
        if (isalnum(text[i]))
        {
            L += 1;
        }
    }
    return L;
}
//function for counting the words
int count_words(string text, int len)
{
    int W = 1;
    for (int n = 0 ; n < len; n++)
    {
        if ((int)((char)text[n]) == 32)
        {
            W += 1;
        }
    }
    return W;
}
//function for counting the sentences
int count_sentences(string text, int len)
{
    int S = 0;
    for (int m = 0 ; m < len ; m++)
    {
        if ((int)((char)text[m]) == 46  || (int)((char)text[m]) ==  33 || (int)((char)text[m]) == 63)
        {
            S++;
        }
    }
    return S;
}
