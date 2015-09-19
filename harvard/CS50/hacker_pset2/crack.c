#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// 50q.zrL5e0Sak  50yoN9fp966dU

#define _XOPEN_SOURCE

#define CHARPOOL_MIN = 32;
#define CHARPOOL_MAX = 126;
#define CHARPOOL_SIZE = (CHARPOOL_MAX - CHARPOOL_MIN) + 1;

// Define constants
const int WORD_SIZE = 128;
const int MAX_PASSWD_SIZE = 8;

int seconds; // Calculate number of seconds to crack

bool attempt_crack(const char *word, const char *hash, const char *salt)
{
	// Compare the encrpytion of the word in question to the hash given 
	if(!strcmp(crypt(word, salt), hash))
	{
		printf("The password was cracked!\nUsers Password: %s\n", word);
		printf("Seconds to crack: %.2d\n", (int) time(NULL) - seconds);

		return true;
	}
	return false;
}

bool dict_attack(char *hash, char *salt)
{
	// Store current 
	char cur_word[WORD_SIZE];

	// Path to dictionary
	FILE *file = fopen("/users/frank/harvard/5pset/words", "r");

	// Exit program if unable to access dictionary
	if (!file)
	{
		printf("Error opening dictionary file.\n");
		return 1;
	}

	// Iterate over each word in dictionary
	while (fgets(cur_word, WORD_SIZE, file))
	{
		// Set last charachter to null terminator
		cur_word[strlen(cur_word) - 1] = '\0';

		// Try current word
		if (attempt_crack(cur_word, hash, salt))
		{
			return true;
		}
	}
	return false;
}

bool brute_force(const char *hash, const char *salt)
{
	// Array to store all possible hash charachters 
	char possible_chars[] = { "0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz!#$&()*+,-./:;<=>?@[]^_`{|}~" };

	// Lenght of array; store index of the hash
	int arr_length = strlen(possible_chars);
	int pos[MAX_PASSWD_SIZE];

	char cur_word[MAX_PASSWD_SIZE + 1];

	// Set last charachter to null terminator 
	cur_word[MAX_PASSWD_SIZE] = '\0';

	// Iterate through length of the hash - 8 charachters
	for (int max_chars = 0; max_chars < MAX_PASSWD_SIZE; max_chars++)
	{
		printf("Trying length %d\n", max_chars + 1);

		bool loop_completed = false;

		// // Initialize current word
		int index;

		// Iterate through possible charachters
		for (index = 0; index <= max_chars; index++)
		{
			pos[index] = 0;
			cur_word[index] = possible_chars[pos[index]];
		}

		cur_word[index] = '\0';

		// Checks every symbol combination
		while(!loop_completed)
		{
			if (attempt_crack(cur_word, hash, salt))
			{
				return true;
			}

			bool shift = true;

			for (int cur_char = 0; cur_char <= max_chars; cur_char++)
			{
				// Shift to the next charachter when shift is true
				if(shift)
				{
					// If all charachters are checked
					if (pos[cur_char] == arr_length - 1)
					{
						// Loop is over
						if (cur_char == max_chars)
						{
							loop_completed = true;
						}

						else
						{
							pos[cur_char] = 0;
							cur_word[cur_char] = possible_chars[pos[cur_char]];
						}

					}
				}
				else
				{
					cur_word[cur_char] = possible_chars[++pos[cur_char]];
					shift = false;
				}
			}

		}
	}
	return false;
}

int main(int argc, char *argv[])
{
	// Confirm encrypted password was supplied
	if (argc != 2)
	{
		printf("Please enter hash.\n");
		return 1;
	}

	// Store hashed password
	char *hash = argv[1];

	// Monitor time it took to crack
	seconds = time(NULL);

	// Extract salt
	char salt[2];
	strncpy(salt, hash, 2);

	printf("Implementing dictionary attack...\n\n");

	// Dictionary attack
	if (dict_attack(hash, salt))
	{
		return 0;
	}

	printf("Dictionary attack failed. Implementing brute force...");

	if (brute_force(hash, salt))
	{
		return 0;
	}

	printf("Encrypted password could not be deciphered.\n");

	return 0;

}
