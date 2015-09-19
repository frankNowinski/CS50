#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

bool check_key(char *string)
{
    // Confirm key contains only alphabetical characters
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        if (!isalpha(string[i]))
        {
            return false;
        }
    }
    return true;
}

void cipher(int *key, char *string)
{
    // Encode the string with the key 
    if(isupper(*string))
    {
        printf("%c", ((*string - 'A' + *key) % 26 + 'A'));
    }
    else 
    {
        printf("%c", ((*string - 'a' + *key) % 26 + 'a'));
    }
}

void encrypt(char *string, char *key)
{
    int key_index = 0, key_length = strlen(key);

    // Iterate through the users message
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        if (isalpha(string[i]))
        {
            // Store numeric key value; position of key
            int key_value, pos = key_index % key_length;

            // Calculate the key value and encode message
            if (isupper(key[pos]))
            {
                key_value = key[pos] - 'A';
                cipher(&key_value, &string[i]);
            }

            else if (islower(key[pos]))
            {
                key_value = key[pos] - 'a';
                cipher(&key_value, &string[i]);
            }

            // Increment key index
            key_index++;
        }

        // Accomodate spaces
        else if (isspace(string[i]))
        {
            printf("%c", string[i]);
        }

        // Accomodate punctuation
        else
        {
            printf("%c", string[i]);
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

    // Store argument in key 
    char *key = argv[1];

    // Verify check_key returned true
    if (!check_key(key))
    {
        printf("Only alphabetical characters are accepted for the key.\n");
        return 1;
    }

    // Variable to hold the message to encrypt
    char string[140];

    // Get message from user and store in string
    fgets(string, sizeof(string), stdin);

    // Encrypt users message
    encrypt(string, key);

    return 0;  
}
