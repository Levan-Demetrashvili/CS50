// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 400;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hash_code = hash(word);
    node *p = table[hash_code];
    // Check if the word is in dictionary
    while (p != NULL)
    {
        if (strcasecmp(p->word, word) == 0)
        {
            return true;
        }
        p = p->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (word == NULL)
    {
        return -1;
    }
    int len = strlen(word);
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += pow((toupper(word[i]) % 65), 2);
    }

    return sum % 400;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Initialize all table pointers with NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char buffer[LENGTH + 1];
    while (fscanf(dict, "%s", buffer) != EOF)
    {

        // get hash code from word
        unsigned int hash_code = hash(buffer);
        // Create new node and intialize with word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, buffer);
        n->next = table[hash_code];
        table[hash_code] = n;
    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int size = 0;
    for (int i = 0; i < N; i++)
    {
        // pointer for each linked list
        node *p = table[i];
        while (p != NULL)
        {
            size++;
            p = p->next;
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        while (p != NULL)
        {
            node *next = p->next;
            free(p);
            p = next;
        }
    }
    return true;
}
