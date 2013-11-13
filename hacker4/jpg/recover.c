/****************************************************************************
* recover.c
*
* Edward M. Poot
* edwardmp@gmail.com
*
* Hacker 4
*
* Recovers jpgs from a forensic image.
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define BLOCKSIZE 512

// the buffer is 512 bytes
uint8_t buffer[BLOCKSIZE];

// the source raw file
char rawFile[] = "card.raw";

// function prototype
bool isValidPattern(uint8_t firstBytes[], uint8_t patternOne[], uint8_t patternTwo[]);

int main (void)
{
    // open the forensic image
    FILE* forensicImage = fopen(rawFile, "r");

    // check if the forensic image could be opened, else abort
    if (forensicImage == NULL)
    {
        printf("card.raw could not be opened. Aborting\n");
        return 1;
    }

    // a valid jpg file begins with either of these patterns
    uint8_t jpgPattern1[4] = {0xff, 0xd8, 0xff, 0xe0};
    uint8_t jpgPattern2[4] = {0xff, 0xd8, 0xff, 0xe1};

    // var that stores the amount of jpg we have found
    uint8_t jpgCounter = 0;

    // var that stores if we are currently writing to a new file
    bool writingToNewFile = false;
    
    // alloc enough to hold 000.jpg plus \0
    char* jpgFilename = malloc((sizeof(char*) * strlen("000.jpg")) + 1);
    
    // create file pointer for the newly created jpgs
    FILE* jpgFile;
    
    // var that stores the first 4 bytes of the buffer
    uint8_t firstBytesOfFile[sizeof(jpgPattern1)];

    // keep looping til end of file is reached
    while(feof(forensicImage) == 0)
    {  
        // read through 512 bytes of the file
        fread(buffer, sizeof(uint8_t), BLOCKSIZE, forensicImage);
        
        // find first bytes of file and store it, so we can compare it later
        for(int i = 0; i < sizeof(firstBytesOfFile); i++)
            firstBytesOfFile[i] = buffer[i];
    
        // compare first bytes to find jpg patterns
        if (isValidPattern(firstBytesOfFile, jpgPattern1, jpgPattern2))
        {
            // create the filename for the next jpg
            sprintf(jpgFilename, "%.3i.jpg", jpgCounter);
            
            if (!writingToNewFile)
            {
                // open a new file for writing the found jpg to
                jpgFile = fopen(jpgFilename, "w");
                
                // if the file couldn't be created, abort
                if (jpgFile == NULL)
                    return 1;
                
                fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, jpgFile);
                writingToNewFile = true;
            }
            if (writingToNewFile)
            {
                // close the previous jpg
                fclose(jpgFile);
                 
                // open a new jpg to write to
                jpgFile = fopen(jpgFilename, "w");
                
                // if the file couldn't be created, abort
                if (jpgFile == NULL)
                    return 1;
                
                // write to the new jpg
                fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, jpgFile);
                
                // increment the filenumber of the next image
                jpgCounter++;
            }
        }
        // if there's no new jpg pattern detected, keep writing to current file
        else if (writingToNewFile)
        {
            // continue writing to the created file
            fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, jpgFile);
        }
    }

    // if the last created file is still open, close it
    if (jpgFile)
        fclose(jpgFile);
        
    // closing the forensic image
    fclose(forensicImage);
    
    printf("I've found and restored %i JPG files. You're welcome.\n", jpgCounter);
    
    // that's it!
    return 0;
}

/*
 * Checks if firstBytes matches either pattern1 or pattern2.
 * @param firstBytes Contains the 4 bytes which need to be matched.
 * @param patternOne Contains uint8_t array of size 4 that will be matched against firstBytes.
 * @param patternTwo Contains uint8_t array of size 4 that will be matched against firstBytes.
 * @return True if firstBytes contains either of the two patterns, false if no match is found.
 */
bool isValidPattern(uint8_t firstBytes[], uint8_t patternOne[], uint8_t patternTwo[])
{
    if ((memcmp(patternOne, firstBytes, 4) == 0) || (memcmp(patternTwo, firstBytes, 4) == 0))
        return true;
    return false;
}
