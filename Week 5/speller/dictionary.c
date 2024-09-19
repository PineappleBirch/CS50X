#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Dictionary size
unsigned int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase
    char lower_word[LENGTH + 1];
    int i = 0;
    while (word[i])
    {
        lower_word[i] = tolower(word[i]);
        i++;
    }
    lower_word[i] = '\0';

    // Hash the word to get the bucket index
    unsigned int index = hash(lower_word);

    // Traverse the linked list at this index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lower_word) == 0)
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
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(f, "%s", word) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(f);
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);

        // Hash the word to get the bucket index
        unsigned int index = hash(word);

        // Insert the node into the hash table
        new_node->next = table[index];
        table[index] = new_node;

        // Increment the dictionary size count
        dictionary_size++;
    }

    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
