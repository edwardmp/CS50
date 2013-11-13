/****************************************************************************
 * sort.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Encode an user supplied string using a caesar cipher.
 * Numerical key is being entered by the user as a command line argument.
 *
 * Please note I already used some char* pointers to get familiar.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

// function prototype
int* splitArray(int array[], int start, int end);

void sort(int array[], int size)
{
    // if list already sorted since there is only one element return false
    if (size < 2)
        return;
     
    int* leftArray = splitArray(array, 0, size / 2);
    sort(leftArray, size / 2);
    
    int* rightArray = splitArray(array, size / 2, size);
    sort(rightArray, size / 2);
    
    int l = 0;
    int r = 0;
    int i;
    
    for(i = 0; i < size; i++)
    {   
        printf("%i %i %i %i ", l, r, leftArray[l], rightArray[r]);
        if (r != size/2 && rightArray[r] < leftArray[l])
        {
            array[i] = rightArray[r];
            printf("right \n");
            r++;
        }
        else if (l != size/2 && leftArray[l] < rightArray[r])
        {
            array[i] = leftArray[l];
            printf("left \n");
            l++;
        }
        else {
            printf ("none \n");
        }
    }
    
    free(splittedArray);
    free(rightArray);
    free(leftArray);
    
    return;
}

int* splitArray(int array[], int start, int end)
{
  int size = end - start;
  int* splittedArray = malloc(size * sizeof(int));
  
  int i = 0;
  int a = start;
  while (a < end)
  {
    splittedArray[i] = array[a];
    i++;
    a++;
  }

  return splittedArray;
}

int main(void)
{
    int numbers[SIZE] = { 4, 15, 16, 50, 8, 23, 42, 108 };
    for (int i = 0; i < SIZE; i++)
        printf("%d ", numbers[i]);
        
    printf("\n");
    sort(numbers, SIZE);
    for (int i = 0; i < SIZE; i++)
        printf("%d ", numbers[i]);
    printf("\n");
    return 0;
}
