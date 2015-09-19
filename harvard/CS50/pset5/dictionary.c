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
#define SIZE 27
	
// Create node 
typedef struct node
{
	bool is_word;
	struct node *children[SIZE];
} node;

// Create root pointer
node *root;

unsigned int dict_count = 0;

// Free memory prototype
bool free_memory(node *node);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// Load dictionary
	FILE *file = fopen(dictionary, "r");
	if (file == NULL)
	{
		printf("Error opening dictionary.\n");
		fclose(file);
		return false;
	}

	// Create character variables
	char word[LENGTH+1], current_char;

	// Create index variables
	int index = 0, child_index = 0;

	// Allocate memory for root node
	root = calloc(1, sizeof(node));

	// Iterate through the dictionary until it has reached the end of the file
	for (int c = fgetc(file); c != EOF; c = fgetc(file))
	{
		// We have reached a new line, or more likely, a new word
		if (c == '\n')
		{
			// Increment dictionary size
			dict_count++;

			// Current position - initialize current_node
			word[index] = c;
			node *current_node = root;

			// Iterate through characters
			for (int i = 0; i <= index; i ++)
			{
				// Current character is the ith letter in the word
				current_char = word[i];

				// If an alphabetical character
				if (isalpha(current_char))
				{
					// Designate current index
					child_index = tolower(current_char) - 'a';

					if (current_node->children[child_index] == NULL)
					{
						// Allocate memory for current node 
						current_node->children[child_index] = (node*) calloc(1, sizeof(node));

						if (current_node->children[child_index] == NULL)
						{
							printf("Error allocating memory");
							fclose(file);
							return false;
						}
					}
					current_node = current_node->children[child_index];
				}

				// Encountered apostrophe
				else if (current_char == '\'')
				{
					if (current_node->children[SIZE - 1] == NULL)
					{
						// Allocate memory for apostrophe
						current_node->children[SIZE - 1] = (node*) calloc(1, sizeof(node));

						if (current_node->children[SIZE - 1] == NULL)
						{
							printf("Error allocating memory");
							fclose(file);
							return false;
						}
					}
					current_node = current_node->children[SIZE - 1];
				}
				else if (current_char == '\n')
				{
					// Found word
					current_node->is_word = true;
				}
			}
			index = 0;
		}
		else 
		{
			// Update word until reach 
			word[index] = c;
			index++;
		}
	}
	// Close file
	fclose(file);

	return true;
}


/**
 * Returns true if word is in dictionary else false.
 */ 
bool check(const char* word)
{
	// Store current character
	char current_char;

	// Store children index
	int index = 0;
	int child_index = 0;

	node *current_node = root;
	if (current_node == NULL)
	{
		printf("Error with current_node");
		return false;
	}

	while (word[index] != '\0')
	{
		// Store current character
		current_char = word[index];

		// Store index of current character
		if (isalpha(current_char))
			child_index = tolower(current_char) - 'a';

		else if (word[index] == '\'')
			child_index = SIZE - 1;

		// If any other character, word is invalid
		else 
			return false;

		// Unable to find the word in the dictionary
		if (current_node->children[child_index] == NULL)
			return false;
		else
			current_node = current_node->children[child_index];

		// Increment index
		index++;
	}

	if (current_node->is_word == true)
		return true;
	else
		return false;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
	if (dict_count > 0)
		return dict_count;
 	return false;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void) 
{
	if (free_memory(root))
		return true;
	return false;
}

bool free_memory(node *node)
{
	// Iterate through trie and free root node memory
	for (int i = 0; i < SIZE; i++)
	{
		if (node->children[i] != NULL)
			free_memory(node->children[i]);
	}
	free(node);

	return true;
}









