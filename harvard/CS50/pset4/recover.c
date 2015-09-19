/*
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
#include <string.h>

#define BLOCKSIZE 512
    
int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    BYTE block[BLOCKSIZE];
     
    // Read through data to recover               
    FILE *inptr = fopen("card.raw", "r");
    
    if (inptr == NULL) 
    {   
         fclose(inptr);
         fprintf(stderr, "Could not open file.");
         return 1;
    }
    
    int count = 0;
    
    FILE *outptr = NULL;
    
    // Loop through contents of file              
    while (fread(block, sizeof(BYTE), BLOCKSIZE, inptr))
    {   
        // Determine if first four bytes are of type JPEG
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            char filename[10];
            
            // Title for JPEG files
            sprintf(filename, "%03d.jpg", count);
            
            // Write recovered JPEG's into new file
            outptr = fopen(filename, "w");
            
            // Increment JPEG counter
            count++;
        }
        
        if (outptr != NULL)
            fwrite(block, sizeof(BYTE), BLOCKSIZE, outptr);
    }
    // Close files
    fclose(outptr);
    fclose(inptr);
}


