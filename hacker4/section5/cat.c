/****************************************************************************
 * cat.c
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 *
 * Displays contents of file char by char while user inputs random values.
 ***************************************************************************/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: cat filename [filename ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        // TODO: open argv[i] and print its contents to stdout
        FILE* fp;
        
        fp = fopen(argv[i], "r");
        
        if (fp == NULL)
        {
            printf("file not readable\n");
            return 1;           
        }
        
        struct termios current_settings, hacker_settings;
        
        // save current settings
        tcgetattr(0, &current_settings);
        hacker_settings = current_settings;
        
        hacker_settings.c_lflag &= ~(ECHO | ICANON);
        hacker_settings.c_cc[VTIME] = 0;
        hacker_settings.c_cc[VMIN] = 1;
        
        // update hacker_settings
        tcsetattr(0, TCSANOW, &hacker_settings);    
      
        for (int c = fgetc(fp); c != EOF; c= fgetc(fp))
        {
            fgetc(stdin);
            putchar(c);
        }
        
        // restore normal settings
        tcsetattr(0, TCSANOW, &current_settings);
    
        fclose(fp);
    }

    return 0;
}
