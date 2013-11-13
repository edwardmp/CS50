/****************************************************************************
 * mario.c                                                     
 *                                                              
 * Edward M. Poot  
 * edwardmp@gmail.com
 *                                                              
 * Generates Super Mario style "pyramid" of which user              
 * can provides the height as an integer     
 ***************************************************************************/
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // variable that stores entered height
    int height;
    
    // check if height meets requirements, else ask again
    do
    {
        printf("Height: ");
        height = GetInt();
    } while((height > 23) || (height <= 0));
    
    // loop trough {height} lines
    for (int i = 0; i < height; i++)
    {   
        // amount of hashes before on a line is equal line number plus 2 (first line is line 0)
        int hashes = (i + 2);
        
        // amount of spaces is equal to height+1 (= width, since two columns at right are equal height) minus space occupied by hashes
        int spaces = ((height + 1) - hashes);
        
        // print out {spaces} number of spaces
        for (int j = 0; j < spaces; j++) { 
            printf(" ");
        }  
        
        // print out {hashes} number of hashes
        for (int k = 0; k < hashes; k++) {
           printf("#");
        }
        
        // start a new line after each iteration
        printf("\n");
    }
    
    return 0;
}
