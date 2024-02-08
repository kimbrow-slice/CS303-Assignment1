#include "functions.h"
#include <iostream>
#include <fstream>
#include <string> // For memcpy and isPosWholeNum

using namespace std;

int* arr = new int[INITIAL_MAX_SIZE];
int currentSize = 0;
int currentCapacity = INITIAL_MAX_SIZE;

void doubleArraySize() {
    int newCapacity = currentCapacity * 2;
    int* newArr = new int[newCapacity];
    memcpy(newArr, arr, currentSize * sizeof(int)); // Copy old elements to new array

    delete[] arr; // Free the old array
    arr = newArr; // Update the pointer to the new array
    currentCapacity = newCapacity; // Update the current capacity
}

void loadData(const char* filename) {
    ifstream file(filename);
    int value;
    while (file >> value) {
        if (currentSize >= currentCapacity) {
            doubleArraySize(); // Double the array size if maximum capacity is reached
        }
        arr[currentSize++] = value;
    }
    file.close();
}

void printArray() {
    for (int i = 0; i < currentSize; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int find(int num) {
    for (int i = 0; i < currentSize; ++i) {
        if (arr[i] == num) return i;
    }
    return -1;
}

pair<int, int> modify(int index, int newValue) {
    if (index < 0 || index >= currentSize) {
        cout << "Index out of bounds." << endl;
        return { -1, -1 };
    }
    int oldValue = arr[index];
    arr[index] = newValue;
    return { oldValue, newValue };
}

bool add(int num) {
    if (currentSize >= currentCapacity) {
        doubleArraySize(); // Double the array size if maximum capacity is reached
    }
    arr[currentSize++] = num;
    return true; // Successful addition
}

bool removeOrReplace(int index, bool remove) {
    if (index < 0 || index >= currentSize) {
        cout << "Index out of bounds." << endl;
        return false;
    }
    if (remove) {
        for (int i = index; i < currentSize - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --currentSize;
    }
    else {
        arr[index] = 0;
    }
    return true;
}

bool isPosWholeNum(const string& str) {
    if (str.empty()) return false; // Ensure empty string is not a positive whole number
    for (char c : str) {
        if (isdigit(c)) return false; // Check each character in string
    }
    return true;
}
