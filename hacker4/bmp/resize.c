/****************************************************************************
 * resize.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Hacker 4
 *
 * Resizes (either larger or smaller) a BMP file with float factor.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>
#include "bmp.h"

// function prototypes
int resizeLarger(FILE* inptr, FILE* outptr, double factor);
int resizeSmaller(FILE* inptr, FILE* outptr, float factor);

int main(int argc, char* argv[])
{
    // start counting running time of program
    clock_t startTime, endTime, totalTime;    
    startTime = clock();
    
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: copy factor[0-100] infile outfile\n");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // if either the infile or the outfile does not end with .bmp, abort
    if (strstr(infile, ".bmp") == 0)
    {
        printf("Infile does not have a .bmp extension. Aborting.\n");
        return 1;
    }
    else if (strstr(outfile, ".bmp") == 0)
    {
        printf("Outfile does not have a .bmp extension. Aborting.\n");
        return 1;
    }
    
    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    
    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // check if input is valid
    if (!atof(argv[1]))
    {
        printf("The factor must be a float or integer.\n");
        return 4;
    }
    else if (atof(argv[1]) <= 0 || atof(argv[1]) >= 100)
    {
        printf("The factor must be of type float or integer and larger than zero and smaller or equal to 100. Aborting.\n");
        return 5;
    }
    
    // input factor to multiply image dimensions with
    float factor = atof(argv[1]);
    
    // let's start resizing the image in separate function assigned for each type of resizing
    if (factor >= 1.0)
    {
        if(resizeLarger(inptr, outptr, factor) != 0)
        {
            printf("An error occured during the resize process. Aborting.\n");
            return 6;
        }
    }
    else if (factor < 1.0)
    {
        if(resizeSmaller(inptr, outptr, factor) != 0)
        {
            printf("An error occured during the resize process. Aborting.\n");
            return 6;
        }
    }
    
    // display rounded factor
    printf("Image resized with factor: %.4f (rounded).\n", factor);
    
    // close infile
    fclose(inptr);
    
    // close outfile
    fclose(outptr);
    
    // temporary storage for filesize
    struct stat st;
    
    // calculate bytesize for infile
    stat(infile, &st);
    int originalSizeInBytes = st.st_size;
     
    // calculate bytesize of outfile
    stat(outfile, &st);
    int resizedSizeInBytes = st.st_size;
    
    // convert bytes to megabytes
    int originalSizeInMB = (originalSizeInBytes / 1024) / 1024; 
    int resizedSizeInMB = (resizedSizeInBytes / 1024) / 1024;
    
    // stop the running time counter
    endTime = clock();
    // calculate final run time in seconds
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    
    // print to the user some fun stats
    printf("Original image is about %i megabytes.\n", originalSizeInMB);
    printf("Resized image is about %i megabytes.\n",  resizedSizeInMB);
    printf("Of course, you already knew that! Or didn't you?\n");
    
    // check if singular or plural
    char* secondCorrectVerb = (totalTime == 1) ? "second" : "seconds";   
    printf("Anyway, the resizing process took just %ld %s.\n", totalTime, secondCorrectVerb);

    // if we made it this far, assume no errors, yay!
    return 0;
}

/*
 * Resizes The input image larger with a given factor between 1 and 100 and stores it in another file.
 * @param inptr File pointer to the original image that is being resized.
 * @param outptr File pointer to the newly created resized image.
 * @param factor Input factor between 1 and 100 with which the original image is being resized.
 * @return resize Returns 0 if no errors occurred, or !0 if errors occurred.
 */
