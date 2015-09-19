#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // Store users name
    char name[50];

    // Prompt user for name
    printf("What is your name?\n");
    fgets(name, sizeof(name), stdin);

    printf("Initials: ");

    // Capitalize and print first initial if it is not a space
    if (name[0] != ' ') printf("%c", toupper(name[0]));
    
    // Capitalize and print each character following a space 
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (isalpha(name[i]) && isspace(name[i-1]))
        {
            printf("%c", toupper(name[i]));
        }
    }

    // New line
    printf("\n");

    return 0;
}


