/****************************************************************************
 * cp.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Creates a copy of source file and saves it at destination.
 ***************************************************************************/

#include <stdio.h>

#define SIZE (1024*1024)

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: cp source destination\n");
        return 1;
    }

    // TODO: copy the contents of argv[1] to argv[2]
    FILE* fp = fopen(argv[1], "r");
    FILE* fcp = fopen(argv[2], "w+");
    
    if (fp == NULL || fcp == NULL)
        return 1;
    
    char *buffer[SIZE];
    size_t bytes;
    
    while((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0)
        fwrite(buffer, 1, bytes, fcp);
    
    fclose(fp);
    
    return 0;
}

