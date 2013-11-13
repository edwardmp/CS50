/****************************************************************************
 * myspace.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 *
 * Converts input string to MySpace style string.
 ***************************************************************************/

#import <stdio.h>
#import <cs50.h>
#import <string.h>

int main(void)
{
    string s;
         
    do {
        printf("Input string: ");
        s = GetString();
    } while (!s);
        
       int count = 0;
       for (int k = 0, length = strlen(s); k < length; k++)
       {
            if ((s[k] >= 'A' && s[k] <= 'Z') || (s[k] >= 'a' && s[k] <= 'z'))
            {
                if (count % 2 == 0)
                {
                    s[k] = s[k] & ~ ('a' - 'A');
                }
                else {
                    s[k] = s[k] | ('a' - 'A');
                }
                count++;         
            }
            printf("%c", s[k]);
       }
}
