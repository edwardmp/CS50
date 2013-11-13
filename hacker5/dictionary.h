/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// define structure for each node in the list
typedef struct node
{
    // the word we store in this node
    char* word;
    
    // the link to the next node in the list
    struct node* next;
}
node;

// define structure for each misspelled node in the list
typedef struct misspelledNode
{
    // the misspelled word we store in this node
    char* word;
    
    // the link to the next mispellde node in the list
    struct misspelledNode* next;
}
misspelledNode;

// ideally SIZE needs to be approximately amount of words in the dict since then every word has it's own hash
#define SIZE 160000

/**
 * Hashes a word. Returns hashed word.
 * Source of hash function: stackoverflow.com/questions/14409466/simple-hash-functions
 * @param const char* word - The word we want return a hash value for.
 * @return unsigned int - Returns the hashed value.
 */
unsigned int hashWord(const char* word);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Creates hashtable for words misspelled.
 * This way we can count the number of unique words misspelled.
 * @param const char* word - The misspelled word we want to register.
 * @return int - The return value is equal to 0 if no errors ocurred, else 1.
 */
int misspelledWordRegister(const char* word);

#endif // DICTIONARY_H
