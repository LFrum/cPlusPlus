/*
Lince Rumainum
Student ID: 112722337
CS2413 Data Structure
Lab 1 VoteR.cpp
*/

// include libraries
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


// Main function
int main() {
	// Variables
	bool dataError = false; // Integer input error indicator							
	bool duplicateID = false; // To use for recordID duplicate indicator

	int lineCount = 0; // The line number for the data
	int dataSize = 0; // Size of the data vector
	int recordIDNum = 0; // The input record ID number
	int recordIDSize = 0; // Size of recordID vector
	int intData = 0; // Integer input data

	std::vector<int> recordID(0); // Vector of record ID number (the first column of data)
	std::vector<std::string> data(0); // Vector use to store individual column in a group
	
	std::string strData = ""; // String from each line in the file	

	// Getting the first line of data
	std::getline(std::cin, strData);
	// Getting the second line of data
	std::getline(std::cin, strData);
	
	do {
		// Updating the line number for the current data
		lineCount++;

		// Set error indicators to false
		dataError = false;
		duplicateID = false;

		/*
		url: http://www.cplusplus.com/forum/general/116829/ - split c++ string
		I use the example on how using stringstream to parse the sentence by ','
		so I would be able to put it in to my vector variable as needed
		#include sstream library is added to use it
		*/
		std::stringstream bigData(strData); // stringstream is use to parse the strData into individual string input
		std::string singleData = ""; // String use to store when parsing the bigData
		data.resize(0); // Resetting data vector to zero

		// Putting each individual string data to the vector parsing it by comma
		while (std::getline(bigData, singleData, ',')) {
			data.push_back(singleData);
		}

		dataSize = (int)data.size(); // Update the dataSize of data vector

		// Input error check
		for (int i = 0; i < dataSize; i++) {
			// For integer input
			if (i != 3 && i != 11 && i != 12) {
				intData = std::stoi(data.at(i)); // Covert data from string to integer

				// Check for negative input error
				if (intData < 0) {
					dataError = true; // Indicate input error
				}
				// Check for duplicate in record ID number list
				else {
					// For record ID number
					if (i == 0) {						
						recordID.push_back(intData); // Store the record ID into the recordID vector					
						recordIDSize = (int)recordID.size(); // Update size of recordID vector
						
						for (int j = 0; j < recordIDSize - 1; j++) { // make sure it does not compare to the last entry
							// Duplicate record ID number is found
							if (intData == recordID.at(j)) {
								recordID.pop_back(); // Deleting last record ID entry
								recordIDNum = recordID.at(j); // Store duplicate record ID number
								duplicateID = true; // Indicate duplication in record ID
							}
						}
					}
				}
			}
		}

		// If there is error, print error message accordingly, otherwise print data
		if (dataError == true) {
			recordID.pop_back(); // Deleting last record ID entry
			std::cout << "Invalid data at line " << lineCount << "." << std::endl;
		}
		else if (duplicateID == true) {
			std::cout << "Duplicate record ID " << recordIDNum << " at line " << lineCount << "." << std::endl;
		}
		else {
			for (int i = 0; i < dataSize; i++) {
				// Print integer data
				if (i != dataSize - 1 && i != 3 && i != 11 && i != 12) {
					intData = std::stoi(data.at(i)); // Covert data from string to integer
					std::cout << intData << ";";
				}
				// Print string data
				else if (i != dataSize - 1 && (i == 3 || i == 11 || i == 12)) {
					std::cout << data.at(i) << ";";
				}
				// Print last data with a new line (We know the data is an integer)
				else {
					intData = std::stoi(data.at(i)); // Covert data from string to integer
					std::cout << intData << std::endl;
				}
			}
		}

	} while (std::getline(std::cin, strData)); // do-while loop until there is no data to read

	// End of program
	return 0;
}