#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <unordered_map>

using namespace std;

string digits[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

unordered_map<string, int> digitsMap = { 
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9}};

int main()
{
	// Get input.txt filepath
	char filepath[FILENAME_MAX];
	GetCurrentDirectoryA(sizeof(filepath), filepath);
	strcat_s(filepath, "\\input.txt");

	// Log filepath
	cout << filepath << endl;

	// Create ifstream object for reading input.txt
	ifstream ifs(filepath);

	// Check if input.txt opened successfully
	if (!ifs.is_open())
	{
		// Log error and exit if unsuccessful
		cout << "failed to open input.txt" << endl;
		return 0;
	}

	// File opened successfully, declare required variables
	int result = 0;
	string line;

	// Read all lines
	while (getline(ifs, line))
	{
		// Declare temporary variables used to find first and last digits in both numerical and written form (e.g. "1" and "one")
		int first_digit = 0;
		int second_digit = 0;
		size_t lowestFirstIndex = line.length();
		size_t heighestSecondIndex = 0;

		// First, search for first and last written form digit
		for (int i = 0; i < 9; i++)
		{
			// Find the written form digit in the digitsMap unordered map
			auto digitsMapIterator = digitsMap.find(digits[i]);

			// Find the first index of the current digit
			size_t index1 = line.find(digits[i]);
			// Compare the found index to any previously found index
			// if it's less, that means it's actually the first written digit in the string
			if (index1 != string::npos && index1 <= lowestFirstIndex)
			{
				// Store the index as the new lowest index for future comparisons
				lowestFirstIndex = index1;
				first_digit = digitsMapIterator->second;
			}

			// Find the last index of the current digit
			size_t index2 = line.rfind(digits[i]);
			// Compare the found index to any previously found index
			// if it's greater, that means it's actually the last written digit in the string
			if (index2 != string::npos && index2 >= heighestSecondIndex)
			{
				// Store the index as the new height index for future comparisons
				heighestSecondIndex = index2;
				second_digit = digitsMapIterator->second;
			}
		}

		// Second, search for first and last numerical digit
		
		// Declare temporary variables used to find first and last digit
		bool first_found = false;
		int index = -1;

		// Iterate over string
		for (char& c : line)
		{
			// Record our index
			index++;

			// Check if it's a numerical digit, if not, continue to next character
			if (!isdigit(c))
			{
				continue;
			}

			// Update first digit to numerical digit, if it's index is lower than the written digit index
			if (!first_found)
			{
				if (index <= lowestFirstIndex)
				{
					first_digit = c - '0';
				}

				first_found = true;
			}

			// Update the second digit to numerical digit, if it's index is greater than the written digit index
			if (index >= heighestSecondIndex)
			{
				second_digit = c - '0';
			}
		}

		// Combine the digits together to form a 2 digit number (e.g: 1 and 1 = 11)
		// then add it to the result
		int cal = first_digit * 10 + second_digit;
		result += cal;
	}

	// Log the result
	cout << result << endl;
}