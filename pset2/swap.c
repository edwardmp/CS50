/****************************************************************************
 * swap.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 *
 * Swaps two inputted integers.
 ***************************************************************************/

#import <stdio.h>
#import <cs50.h>
#import <string.h>
 
int main(void)
{   
    printf("x: ");
    int x = GetInt();
    
    printf("y: ");
    int y = GetInt();
    printf("x is %i\ny is %i\n", x , y);
    
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
    printf("x is %i\ny is %i\n", x , y);    
}
