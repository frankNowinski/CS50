#include <stdio.h>
#include <math.h>
#include <cs50.h>

int get_coins (int *change, int value)
{
    // Calculate maximum number of coins per amount of change
    int coin = *change / value;

    // Update leftover change
    *change = *change % value;
    
    // Return amount of coins
    return coin;
}

int main(int argc, char *argv[])
{
    // Store users change in a float
    float change;
  
    // Continuously prompt user until a non-negative value less than 1 is inputted 
    do
    {
        printf("Oh hai! How much change is owed: ");
        scanf("%f", &change);
    }  
    while (change <= 0.0 || change >= 1.0);

    // Convert float to integer
    int total_change = round(change * 100);

    // Coin variables/total amount of coins owed
    int quarters, dimes, nickels, pennys, total_coins = 0;

    quarters = total_coins + get_coins(&total_change, 25);  
    dimes = total_coins + get_coins(&total_change, 10);    
    nickels = total_coins + get_coins(&total_change, 5);    
    pennys = total_coins + get_coins(&total_change, 1); 

    // Amount of coins owed
    total_coins = quarters + dimes + nickels + pennys;

    printf("\nQuarters: %i\nDimes: %i\nNickels: %i\nPennys: %i\nTotal coins owed: %i\n", 
        quarters, dimes, nickels, pennys, total_coins);

    return 0;
}
