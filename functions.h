
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <utility> // Used utility for pair function std::pair 
#include <string> 
using namespace std;


const int INITIAL_MAX_SIZE = 100; // Initial Array Size
extern int* arr; // Pointer to the array of integers
extern int currentSize; // Current number of elements in the array
extern int currentCapacity; // Current maximum capacity of the array

void doubleArraySize(); // Double size as needed
void loadData(const char* filename); // Read in file
void printArray(); // Display user the array after updating

int find(int num); 
// Using Pair to return two old and new values from a our function 
pair<int, int> modify(int index, int newValue);

bool add(int num); // Add a number, return true if number is successfully added

/* Remove or replace an elemetn at given index.
Remove is true for removal, false for replacing. */
bool removeOrReplace(int index, bool remove = true); 

/* Validate if input is a positive whole number, return true if string is positive whole number
return false otherwise */
bool isPosWholeNum(const string& str);

#endif // FUNCTIONS_H
