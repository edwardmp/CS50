/****************************************************************************
 * greedy.c                                                     
 *                                                              
 * Edward M. Poot
 * edwardmp@gmail.com
 *                                                              
 * Calculates the least (optimal) amount of coins (and which coins)               
 * that need to be returned when calcuating change.             
 ***************************************************************************/
 
#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    // declare float that holds change amount
    float amount;
    
    // prompt user to fill in change amount, repeat if input not valid
    do {
        printf("Change owned: ");
        amount = GetFloat();
    }
    while (amount <= 0);
    
    // convert float to integer
    int roundedAmount = (int) round((amount * 100)); // multiply by 100 to get amount in cents, then round just to be sure of any inconsistencies
    
    // calculate how many quarters "fit" in roundedAmount
    int quarters = (roundedAmount / 25);
    
    // first substract the value of the quarters from the roundedAmount, afterwards same as above, but this time considering dimes instead of quarters
    int dimes = ((roundedAmount - (quarters * 25)) / 10 );
    
    // same as above, but this time also substract the dimes
    int nickels = ((roundedAmount - (quarters * 25) - (dimes * 10)) / 5 );
    
    // same as above, but this time also substract the nickels
    int pennies = ((roundedAmount - (quarters * 25) - (dimes * 10) - (nickels * 5)) / 1 );
    
    // finally count how many coins in total are used
    int totalCoins = quarters + dimes + nickels + pennies;
    
    printf("Change owed consists of %d quarters, %d dimes, %d nickels and %d pennies.\nAmount of coins is %d.\n", quarters, dimes, nickels, pennies, totalCoins);
    
    // return 0 since everything went perfect
    return 0;
}
