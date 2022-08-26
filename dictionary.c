// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// const unsigned int N = 625;

// Hash table
const unsigned int N = 500;
node *table[N];
unsigned int counter = 0;
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char word_copy[LENGTH + 1];
    int n = strlen(word);
    
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    unsigned int key = hash(word_copy);

    node* cursor = table[key]; 
    while (cursor != NULL) {
        if (strcasecmp(word, cursor->word) == 0) {
            return true;
        }
        else 
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return (word[0]*word[0])%500;
} 

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH+1];
    FILE *file = fopen(dictionary, "r");

    while (fscanf(file, "%s", word) != EOF) 
    {
        node* new_word = (node *) malloc(sizeof(node));
        
        strcpy(new_word->word, word);
        int key = hash(new_word->word);

        node* head = table[key];

        if (head == NULL) {
            table[key] = new_word;
            counter++;
        } else {
            new_word->next = table[key];
            table[key] = new_word;
            counter++;
        }
    }
    fclose(file);
    return true;
}
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i <= N; i++)
    {
        if (table[i])
        {
            node* head = table[i];
            node* cursor = head;
        
            while (cursor != NULL) {
                node* tmp = cursor;
                cursor = cursor->next;
                free(tmp);
        }
        }
        
    }
    
    return true;
}

