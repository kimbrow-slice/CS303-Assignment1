#include "functions.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <fstream>

using namespace std;


int main() {
    // Adding relative path
    string filename = "A1input.txt";
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
    }

    // Load the data from the file 
    loadData(filename.c_str());

    // Declare and initialize varaibles outside the loop

    int action = -1;
    int oldIndex = -1;
    int num;
    int index;
    int newValue;
    int addNum;
    bool isDuplicate = false;
    int userInput;

    while (true) {
        cout << "\nChoose an action: (1) Find, (2) Modify, (3) Add, (4) Remove/Replace, (0) Exit: ";
        cin >> action;

        // Check for non-numeric, negative, and decimal values or an action number outside the bounds.
        if (cin.fail() || action < 0 || action > 4) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input
            cout << "The input must be a positive whole number. Please try again." << endl;
            continue; // Skip the rest of this iteration and prompt again
        }

        if (action == 0) {
            cout << "Exiting program." << endl;
            break; // Exit the program
        }

        try {
            switch (action) {
            case 1: // Find a number and return it's index to the user
            {
                cout << "Please enter a number to find: ";
                cin >> num;
                if (cin.fail() || num <= 0) {
                    cin.clear(); // Clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore subsequent characters
                    cout << "The input must be a positive whole number. Please try again." << endl;
                    continue;
                }

                index = find(num);

                if (index != -1) {
                    cout << "The number " << num << " found at index " << index << "." << endl;
                }
                else {
                    cout << "The number " << num << " was not found, try adding it to the array!" << endl;
                }
                break;
            }
            case 2: // Modify a number at a specific index
            {
                // Prompt the user to input the index of the element they want to modify and the new value
                cout << "Please enter the index you wish to modify: ";
                cin >> index;
                // Error handle for non-positive whole number input
                if (cin.fail() || index <= 0) {
                    cin.clear(); // Clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore subsequent characters
                    cout << "The input must be a positive whole number. Please try again." << endl;
                    continue;
                }

                cout << "Please enter the value you wish to replace it with: ";
                cin >> newValue;
                // Error handle for non-positive whole number input
                if (cin.fail() || newValue <= 0) {
                    cin.clear(); // Clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore subsequent characters
                    cout << "The input must be a positive whole number. Please try again." << endl;
                    continue;
                }

                // Check if the entered index is within the bounds of the array.
                if (index < 0 || index >= currentSize) {
                    cout << "The index you've entered is out of bounds. Please enter a valid index." << endl;
                    break;
                }
                auto modResult = modify(index, newValue);
                if (modResult.first != -1) {
                    // Error handle for non-positive whole number input
                    if (cin.fail() || index <= 0) {
                        cin.clear(); // Clear error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore subsequent characters
                        cout << "The input must be a positive whole number. Please try again." << endl;
                        continue;
                    }
                    cout << "You have modified the index " << index << " from " << modResult.first << " to " << modResult.second << "." << endl;
                    cout << "\nThe array has now been updated!" << endl;
                    printArray();
                }
                else {
                    cout << "The modification you attempted has failed. Double check that the index is within the bounds." << endl;
                }
                break;
            }
            case 3: // Add a number to the end of the array
            {
                cout << "Enter a number to add to the array: ";
                cin >> addNum;

                // Check for duplicates before adding
                for (int i = 0; i < currentSize; ++i) {
                    if (arr[i] == addNum) {
                        // Prompt the user that the number is already in our array. 
                        cout << "The number " << addNum << " already exists in the array. Try adding a different number!" << endl;
                        isDuplicate = true;
                        break; // Duplicate found, exit the loop
                    }
                }

                if (!isDuplicate && add(addNum)) {
                    // Error handle for non-positive whole number input
                    if (cin.fail() || addNum <= 0) {
                        cin.clear(); // Clear error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore subsequent characters
                        cout << "The input must be a positive whole number. Please try again." << endl;
                        continue;
                    }
                    // If a duplicate is not found then add the number to the end of the array. 
                    cout << "You added " << addNum << " successfully!" << endl;
                    cout << "\nThe array has now been updated!" << endl;
                    printArray();
                }

                break;
            }

            case 4: // Remove/Replace a specific index from the array.
            {
                cout << "Please enter the index of the number you want to remove or replace: ";
                cin >> index;
                // Error handle for non-positive whole number input
                if (cin.fail() || index <= 0) {
                    cin.clear(); // Clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore subsequent characters
                    cout << "The input must be a positive whole number. Please try again." << endl;
                    continue;
                }

                // Error handle for if the user trys to write out bounds. 
                if (index < 0 || index >= currentSize) {
                    cout << "Index out of bounds. Please enter a valid index." << endl;
                    break;
                }
                num = arr[index];
                cout << "You have selected to remove/replace the value: " << num << " at index " << index << "!" << endl;


                oldIndex = find(num); // Store the old index of the value before modification

                cout << "Select the following: (0 for remove, 1 for replace): "; // Using newValue as a flag for remove (0) or replace (1)
                cin >> newValue;

                // Error handle for non-positive whole number input
                if (cin.fail() || newValue < 0 || newValue > 1) {
                    cin.clear(); // Clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore subsequent characters
                    cout << "The input must be 0 for remove or 1 for replace. Please try again." << endl;
                    continue;
                }


                if (newValue == 0) {
                    // Shift elements to the left to fill the gap created by the removal
                    for (int i = index; i < currentSize - 1; i++) {
                        arr[i] = arr[i + 1];
                    }
                    --currentSize; // Decrement currentSize after removal
                    cout << "You have removed the " << num << " at index " << index << "." << endl;
                    cout << "The array has now been updated!" << endl;
                    printArray();
                    // If a valid index exists, inform the user of the value and its index prior to deletion.
                    if (oldIndex != -1) {
                        cout << "The value " << num << " was at index " << oldIndex << " before deleting." << endl;
                    }
                }
                else if (newValue == 1) {
                    // Replace the value at index with the user's input.

                    cout << "Enter the new value to replace " << num << " at index " << index << ": ";
                    cin >> userInput;
                    // Error handle for non-positive whole number input
                    if (cin.fail() || userInput <= 0) {
                        cin.clear(); // Clear error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore subsequent characters
                        cout << "Input must be a positive integer. Please try again." << endl;
                        continue;
                    }

                    arr[index] = userInput;

                    cout << "Replaced element at index " << index << " with " << userInput << "." << endl;
                    cout << "\nThe array has now been updated!" << endl;
                    printArray();
                }
                else {
                    cout << "Invalid input for replace option. Please enter 0 for remove or 1 for replace." << endl;
                }

                break;
            }

            case 0: // Exit Program
                cout << "Exiting Program." << endl;
                break;

            default:
                cout << "Invalid action. Please try again." << endl;
                break;
            }
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    return 0;
}

