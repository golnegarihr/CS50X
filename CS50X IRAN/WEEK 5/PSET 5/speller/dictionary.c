// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>

#include "dictionary.h"

unsigned int shomaregar_size = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int shakhes ;

    shakhes = hash(word);

    node *neshangar = table[shakhes];

    while (neshangar != NULL)
    {
        if (strcasecmp(neshangar -> word, word) == 0)
        {
            return true;
        }
        neshangar = neshangar -> next;
    }
    return false;
}


// Hashes word to a number
//djb2 from http://www.cse.yorku.ca/~oz/hash.html reported by dan bernstein
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //opening dictionary file for reading
    FILE *khandan_dict = fopen(dictionary, "r");

    if (khandan_dict == NULL)
    {
        return false;
    }
    // made kalameh variable
    char kalameh[LENGTH + 1];

    while (fscanf(khandan_dict, "%s", kalameh) != EOF)
    {
        node *nodejadid = malloc(sizeof(node));

        if (nodejadid == NULL)
        {
            return false;
        }
        strcpy(nodejadid -> word, kalameh);

        nodejadid -> next = NULL;

        int shakhes2 ;

        shakhes2 = hash(kalameh);

        if (table[shakhes2] == NULL)
        {
            table[shakhes2] = nodejadid;
        }
        else
        {
            nodejadid -> next = table[shakhes2];

            table[shakhes2] = nodejadid;
        }
        shomaregar_size++;
    }
    fclose(khandan_dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return true ;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {


        while (table[i] != NULL)
        {
            node *movaghat = table[i] ->next;

            free(table[i]);

            table[i] = movaghat;
        }

    }
    return true;
}
