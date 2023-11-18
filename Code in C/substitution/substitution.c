#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, string argv[])
{
    //first we check if any key was introduced
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //if key was introduced we memorise it in a string, and its length in an int
    string key = argv[1];
    int length = strlen(key);
    //if there are not 26 characters in the key error
    if (length != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //2 loops for checking the elements of the key,
    //first we check if the letter is unique in key, after we check if all the characters are letters
    for (int i = 0; i < length ; i++)
    {
        for (int j = i + 1 ; j < length; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    //if all the loops above were passed we enter the plaintext to be subtitued and we register its length
    string text = get_string("plaintext: ");
    int l = strlen(text);
    printf("ciphertext: ");
    for (int n = 0 ; n < l; n++)
    {
        //we check if the plaintext contain letters and if so we check if they are lower or upper cases
        if (isalpha(text[n]))
        {
            if (isupper(text[n]))
            {
                //in ASCII the letter A coresponds with the number 65, so we subtract that
                int x = text[n] - 65;
                //now that A coresponds to 0 and Z to 25, like how equivalent letters are arranged in the key
                printf("%c", toupper(key[x]));
            }
            else if (islower(text[n]))
            {
                // the letter a coresponds to number 97
                int y = text[n] - 97;
                printf("%c", tolower(key[y]));
            }
        }
        else
        {
            printf("%c", text[n]);
        }
    }
    printf("\n");
}


