#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

int* split(int array[], int start, int end)
{
    int length = end - start;
    int* splittedArray = malloc(length * sizeof(int));
    
    int i = 0;
    int j = start;
    
    while (j < end)
    {
        splittedArray[i] = array[j];
        i++;
        j++;
    }
    
    return splittedArray;
}

void sort(int array[], int size)
{ 
    if (size < 2)
        return;
       
    int* leftArray = split(array, 0, size / 2);
    sort(leftArray, size / 2);
    
    int* rightArray = split(array, size / 2, size);
    sort(rightArray, size / 2);
    
    for (int i = 0, l = 0, r = 0; i < size; i++)
    {
        if (l != size / 2 && leftArray[l] < rightArray[r])
        {   
            array[i] = leftArray[l];
            l++;
        }
        else if (r != size / 2 && rightArray[r] < leftArray[l])
        {
            array[i] = rightArray[r];
            r++;
        }
    }
    
    return;   
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
