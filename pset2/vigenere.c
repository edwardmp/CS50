/****************************************************************************
 * vigenere.c                                                     
 *                                                              
 * Edward M. Poot  
 * edwardmp@gmail.com                                             
 *                                                              
 * Encode an user supplied string using a Vigenere style cipher.              
 * Alphabetical key is being entered by the user as a command line argument.
 *
 * Please note I already used some char* pointers to get familiar.             
 ***************************************************************************/

#import <stdio.h>
#import <cs50.h>
#import <string.h>
#include <ctype.h>

// function prototype
string VigenereCipher(string plain, string key);

int main(int argc, string argv[])
{   
    // typecast input string to integer if 1 argument is given, else return 0 so program exits in the next if statement
    string key = argv[1];
    
    // if more than 2 parameters (first being ./vigenere, second the key)
    // are supplied abort the program
    if (argc != 2) {
        printf("Usage: vigenere <key>\n");
        printf("Wrong number of parameters, string or negative number supplied. Aborting.\n");
        
        // stop executing program
        return 1;
    }
    
    // loop through all the keys in the key and check if they are all alphabetical
    for(int i = 0, j = strlen(key); i < j; i++)
    {
        if (!isalpha(key[i]))
        {   
            printf("Usage: vigenere <key>\n");
            printf("Non-alphabetic characters given. Aborting.\n");
            
            // impossibile to do Vigenere cipher using non-alphabetical chars, abort.
            return 1;
        }
    }
    
    string plainText;
    
    do {
        plainText = GetString();
    }
    while (strlen(plainText) == 0); // keep asking for input until user enters at least 1 char
    
    // cipher the plainText
    string result = VigenereCipher(plainText, key);
    
    // print the result back to the user
    printf("%s\n", result);
    
    return 0;
}

/*
 * Ciphers given string using Vigenere cipher, alphabetical letters shifted by wrapping the key letters around cyclically if needed
 * @param string Input that is being ciphered
 * @param string Use this string to cyclically wrap around the input  
 */
string VigenereCipher(string plain, string key)
{
    // calculate length of key used later
    // define it here so strlen() won't be run each time the for loop runs
    int keyLength = strlen(key);
    
    // initialize a variable that will hold ciphered string, needs to be same length as plain string
    char* cipher = plain;
    
    // loop through all characters of the plain text string
    for (int i = 0, j = 0, n = strlen(plain); i < n; i++)
    {   
        // if alphabetic proceed with ciphering, else return normal character
        if (isalpha(plain[i])) {
            
            // calculate ASCII code for the key position (j), wrap around beginning of keyword when end of keyword is reached
            char keyReferenceValue = (isupper(key[j % keyLength])) ? 'A' : 'a';
            
            // calculate ASCII code of the first letter of alphabet depending on upper- or lowercase
            char referenceValue = (isupper(plain[i])) ? 'A' : 'a';
            
            // calculate cipher letter using formula ci = (pi + kj) % 26, then convert to right ASCII character number
            cipher[i] = ((plain[i] - referenceValue + (key[(j % keyLength)] - keyReferenceValue)) % 26) + referenceValue;
            
            // printf("%c %i %i %i %i %i\n", cipher, j, strlen(key), key[(j % keyLength)], referenceValue, rotate);
           
            // increment key position (j) so next letter in key is used
            j++;
        }
        else {
            // output all non-alphabetical chars normally
            cipher[i] = plain[i];
        }
    }
    
    // return ciphered string
    return cipher;
}
