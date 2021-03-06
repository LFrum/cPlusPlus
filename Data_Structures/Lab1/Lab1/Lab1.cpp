// Lab1.cpp : Defines the entry point for the console application.
//
/*
Lince Rumainum
Student ID: 112722337
CS2413 Data Structure
Lab 1
*/

// include libraries
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


int main() {
	// Initialize variables
	int lineCount = 0; // The line number for the data
	std::string strData; // string from each line in the file
	std::vector<int> recordID; // first column of data (record ID number)

	// Getting the data to skip first line of data
	std::getline(std::cin, strData);
	std::getline(std::cin, strData);

	do {
		lineCount++;
		if (lineCount > 1) {
			std::cout << endl;		
		}
		/*
		url: http://www.cplusplus.com/forum/general/116829/ - split c++ string
		I use the example how using stringstream to parse the sentence by ','
		so I would be able to put it in to my vector variable as needed
		*/
		std::stringstream bigData(strData);
		std::string singleData;
		std::vector<std::string> data;

		// Putting each individual string data to the vector parsing it by comma
		while (std::getline(bigData, singleData, ',')) {
			data.push_back(singleData);
		}

		for (int i = 0; i < data.size() - 1; i++) {
			// For string columns at 4th, 12th, and 13th column
			if (i == 3 || i == 11 || i == 12) {
				// Print out the string
				std::cout << data.at(i) << ";";
			}
			// For integer data
			else {
				// Covert data from string to integer
				int intData = stoi(data.at(i));

				// Check for negative input error
				if (intData < 0) {
					std::cout << "Invalid data at line " << lineCount << "." << std::endl;
				}
				else {
					// For record ID number
					if (i == 0) {
						// Record the record ID
						recordID.push_back(intData);
						bool duplicate = false;

						// Check for duplicate record ID
						for (int j = 0; j < recordID.size() - 2; j++) {
							// Duplicate record ID error
							if (intData == recordID.at(j)) {
								std::cout << "Duplicate record ID " << recordID.at(j) << " at line " << lineCount << "." << std::endl;
								// Deleting last record ID entry
								recordID.pop_back();
								duplicate = true;
							}
						}

						if (duplicate == false) {
							// If there is no duplicate, print record ID 
							std::cout << intData << ";";
						}
					}

					// For other integer input
					else {
						std::cout << intData << ";";
					}
				}
			}
		}

		// Reading the next line of data		
		std::getline(std::cin, strData);
	} while (strData != "");

	// End of program
	return 0;
}