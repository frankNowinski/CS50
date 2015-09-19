#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

void encrypt (int key, char *string)
{
    // Iterate through the inputted string
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        // Encode each letter of the string with the key
        if (islower(string[i]))
        {
            string[i] = (string[i] - 'a' + key) % 26 + 'a';
        }
        else if (isupper(string[i]))
        {
            string[i] = (string[i] - 'A' + key) % 26 + 'A';
        }
    }
}

int main(int argc, char *argv[])
{
    // Confirm two arguments were given
    if (argc != 2)
    {
        printf("Invalid input: please supply two arguments.\n");
        return 1;
    }

    // Confirm the argument was numeric
    if (isalpha(*argv[1]))
    {
        printf("Only integers are accepted for the second argument.\n");
        return 1;
    }

    // Convert the argument to an integer
    int key = atoi(argv[1]);

    // Variable to hold the message to encrypt 
    char string[50]; 

    // Get message from user
    fgets(string, sizeof(string), stdin);

    // Encrypt message
    encrypt(key, string);

    // Print encrypted message
    printf("%s", string);

    return 0;
}     
