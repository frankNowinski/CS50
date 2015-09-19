/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

// Searching algorithms
bool binary_search(int value, int array[], int size);
bool linear_search (int value, int array[], int size);
bool recursive_search(int value, int array[], int start, int end);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

// Sorting algorithms
void selection_sort(int array[], int size);
void bubble_sort(int array[], int size);


