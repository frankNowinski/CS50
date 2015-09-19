/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <string.h>
#include "helpers.h"
#include <stdio.h>

// Declare prototypes
bool binary_search(int value, int array[], int size);
void selection_sort(int array[], int size);

/**
* Returns true if value is in array of n values, else false.
*/

bool search(int value, int array[], int size)
{
    // Confirm array holds more than 1 element
    if (size < 2)
        return false;
    else
        return binary_search(value, array, size);
}

bool binary_search(int value, int array[], int size)
{
    // Set upper and lower bounds
    int lower = 0, upper = size - 1;

    while (lower <= upper)
    {
        // Store middle value
        int middle = (lower + upper) / 2;

        // Break out of while loop if value is found
        if (value == array[middle])
            return true;
        else if (value > array[middle])
            lower = middle + 1;
        else
            upper = middle - 1;
    }
    // Unable to find value
    return false;
}

/**
* Sorts array of n values.
* Selection sort.
*/

void sort(int array[], int size)
{
    selection_sort(array, size);
    return;
}

void selection_sort(int array[], int size)
{
    // Iterate through array
    for (int i = 0; i < size - 1; i++)
    {
        int smallest = 0;

        for (int j = i + 1; j < size; j++)
        {
            // Swap if encounter smaller element
            if (array[j] < array[smallest])
                smallest = j;
        }
        int temp = array[smallest];
        array[smallest] = array[i];
        array[i] = temp;
    }
}

/**
* Additional search and sort implementations not used 
* directly in this pset but were written solely 
* for practice
*/

// Declare prototypes
bool linear_search(int value, int array[], int size);
bool recurisve_search(int value, int array[], int start, int end);
void bubble_sort(int array[], int size);

bool linear_search (int value, int array[], int size)
{
    // Iterate through the array until the value is found
    for (int i = 0; i < size; i++)
    {
        if (value == array[i]) 
            return true;
    }
    // Unable to locate value
    return false;
}

bool recursive_search(int value, int *array, int start, int end)
{
    // Found needle 
    if (value == array[(start+end)] / 2) 
        return true;

    while (start <= end)
    {
        // Declare middle variable  
        int middle = (start + end) / 2;

        // Recursively search left/right portion of the array
        if (value > array[middle])
            return recursive_search(value, array, middle + 1, end);
        else
            return recursive_search(value, array, start, middle - 1);
    }
    // Unable to locate value
    return false;
}

void bubble_sort(int array[], int size)
{
    // Iterate through array
    for (int k = 0; k < size-1; k++)
    {
        // Initialize swaps variable
        int swaps = 0;

        for (int i = 0; i < size-1-k; i++)
        {
            // Switch adjacent elements if they are out of order
            if (array[i] > array[i+1])
            {
                int temp = array[i+1];
                array[i+1] = array[i];
                array[i] = temp;
                swaps++;
            }
        }

        // Bubble sort is complete if there are no swaps
        if (!swaps)
            break;
    }
}
