#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <utility>
#include <string>
using namespace std;

// Initial Array Size
const int INITIAL_MAX_SIZE = 100;
extern int* arr;
extern int currentSize;
extern int currentCapacity;

void doubleArraySize();
void loadData(const char* filename);
void printArray();
int find(int num);
// Using Pair to return two old and new values from a our function 
pair<int, int> modify(int index, int newValue);
bool add(int num);
bool removeOrReplace(int index, bool remove = true);
bool isPosWholeNum(const string& str);

#endif // FUNCTIONS_H