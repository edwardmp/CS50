/****************************************************************************
 * caesar.c                                                     
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
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// function prototype
char* CaesarCipher(string plain, int key);

int main(int argc, string argv[])
{   
    // typecast input string to integer if 1 argument is given, else return 0 so program exits in the next if statement
    int key = (argc == 2) ? atoi(argv[1]) : 0;
   
    // if more than 2 parameters (first being ./caesar, second the key)
    // are supplied abort the program
    if (argc != 2 || key <= 0) {
        printf("Usage: caesar <key>\n");
        printf("Wrong number of parameters, string or negative number supplied. Aborting.\n");
        
        // stop executing program
        return 1;
    }
    
    string plainText;
    
    do
    {
        plainText = GetString();
    }
    while (strlen(plainText) == 0); // keep asking for input until user enters at least 1 char
    
    string result = CaesarCipher(plainText, key);
    
    printf("%s\n", result);
    
    return 0;
}

/*
 * Ciphers given string using Caesar cipher, alphabetical letters are shifted by 'k'
 * @param string Input that is being ciphered
 * @param integer Shift alphabetical letters this many positions   
 */
char* CaesarCipher(string plain, int k)
{
    char* cipher = plain; // create a placeholder variable, allocating the size using equal length of plain
    
    for (int i = 0, n = strlen(plain); i < n; i++)
    {          
        // confirm that character is alphabetic
        if (isalpha(plain[i])) {
            // check if the char is upper- or lowercase
            if (isupper(plain[i]))
            {
                cipher[i] = (((plain[i] - 'A') + k) % 26) + 'A'; // calculate which letter of the alphabet it is, calculate modulo of result, then add the ASCII value of 'A'
            }
            else if (islower(plain[i])) {
                cipher[i] = (((plain[i] - 'a') + k) % 26) + 'a'; // same as above, but considering lowercase 'a' as starting point of the alphabet
            }
        }
        else {
            cipher[i] = plain[i]; // all other characters aren't changed
        }
    }
    
    return cipher; // return the ciphered string
}                 
