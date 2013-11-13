/****************************************************************************
 * needle.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Searches for inputted number in predefined array. Applies binary search.
 ***************************************************************************/

#include <cs50.h>
#include <stdio.h>

#define SIZE 8

bool search(int needle, int haystack[], int size)
{
    int lowIndex = 0;
    int highIndex = size - 1;
    int middle = (highIndex + lowIndex) / 2;
    
    while (lowIndex <= highIndex) {
     
        if (haystack[middle] > needle)
        {   
            highIndex = middle - 1;
        }
        else if (haystack[middle] < needle) {
            lowIndex = middle + 1;
        }
        else if (haystack[middle] == needle) {
            return true;    
        }
        else {
            return false;
        }
               
        // calculate middle with new indexes
        middle = (highIndex + lowIndex) / 2;
    }
    return false;
}

int main(void)
{
    int numbers[SIZE] = { 4, 8, 15, 16, 23, 42, 50, 108 };
    printf("> ");
    int n = GetInt();
    if (search(n, numbers, SIZE))
        printf("YES \n");
    return 0;
}
