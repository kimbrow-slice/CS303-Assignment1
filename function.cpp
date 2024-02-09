#include "functions.h"
#include <iostream>
#include <fstream>
#include <string> // For memcpy and isPosWholeNum

using namespace std;

// Global variables for array management 
int* arr = new int[INITIAL_MAX_SIZE]; // Point to array
int currentSize = 0; // Initial size of array
int currentCapacity = INITIAL_MAX_SIZE; // Current Max Capacity 

// Function to double the size of the array when the current capacity is reached
void doubleArraySize() {
    int newCapacity = currentCapacity * 2;
    int* newArr = new int[newCapacity];
    memcpy(newArr, arr, currentSize * sizeof(int)); // Copy old elements to new array

    delete[] arr; // Free the old array
    arr = newArr; // Update the pointer to the new array
    currentCapacity = newCapacity; // Update the current capacity
}

// Function to load data from file into array
void loadData(const char* filename) {
    ifstream file(filename);
    int value;
    while (file >> value) { // Read in integers from file
        if (currentSize >= currentCapacity) {
            doubleArraySize(); // Double the array size if maximum capacity is reached
        }
        arr[currentSize++] = value; // Add value to the array
    }
    file.close();
}

/* Function to print all numbers in the array. This was used to show the user the updated array after 
making modifications to the data */
 
void printArray() {
    for (int i = 0; i < currentSize; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to find the index of a given number in our array
int find(int num) {
    for (int i = 0; i < currentSize; ++i) {
        if (arr[i] == num) return i;
    }
    return -1;
}

// Function to modify the value within the array at a given index and return both old and new values
pair<int, int> modify(int index, int newValue) {
    if (index < 0 || index >= currentSize) {
        cout << "Index out of bounds." << endl; 
        return { -1, -1 }; // Return error if index is out of bounds
    }
    int oldValue = arr[index]; // Store old value
    arr[index] = newValue; // Update value at given index
    return { oldValue, newValue }; // Return old and new valyue
}

// Function to add a number into the array
bool add(int num) {
    if (currentSize >= currentCapacity) {
        doubleArraySize(); // Double the array size if maximum capacity is reached
    }
    arr[currentSize++] = num; // Add number to the and post increment current size
    return true; // Successful addition to the array
}

// Function either remove or replace a value at given index 
bool removeOrReplace(int index, bool remove) {
    if (index < 0 || index >= currentSize) {
        cout << "Index out of bounds." << endl;
        return false; // Return error if index is out of bounds
    }
    if (remove) {
        for (int i = index; i < currentSize - 1; ++i) {
            arr[i] = arr[i + 1]; // Shift elements to fill the gap from removing
        }
        --currentSize; // Decrement the current size
    }
    else {
        arr[index] = 0;
    }
    return true; // Successfully removed or replaced
}

// Function to check if a string represents a positive whole number
bool isPosWholeNum(const string& str) {
    if (str.empty()) return false; // Check for empty string
    for (char c : str) {
        if (isdigit(c)) return false; // Return false if input is not a digit
    }
    return true; // User input is a positive whole number
}
