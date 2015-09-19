#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

long long get_card_number(long long card_number)
{
	bool get_number = false;

	// Prompt user for credit card number
	printf("Enter Credit Card number: ");
	scanf("%lld", &card_number);

	// Return true if the inputted value adheres to required length
	get_number = (card_number == 13 || card_number == 15 || card_number == 16) ?
		true : false;

	return card_number;
}

int sum_digits(int product)
{
	// Add the digit in the tens place to the digit in the singles place
	return (product / 10) + (product % 10);
}

// Use Luhn’s algorithm to determine if the card number is valid
bool card_valid(char *card_number)
{
	bool card_valid = false;

	// Initialize variables
	int sum, digit;

	// Iterate over the length of the credit card number
	for (int i = 0, n = strlen(card_number); i < n; i++)
	{
		digit = card_number[i] - '0';

		// Add individual credit card numbers 
		// Odd lengthed credit card number 
		if (n % 2 != 0)
		{
			sum += (i % 2 != 0) ? sum_digits(digit * 2) : digit;
		}

		// Even lengthed credit card number
		else
		{
			sum += (i % 2 == 0) ? sum_digits(digit * 2) : digit;
		}
	}

	// Card is valid if the sum of the credit cards digits is evenly divisible by 10 
	if (sum % 10 == 0)
	{
		printf("Status: Valid\n");
		return true;
	}
	else
	{
		printf("Invalid credit card number.\n"); 
		return false;
	}
}

int main(void)
{
	// Store credit card number	
	long long card_number;
	card_number = get_card_number(card_number);

	// Convert card_number to string
	char card_str[17];
	sprintf(card_str, "%lld", card_number);

	// Variable to store credit card company
	char *card;

	// Aesthetic top border
	printf("-----------------------------\n");

	// Execute the following if the credit card is valid
	if (card_valid(card_str))
	{
		// Evaluate the first two digits to determine credit card company
		if (card_str[0] == '3' && (card_str[1] == '4' || card_str[1] == '7'))
		{
			card = "American Express";
		}
		
		else if (card_str[0] == '5' && (card_str[1] >= 1 && card_str[1] <= 5))
		{
			card = "Mastercard";
		}

		else if (card_str[0] == '4')
		{
			card = "Visa";
		}

		// Print credit card company 
		printf("Credit Card: %s\n", card);
	}

	// Aesthetic bottom border
	printf("-----------------------------\n");
}
