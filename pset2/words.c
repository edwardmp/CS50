/****************************************************************************
 * words.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 *
 * Searches dictionary file for string inputted as command line argument.
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char *argv[]) {

    string searchString = argv[1];
    
    do {
        FILE *file = fopen("/usr/share/dict/words", "r");
        char tmp[256]= {0x0};
        
        while(file != NULL && fgets(tmp, sizeof(tmp), file) != NULL)
        {
            if (strstr(tmp, searchString))
            {   
               
                printf("%s", tmp);
            }              
        }
    } while (argc == 0);
}