int resizeLarger(FILE* inptr, FILE* outptr, double factor)
{
    // double check the input factor
    if (factor < 1.00 || factor > 100.00)
    {
        printf("The resizeLarger() function only handles values larger than 0 and smaller than 1. Aborting.\n");
        return 9;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // store the originalBiHeight and originalBiWidth of the original image
    // so we can use it later on
    int originalBiHeight = bi.biHeight;
    int originalBiWidth = bi.biWidth;
    
    // overwrite the BITMAPINFOHEADER values for biWidth & biHeight   
    bi.biWidth = ceil(originalBiWidth * factor); // new Width is original width of the infile times the input factor
    
    // if originalBiHeight is negative, ceil rounds (e.g.) -2.3 to -2, while we would expect -3, so we floor instead
    bi.biHeight = (originalBiHeight >= 0) ? ceil(originalBiHeight * factor) : floor(originalBiHeight * factor); // new Height is original height of the infile times the factor

    // determine padding for scanlines
    int originalPadding =  (4 - (originalBiWidth * sizeof(RGBTRIPLE)) % 4) % 4; // padding in the original file
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // padding in the to be resized file
    
    // calculate biSizeImage for to be resized image. biHeight can be negative so with abs() we make it positive.
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof(RGBTRIPLE)) + padding); // width times the size of each RGBTRIPLE plus the padding at the end of line
    
    // calculate bfSize for to be resized image. This is equal to the biSizeImage of the same file, plus the size of the two HEADERs
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
     
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 7;
    }
    
    // write outfile's BITMAPFILEHEADER using the new values we assigned earlier
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER using the new values we assigned earlier
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // float that stores the size of each vertical step
    float fractionOfLinesHeight = factor;
    
    // float that stores the size of each horizontal step
    float fractionOfLinesWidth = factor;

    // declare a float that stores the initial vertical location
    float verticalLocation = 0.00;
    
    // int that holds initial number of vertical lines that are skipped
    int numOfVerticalLines = 0;
    
    // int that holds initial vertical step size
    int verticalStep = 0;
        
    // iterate vertically until i matches originalBiHeight of infile divided by size of each vertical step
    // we use abs() here because according to MSDN specification the height can be negative
    for (int i = 0, newBiHeight = ceil(abs(originalBiHeight) * factor); i < newBiHeight; i++)
    {         
        // stores the ceil of current verticalLocation plus the size of each extra step (e.g. fractionOfLinesHeight),
        // minus previous ceiled value of verticalLocation (which is set in previous iteration)
        verticalStep = (ceil(verticalLocation + fractionOfLinesHeight) - ceil(verticalLocation));      
 
        // declare a float that stores the initial horizontal location (reset to 0.00 when next line is reached)
        float horizontalLocation = 0.00;
     
        // iterate horizontally until j matches originalBiWidth of infile divided by size of each horizontal step
        for (int j = 0; j < originalBiWidth; j++)
        {
            // stores the ceiled value of current horizontalLocation plus the size of each extra step (fractionOfLinesWidth),
            // minus previous ceiled horizontalLocation (which is set in the previous iteration)
            int horizontalStep = (ceil(horizontalLocation + fractionOfLinesWidth) - ceil(horizontalLocation));           
            
            // temporary storage for each pixel that consists of Red, Green and Blue
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // for each RGBTRIPLE in the original file, write horizontalStep times as much RGBTRIPLEs
            for (int k = 0; k < horizontalStep; k++)
                // write RGB triples to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
           
            // new horizontalLocation is equal to current horizontalLocation plus the size of each extra horizontal step (fractionOfLinesWidth)
            horizontalLocation += fractionOfLinesWidth;
        }
        
        // skip over padding in the original image, if any
        fseek(inptr, originalPadding, SEEK_CUR);
        
        // then add the padding back
        for (int k = 0; k < padding; k++)
            fputc(0x00, outptr);   
        
        // the size of each line in bytes
        int originalLineSizeInBytes = ((originalBiWidth * sizeof(RGBTRIPLE)) + originalPadding);
        
        if (numOfVerticalLines <= verticalStep)
        {
            // skip one line back
            fseek(inptr, -originalLineSizeInBytes, SEEK_CUR);
            
            // increment the amount of verticalLines that have been duplicated
            numOfVerticalLines++;
        }

        // if the number of verticalLines needed to be duplicated is done, reset
        if (numOfVerticalLines == verticalStep)
        {
            numOfVerticalLines = 0;
            fseek(inptr, originalLineSizeInBytes, SEEK_CUR);
        }
        
        // new verticalLocation is equal to current verticalLocation plus size of each extra vertical step (fractionOfLinesHeight)
        if (numOfVerticalLines == 0)
            verticalLocation += fractionOfLinesHeight;
    }
    
    // This pset was by far the hardest one til now, but we did alright, so let's return 0
    return 0;
}

