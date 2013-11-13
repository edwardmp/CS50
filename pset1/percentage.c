/****************************************************************************
 * percentage.c                                                    
 *                                                              
 * Edward M. Poot                                         
 *                                                              
 * Calculates percentage from user supplied numerator and denumerator               
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    // set to negative value so prompt shows up at least once   
    int numerator = -1;
    
    while (numerator < 0) {
         printf("non-negative numerator: ");    
         numerator = GetInt();  
    }
    
    // same as before, set to 0 to show up prompt at least once
    int denumerator = 0;
    
    while (denumerator <= 0) {
        printf("positive denominator: ");
        denumerator = GetInt();
    }
 
    // do the math
    float calc = (numerator % denumerator);
    
    // print value of calc, round to 2 decimals
    printf("%.2f%% \n", calc);
}
