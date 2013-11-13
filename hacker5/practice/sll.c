/*************************************************************************
 * sll.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Hacker 5
 *
 * Implements a simple singly-linked list structure for ints.
 ************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// the size of our test list: feel free to adjust as you wish!
#define TEST_SIZE 10

typedef struct node
{
    // the value to store in this node
    int i;
    
    // the link to the next node in the list
    struct node* next;
}
node;

// declare the first node of our list (as a global variable)
node* first = NULL;

/**
 * Returns the length of the list.
 */
int length(void)
{
    int length = 0;
    node* ptr = first;
    while (ptr != NULL)
    {
        length++;
        ptr = ptr->next;
    }
    return length;
}

/**
 * Returns true if a node in the list contains the value i and false
 * otherwise.
 */
bool contains(int i)
{
    node* node = first;
    int count = 0;
    while (node != NULL)
    {
        if (node->i == count)
            return true;
        count++;
        node = node->next;
    }
    return false;
}

/**
 * Puts a new node containing i at the front (head) of the list.
 */
void prepend(int i)
{
    node* temp = (node* ) malloc(sizeof(node));
    temp->i = i;
    temp->next = first;
    first = temp;
}

/**
 * Puts a new node containing i at the end (tail) of the list.
 */
void append(int i)
{
    node* ptr = first;
    node* new = (node* ) malloc(sizeof(node));
    
    new->i = i;
    new->next = NULL;
    
    if (first == NULL)
    {
        first = new;
        return;
    }
    
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = new;
}

/**
 * Puts a new node containing i at the appropriate position in a list
 * sorted in ascending order.
 */
void insert_sorted(int i)
{
    node* ptr = first;
    
    node* new = (node *) malloc(sizeof(node));
    new->i = i;
    
    if (ptr == NULL)
    {
        first = new;
        new->next = NULL;
        return;
    }
    
    if (ptr->i >= i)
    {
        new->next = first;
        first = new;
        return;
    }
    
    while(ptr->next != NULL)
    {
        if (ptr->next->i >= i)
        {
            new->next = ptr->next;
            ptr->next = new;
            return;
        }
        ptr = ptr->next;
    }
    
    ptr->next = new;
    new->next = NULL;
}

/**
 * Implements some simple test code for our singly-linked list.
 */
int main(void)
{
    printf("Prepending ints 0-%d onto the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        prepend(i);
    }
    printf("done!\n");
    
    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");
    
    printf("Making sure that values are arranged in descending order...");
    node* n = first;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i == TEST_SIZE - i - 1);
        n = n->next;
    }
    printf("good!\n");
    
    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");
    
    printf("Appending ints 0-%d to the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        append(i);
    }
    printf("done!\n");
    
    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");
    
    printf("Making sure that values are arranged in ascending order...");
    n = first;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i == i);
        n = n->next;
    }
    printf("good!\n");
    
    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");
    
    printf("Inserting %d random ints to the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        insert_sorted(rand() % TEST_SIZE);
    }
    printf("done!\n");
    
    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");
    
    printf("Making sure that values are arranged in sorted order...");
    n = first;
    int prev = 0;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i >= prev);
        prev = n->i;
        n = n->next;
    }
    printf("good!\n");
    
    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");
    
    printf("\n********\nSuccess!\n********\n");
    
    return 0;
}