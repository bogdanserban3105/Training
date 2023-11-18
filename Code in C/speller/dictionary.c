// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <string.h>

typedef uint8_t BYTE;

int count = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// i let it 26,even tho its slow its less code
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // stocheaza tot in hash table
    // functie hash care sa atribuie un numar fiecarui input
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        char *cuvant = cursor->word;
        if (strcasecmp(cuvant, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //reused from my scrabble problem solution
    int x = 0;
    if (isalpha(word[0]))
    {
        if (isupper(word[0]))
        {
            //in ASCII the letter A coresponds with the number 65, so we subtract that
            x = word[0] - 65;
        }
        else if (islower(word[0]))
        {
            //in ASCII the letter A coresponds with the number 97, so we subtract that
            x = word[0] - 97;
        }
    }
    else
    {
        return 1;
    }

    return x;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }
    //initializeaza variabila in care e stocat cuvantul din dex
    char wrd[LENGTH + 1];
    node *array = NULL;
    //scaneaza si stocheaza din file in wrd
    while (fscanf(file, "%s", wrd) != EOF)
    {

        node *new_node = malloc(sizeof(node));

        //check if n returns null
        if (new_node == NULL)
        {
            return false;
        }
        //copiaza cuvantul wrd in word al nodeului
        strcpy(new_node->word, wrd);
        //ramura next a nodeului primeste null
        new_node->next = NULL;
        //pana aici e bine

        new_node->next = array;
        array = new_node;

        array->next = table[hash(new_node->word)];

        table[hash(new_node->word)] = array;
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //made a loop to go through all array
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}

