#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffile.h"
#include "tree.h"
#include "forest.h"
                   
// function prototype

/**
 * Converts char to binary representation in Huffman tree.
 * @param Tree* tree - Starting point of search.
 * @param char c - The character we want to convert to binary representation.
 * @param char array[] - The array in which we store the binary representation.
 * @param int counter - Increments after left/right step, stores current position in the array.
 * @return bool - True if we've found the char we're looking for, false if we didn't.
 */
bool convertLetterToBinary(Tree* tree, char c, char trail[], int counter);

int main(int argc, char* argv[])
{
    // check if user supplied exactly 2 arguments
    if (argc != 3)
    {
        printf("Usage: huff <input file> <output file>\n");
        return 1;
    }
    
    // store in- and output filenames
    char* inputFile = argv[1];
    char* outputFile = argv[2];
    
    FILE* inputFP;
    Huffile* hf;  
    // check if we can open both files for either reading or writing
    if((inputFP = fopen(inputFile, "r")) == NULL)
    {
        printf("Could not open input file %s. Aborting.\n", inputFile);
        return 1;
    }
    else if ((hf = hfopen(outputFile, "w")) == NULL)
    {
        printf("Could not open (huffed) output file %s. Aborting.\n", outputFile);
        fclose(inputFP);
        return 1;
    }

    // create space for header and initialize properties
    Huffeader* header = malloc(sizeof(Huffeader));
    header->magic = MAGIC;
    header->checksum = 0;    
    // just to be sure, initialize all other values to 0
    for (int i = 0; i < SYMBOLS; i++)
        header->frequencies[i] = 0;
    
    int c;
    while ((c = fgetc(inputFP)) != EOF)
    {
        // increment the header correctly
        header->frequencies[c]++;
        header->checksum++;
    }
    
    Forest* huffForest = mkforest();
    Tree* newTree;
    for (int j = 0; j < SYMBOLS; j++)
    {   
        if (header->frequencies[j] > 0)
        {
            newTree = mktree();
            newTree->frequency = header->frequencies[j];
            newTree->symbol = j;
            newTree->left = NULL;
            newTree->right = NULL;
            plant(huffForest, newTree);
        }
    }

    // write the header
    if(!hwrite(header, hf))
    {
        printf("Could not write header to file %s. Aborting.\n", outputFile);
        free(header); // free memory
        return 1;
    } 
    
    // we don't need the header anymore so let's free it
    free(header);           
        
    // the first parent
    Tree* huffParent;

    // pick two trees with lowest frequenties out of forest
    Tree* firstPicked = pick(huffForest);
    Tree* secondPicked = pick(huffForest);
      
    // keep iterating til there are not enough trees to be picked
    while (firstPicked != NULL && secondPicked != NULL)
    {       
        // create new parent          
        huffParent = mktree();
               
        // set parent's left child pointer to the correct tree  
        huffParent->left = firstPicked;
   
        // set parent's right child pointer to the correct tree  
        huffParent->right = secondPicked;

        // calculate parent frequency
        huffParent->frequency = firstPicked->frequency + secondPicked->frequency;

        // plant the new parent
        plant(huffForest, huffParent);          

        // pick new trees for next iteration        
        firstPicked = pick(huffForest);     
        secondPicked = pick(huffForest);
    }

    // reset input file position to beginning
    fseek(inputFP, 0, SEEK_SET);
    
    // if after only 1 char end of file is reached, just write 0
    if (fgetc(inputFP) != EOF && fgetc(inputFP) == EOF)
    {
        if(!bwrite(0, hf))
            printf("Writing failed. Aborting.\n"); 
    }
    // more than 1 char, continue normally
    else
    {
        // reset input file position to beginning
        fseek(inputFP, 0, SEEK_SET);
                  
        char trail[1024]; // set to a large size, so there's enough space
        char ch;
        while ((ch = fgetc(inputFP)) != EOF)
        {
            if (convertLetterToBinary(huffParent, ch, trail, 0))
            {           
                // loop through all bits in the array
                for (int i = 0; i < strlen(trail); i++)
                {               
                    // convert ASCII value to numerical value
                    if(!bwrite(trail[i] - '0', hf))
                    {
                        printf("Writing failed. Aborting.\n");
                        return 1;
                    }
                } 
            }         
        }
    }
    
    // calculate both files' final size
    double inputSize = 0; double outputSize = 0;
    printf("Input file %s is %.0f bytes.\n", inputFile, inputSize = ftell(inputFP));
    printf("Huffed file %s is %.0f bytes.\n", outputFile, outputSize = ftell(hf->stream));
    
    if (outputSize > inputSize)
        printf("\nActually that's useless, huffed file is %.2f%% larger than the input file was..\nYou'll be better off using the original file!\n", ((outputSize / inputSize) * 100));  
    else if (outputSize < inputSize)
        printf("\nCongratulations, the huffed file's size is just %.2f%% of the input file!\n", ((outputSize / inputSize) * 100));
    
    // housekeeping    
    rmtree(huffParent);
    rmforest(huffForest);
    
    //close files
    hfclose(hf);  
    fclose(inputFP); 
}

/**
 * Converts char to binary representation in Huffman tree.
 * @param Tree* tree - Starting point of search.
 * @param char c - The character we want to convert to binary representation.
 * @param char array[] - The array in which we store the binary representation.
 * @param int counter - Increments after left/right step, stores current position in the array.
 * @return bool - True if we've found the char we're looking for, false if we didn't.
 */
bool convertLetterToBinary(Tree* tree, char c, char trail[], int counter)
{   
    // base case, we have found the symbol we were looking for
    if (tree->symbol == c)
    {
        // end the binary trail
        trail[counter] = '\0';
        return true;
    }
    else
    {    
        // if we are at at a leaf, continue
        if (tree->left != NULL && tree->right != NULL)
        {        
            // we have found the char we are looking for at left tree
            if (convertLetterToBinary(tree->left, c, trail, counter + 1))
            {
                trail[counter] = '0';
                return true;
            }
            // we have found the car we are looking for at right tree
            if(convertLetterToBinary(tree->right, c, trail, counter + 1))
            {
                trail[counter] = '1';
                return true;
            }
        }
        return false;
    }        
}
