/****************************************************************************
 * dictionary.c
 * 
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
***************************************************************************/ 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Size of hash table
#define SIZE 1000000
	
// Create node 
typedef struct node
{
	char word[LENGTH+1];
	struct node *next;
} node;

// Create hash table
node *hash_table[SIZE];

// Create hash function 
int hash (const char *word)
{
	// Store sum of each individual characters value
	int value = 0;

	for (int i = 0, n = strlen(word); i < n; i++)
	{
		if (isalpha(word[i]))
			value += tolower(word[i]) - 'a';
		else
			value += 26; // Apostrophe
	}
	return value % SIZE;
}

// Count words in the dictionary file
unsigned int dict_size = 0;

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// Load dictionary file
	FILE *file = fopen(dictionary, "r");
	if (file == NULL)
		return false;

	// Create array to store word 
	char word[LENGTH+1];

	// Hash table index
	int bucket;

	// Scan dictionary, loading each new word to the hash table
	while(fscanf(file, "%s\n", word) != EOF)
	{
		// Increment dictionary size
		dict_size++;

		// Allocate memory for new word
		node *new_word = malloc(sizeof(node));

		if (new_word == NULL)
		{
			printf("Error allocating memory.\n");
			fclose(file);
			return false;
		}

		// Copy word to new word
		strcpy(word, new_word->word);

		// Determine what bucket to store new word
		bucket = hash(word);

		// If bucket is empty - insert word
		if (hash_table[bucket] == NULL)
		{
			new_word->next = NULL;
			hash_table[bucket] = new_word;
		}

		// If bucket is not empty - append word
		else
		{
			// Create previous and current node
			node *previous = NULL;
			node *current = hash_table[bucket];

			// Traverse through new_worded listed
			while (current != NULL && current->word > new_word->word)
			{
				previous = current;
				current = current->next;
			}
			new_word->next = current;

			// Insert at the beginning
			if (previous == NULL)
				hash_table[bucket] = new_word;
			// Insert at the middle or the end
			else
				previous->next = new_word;
		}
	}
	// close file
	fclose(file);

	return true;	
} 

/**
 * Returns true if word is in dictionary else false.
 */ 
bool check(const char* word)
{
	// Initiate temporary variable 
	char temp[LENGTH + 1];

	// Word length
	int n = strlen(word);

	// Convert word to lowercase
	for (int i = 0; i < n + 1; i++)
		temp[i] = tolower(word[i]);

	// Set last character to null 
	temp[n] = '\0';

	// Determine hash index
	int bucket = hash(temp);

	// If bucket is empty
	if (hash_table[bucket] == NULL)
		return false;

	// Create node to compare word to 
	node *cursor = hash_table[bucket];

	// Determine if word is spelled correctly
	while (cursor != NULL)
	{
		if (strcmp(cursor->word, temp) == 0)
			return true;
		cursor = cursor->next;
	}
    return false;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dict_size > 0)
    	return dict_size;
 	
 	return 0;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void) 
{
	// Index variable
	int bucket = 0;

	while (bucket < SIZE)
	{
		if (hash_table[bucket] == NULL)
			bucket++;
		else
		{
			while (hash_table[bucket] != NULL)
			{
				// Free memory in each hash index
				node *cursor = hash_table[bucket];
				hash_table[bucket] = cursor->next;
				free(cursor);
			}
			bucket++;
		}
	}
    return true;
}
