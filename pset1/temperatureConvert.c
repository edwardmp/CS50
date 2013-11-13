/****************************************************************************
 * temperatureConvert.c                                                    
 *                                                              
 * Edward M. Poot
 * edwardmp@gmail.com
 *                                                              
 * Converts entered Fahrenheit temperature to degrees Celsius             
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Vul een temperatuur in Celsius in: ");
    
    // retrieve user input
    float c = GetFloat();
    
    // conversion formula found on www.manualsweb.com/temp.htm
    float f = c * (9.0 / 5.0) + 32.0;
    
    printf("%.1f graden Celsius is %.1f graden Fahrenheit \n", c, f);
    
    return 0;
}  