/*
 * Resizes the input image smaller with a given factor larger than 0 and smaller than 1 and stores it in another file.
 * @param inptr File pointer to the original image that is being resized.
 * @param outptr A file pointer to the newly created resized image.
 * @param factor The input factor with which the original image is being resized.
 * @return resize Returns 0 if no errors occurred, or !0 if errors occurred.
 */
int resizeSmaller(FILE* inptr, FILE* outptr, float factor)
{   
    // double check that we can work with this factor
    if (factor <= 0.00 || factor >= 1.00)
    {
        printf("The resizeSmaller() function only handles values larger than 0 and smaller than 1. Aborting.\n");
        return 10;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // store the originalBiHeight and OriginalBiWidth of the original image
    // so we can use it later on
    int originalBiHeight = bi.biHeight;
    int originalBiWidth = bi.biWidth;
    
    // overwrite the BITMAPINFOHEADER values for biWidth & biHeight   
    bi.biWidth = ceil(originalBiWidth * factor); // new Width is original width of the input file times the input factor
    // if originalBiHeight is negative, ceil rounds (e.g.) -2.3 to -2, while we would expect -3, so we floor instead
    bi.biHeight = (originalBiHeight >= 0) ? ceil(originalBiHeight * factor) : floor(originalBiHeight * factor); // new Height is original height of original times the factor

    // determine padding for scanlines
    int originalPadding =  (4 - (originalBiWidth * sizeof(RGBTRIPLE)) % 4) % 4; // padding in the original file
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // padding in the to be resized file
    
    // calculate biSizeImage for to be resized image. biHeight can be negative so with abs() we make it positive.
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof(RGBTRIPLE)) + padding); // width times the size of each RGBTRIPLE plus the padding at the end of line
    
    // calculate bfSize for to be resized image. This is equal to the biSizeImage of the same file, plus the size of the two HEADERs
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 7;
    }
    
    // write outfile's BITMAPFILEHEADER using the new values we assigned earlier
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER using the new values we assigned earlier
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over each horizontal line of the infile (original file)
    for (int j = 0, originalBiHeightWithAbs = abs(originalBiHeight); j < originalBiHeightWithAbs; j++)
    {
        // if the ceiled product of iteration count and factor are not equal to the next iteration's
        // product of the same factors, vertical line needs to be included in the outfile
        if ( ceil(j * factor) != ceil((j+1) * factor) )
        {     
            // iterate over each pixel in the width of the infile (original file)        
            for (int i = 0; i < originalBiWidth; i++)
            {   
                // same as above, but now considering horizontal iteration count
                if (ceil(i * factor) != ceil((i+1) * factor))
                {
                    // temporary storage for triple
                    RGBTRIPLE triple;
                    
                    // read one pixel (aka 1 RGBTRIPLE) from the infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    
                    // write one pixel to the outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                else if (ceil(i * factor) == ceil((i+1) * factor))
                {
                    // skip over 1 pixel
                    fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);
                }
            }
            
            // skip over the padding in the infile
            fseek(inptr, originalPadding, SEEK_CUR);
            
            // add it back to the outfile
            for (int k = 0; k < padding; k++)
                fputc(0x00, outptr); // each byte of padding consists of 2 zero's, in hex
        }
        else if (ceil(j * factor) == ceil((j+1) * factor))
        {
            // skip over 1 horizontal line
            // line size in bytes is the product of amount of pixels times size of each pixel (3 or size of RGBTRIPLE)
            // finally add padding, if any exists in the original file
            fseek(inptr, (sizeof(RGBTRIPLE) * abs(originalBiWidth) + originalPadding), SEEK_CUR);
        }
    }
    
    // no errors occurred during the resize process
    return 0;
}
