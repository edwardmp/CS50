#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool contains(int value);
bool insert(int value);
bool freeMemory(void);

typedef struct node
{
    // value of the node
    int value;
    
    // pointer to left child node
    struct node* left;
    // pointer to right child node
    struct node* right;
}
node;

// global root node
node* root = NULL;

int main(int argc, char* argv[])
{
    // create root node
    root = malloc(sizeof(node));
    root->value = 0;
    root->left = NULL;
    root->right = NULL;
    
    // insert a new node
    for (int i = 1; i <= 10; i++)
        if(insert(i))
            printf("New node %d successfully inserted!\n", i);
    
    // loop through some sample numbers
    for (int i = 0; i <= 10; i++)
        if (contains(i))
            printf("FOUND %i\n", i);    
        else
            printf("DID NOT FIND %i\n", i);   
            
    //free(root);   
    freeMemory();      
}

/**
 * Checks if value is present in tree.
 * @param - int value - The value we search in the tree.
 * @return - True if found, false if not found.
 */
bool contains(int value)
{
    // starting point
    node* ptr = root;

    // continue till we are at a leaf
    while (ptr != NULL)
    {
        // value found
        if (ptr->value == value)
        {
            return true;     
        }      
        // value is smaller than current node value, go to left
        else if (value < ptr->value)
        {   
            ptr = ptr->left;
        }
        // value is larger than current node value, go to right
        else if (value > ptr->value)
        {
            ptr = ptr->right;
        }
    }
        
    // value is not present in tree   
    return false;
}

/**
 * Inserts a new node in the tree.
 * @param int value - The value to be inserted.
 * @return - True if succes, false if errors ocurred or value already exists.
 */
bool insert(int value)
{
    // starting point
    node* ptr = root;

    // continue til either the left or right pointer contains a NULL value
    while (ptr->left != NULL || ptr->right != NULL)
    {
        // if value is already in tree return false
        if (ptr->value == value)
            return false;       
        
        // if the value is smaller than value of current node, continue to left, else right      
        ptr = (value < ptr->value) ? ptr->left : ptr->right;        
    }
    
    // alloc space for new node
    node *newNode = malloc(sizeof(node));
    
    // decide on which side we wan't to insert new node
    ptr->left = (value < ptr->value) ? newNode : NULL;
    ptr->right = (value > ptr->value) ? newNode : NULL;
    
    // something clearly went wrong
    if (newNode == NULL || (ptr->left == NULL && ptr->right == NULL))
        return false;
     
    // assign values to new node   
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
       
    return true; 
}

bool freeMemory(void)
{
    return true;
}
