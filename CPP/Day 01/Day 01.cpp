#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int main()
{
	// Get input.txt filepath
	char filePath[FILENAME_MAX];
	GetCurrentDirectoryA(FILENAME_MAX, (LPSTR)filePath);
	strcat_s(filePath, "\\input.txt");

	// Log input.txt filepath
	std::cout << filePath << endl;

	// Create ifstream object and open input.txt
	ifstream ifs;
	ifs.open(filePath, ios::in);

	// Check if input.txt opened successfully
	if (!ifs.is_open())
	{
		// Log error and exit if unsuccessful
		cout << "failed to load input file" << endl;
		return 0;
	}

	// File opened successfully, declare required variables
	int result = 0;
	string line;

	// Read all lines
	while (getline(ifs, line))
	{
		// Declare temporary variables used to find first and last numerical characters
		bool first_found = false;
		int last_digit = 0;

		// Iterate over string
		for (char& c : line)
		{
			// Check if it's a numerical digit, if not, continue to next character
			if (!isdigit(c))
			{
				continue;
			}

			// Add the first digit multiplied by 10 to the result
			if (!first_found)
			{
				result += (c - '0') * 10;
				first_found = true;
			}

			// Storing every digit encountered ensures the last digit is stored
			last_digit = c - '0';
		}

		// Add the second digit value
		result += last_digit;
	}
	
	// Log the result
	std::cout << result << endl;

	system("pause");
}