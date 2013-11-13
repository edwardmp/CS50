/****************************************************************************
 * dictionary.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Hacker 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include "dictionary.h"

// the hash table array we store the linked lists in for each key
node* wordArray[SIZE];

// the hash table array we store misspelled words in, this way, we can count the amount of unique words misspelled
misspelledNode* misspelledWordArray[SIZE];

// start at zero words, while we load words we increment this after each word
unsigned int wordsInDictionary = 0;

// while we check words for mispellings we increment this if mispelling is not already registered
unsigned int uniqueMispellings = 0;

/**
 * Hashes a word. Returns hashed word.
 * Source of hash function: stackoverflow.com/questions/14409466/simple-hash-functions
 * I chose this function because of the few short hash functions I found, this one was consistenly the fastest.
 * @param const char* word - The word we want return a hash value for.
 * @return unsigned int - Returns the hashed value.
 */
unsigned int hashWord(const char* word)
{
    unsigned int count;
    unsigned int hashValue = 0;
    for(count = 0; word[count] != '\0'; count++)
        hashValue = word[count] + (hashValue << 6) + (hashValue << 16) - hashValue;
 
    return (hashValue % SIZE);
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{   
    // convert word to lowercase   
    char wordLowercase[strlen(word)];
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        wordLowercase[i] = tolower(word[i]);
    }
    // don't forget to add the null character to indicate end
    wordLowercase[strlen(word)] = '\0';
    
    // look up the lowercased word in the array
    node* nodeToCheckAgainst = wordArray[hashWord(wordLowercase)];
    
    // if no node has been initialized at that position in the array, return false
    while (nodeToCheckAgainst != NULL)
    {         
        // if strcmp returns 0, we know that the words are identical 
        if (strcmp(nodeToCheckAgainst->word, wordLowercase) == 0)
        {
            return true;
        }
        
        // the words were not identical, check next node in the list
        nodeToCheckAgainst = nodeToCheckAgainst->next;  
    }
    
    // word has not been found in dictionary, so it is a mispelling, let's register it
    misspelledWordRegister(wordLowercase);
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the dictionary file for reading
    FILE* dict = fopen(dictionary, "r");
      
    // if we couldn't open the dict file return  
    if (dict == NULL)
        return false;
         
    // create string that holds current word readed
    char* string = malloc((LENGTH + 1) * sizeof(char));
    
    // in each word we start at the first char, and then increment int after each char read
    int index = 0;
    
    // placeholder for char, so we can use it in the loop later on
    char c;
    
    // loop through each word in the dict file
    while((c = fgetc(dict)) != EOF)
    {    
        // end of wordline is reached
        if (c == '\n')
        {
            string[index] = '\0';   
  
            // malloc space for the word
            node* newWordNode = malloc(sizeof(node));
            
            // mallloc space on the heap for the word itself
            newWordNode->word = malloc((strlen(string) + 1) * sizeof(char));
            
            if (newWordNode == NULL || newWordNode->word == NULL)
            {
                printf("Allocating memory failed. Aborting");
                return 1;
            }
                
            // just initialize the next pointer to null for now
            newWordNode->next = NULL;
            
            // copy the word string to the node
            strcpy(newWordNode->word, string);
            
            // calculate index in WordArray
            int hashIndex = hashWord(string);          
            
            // there is no linked list yet at that location of the wordArray, so let's make one
            if (wordArray[hashIndex] == NULL)
            {
                // at that index position of the array, assign the address of the new node
                wordArray[hashIndex] = newWordNode;              
            }
            // there is already a linked list at that location, so append to tail
            else
            {
                node* ptr = wordArray[hashIndex];
                
                // loop through nodes til we find one which next pointer is still NULL
                while(ptr->next != NULL)
                    // not yet found any empty next pointers, so go to the next one
                    ptr = ptr->next;
                
                // store the node in the next (tail) node     
                ptr->next = newWordNode;
            }
            
            // reset index for next word
            index = 0;
            
            // increment the amount of words that have been read
            wordsInDictionary++;
        }  
        else
        {             
            string[index] = c;
            index++; 
        }
    } 
    
    // release temporarily allocated string
    free(string);
    
    // close the dictionary file
    fclose(dict);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // if words is equal to 1 or higher, we assume size is correct
    // pset document states that a dictionary contains at least one word
    if (wordsInDictionary >= 1)
        return wordsInDictionary;
        
    // if words is equal to 0, something went wrong   
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // loop through all indexes in the wordArray
    for (int i = 0; i < SIZE; i++)
    {
        // only if there is a linked list at that index we have to free stuff
        while (wordArray[i] != NULL)
        {
            // free the space for individual words in each node we allocated
            free(wordArray[i]->word);
            
            // find address of next node
            node* next = wordArray[i]->next;
            
            // free the node itself
            free(wordArray[i]);
            
            // on next iteration, we loop through the next node
            wordArray[i] = next;
        }
        
        // same as the while above, but this time for the hash table of unique misspelled words
        while (misspelledWordArray[i] != NULL)
        {
            // free the space for individual words in each node we allocated
            free(misspelledWordArray[i]->word);
            
            // find address of next node
            misspelledNode* next = misspelledWordArray[i]->next;
            
            // free the node itself
            free(misspelledWordArray[i]);
            
            // on next iteration, we loop through the next node
            misspelledWordArray[i] = next;
        }
    }
    
    // print the amount of unique mispellings we encountered
    // note that I do this here because we can not alter speller.c
    printf("\nUNIQUE WORDS MISSPELLED: %d", uniqueMispellings);
    
    return true;
}

/**
 * Creates hashtable for words misspelled.
 * This way we can count the number of unique words misspelled.
 * @param const char* word - The misspelled word we want to register.
 * @return int - The return value is equal to 0 if no errors ocurred, else 1.
 */
int misspelledWordRegister(const char* word)
{
    // malloc space for the word
    misspelledNode* newMisspelledNode = malloc(sizeof(misspelledNode));

    // mallloc space on the heap for the word itself
    newMisspelledNode->word = malloc((strlen(word) + 1) * sizeof(char));
    
    if (newMisspelledNode == NULL || newMisspelledNode->word == NULL)
    {
        printf("Allocating memory failed. Aborting");
        return 1;
    }
            
    // just initialize the next pointer to null for now
    newMisspelledNode->next = NULL;

    // copy word to node
    strcpy(newMisspelledNode->word, word);

    // calculate index in WordArray
    int hashIndex = hashWord(word);          

    // there is no linked list yet at that location of the wordArray, so let's make one
    if (misspelledWordArray[hashIndex] == NULL)
    {
        // at that index position of the array, assign the address of the new node
        misspelledWordArray[hashIndex] = newMisspelledNode;   
        
        uniqueMispellings++;           
    }
    // there is already a linked list at that location, so append to tail
    else
    {
        misspelledNode* ptr = misspelledWordArray[hashIndex];
        
        // loop through nodes til we find one which next pointer is still NULL
        while(ptr->next != NULL)
            // not yet found any empty next pointers, so go to the next one
            ptr = ptr->next;
        
        // store the node in the next (tail) node     
        ptr->next = newMisspelledNode;
    }  
    
    // report no errors
    return 0;      
}
