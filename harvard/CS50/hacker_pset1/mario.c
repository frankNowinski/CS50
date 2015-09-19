#include <stdio.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // Initialize height variable
    int height;

    // Prompt user for height
    do
    {
        printf("Enter height between 1 - 23: ");
        scanf("%i", &height);
    }
    while (height < 0 || height > 23);
    
    // Iterate over rows in pyramid
    for (int i = 0; i < height; i++)
    {
        // Spaces per row
        for (int x = 0; x < (height - i + 1); x++)
        {
            printf(" ");
        }

        // # per row
        for (int y = 0; y <= i; y++)
        {
            printf("#");
        }

        // Insert space between pyramids
        printf("  ");

        // Construct second pyramid
        for (int z = 0; z <= i; z++)
        {
            printf("#");
        }

        // New row
        printf("\n");
    }

    return 0;
}






