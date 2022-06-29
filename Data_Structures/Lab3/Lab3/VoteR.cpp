/*
Lince Rumainum
Student ID: 112722337
CS2413 Data Structure
Lab 3 VoteR.cpp
*/

// include libraries
#include <iostream>
#include <string>
#include <sstream>
#include "NvraRecord.h"
#include "NvraArray.h"

// Main function
int main() {
	// Variables
	int lineCount = 0; // The line number for the data
	int dataIndex = -1;
	bool errorCheck = false;

	// Variables for objects
	NvraArray* storedNvraArray = new NvraArray();
	NvraRecord* recordData = NULL;
	
	// Index number of each nvraRecord (both nums & strings)
	int nvraRecordCurrentIndex = 0;

	std::string strData = ""; // String from each line in the file	

	// Getting the first line of data
	std::getline(std::cin, strData);
	// Getting the second line of data
	std::getline(std::cin, strData);

	do {
		// Updating the line number for the current data
		lineCount++;
		dataIndex++;

		// Resetting error check
		errorCheck = false; 

		/*
		url: http://www.cplusplus.com/forum/general/116829/ - split c++ string
		I use the example on how using stringstream to parse the sentence by ','
		so I would be able to put it in to my vector variable as needed
		#include sstream library is added to use it
		*/
		std::stringstream bigData(strData); // stringstream is use to parse the strData into individual string input
		std::string singleData = ""; // String use to store when parsing the bigData

		// Resetting current record indexes to zeroes
		nvraRecordCurrentIndex = 0;
		// Record single line input
		recordData = new NvraRecord[1];


		// Putting each individual nums and strings data to the nvra Record vector parsing it by comma
		while (std::getline(bigData, singleData, ',')) {
			// For nums input
			if (nvraRecordCurrentIndex != 3 && nvraRecordCurrentIndex != 11 && nvraRecordCurrentIndex != 12) {
				recordData->addNum(std::stoi(singleData));
				//storedNvraArray->get(dataIndex).addNum(std::stoi(singleData));
			}
			// For strings input
			else {
				recordData->addString(singleData);
				//storedNvraArray->get(dataIndex).addString(singleData);
			}
			nvraRecordCurrentIndex++;
		}

		// Input error check for the array nums input
		for (int i = 0; i < MAX_NUMS; i++) {
			// Check for negative input error
			if (recordData->getNum(i) < 0) {
				// Send error message out for invalid data at current line
				std::cout << "Invalid data at line " << lineCount << "." << std::endl;
				
				dataIndex--; // The data index is set back for invalid data
				errorCheck = true; // Error found
			}
			// Check for duplicate in record ID number list
			else {
				// For record ID number
				if (i == 0 && dataIndex > 0) {
					// Compare to the previous record ID
					for (int j = 0; j < dataIndex; j++) { // make sure it does not compare to the last entry
						// Duplicate record ID number is found
						if (recordData->getNum(i) == storedNvraArray->get(j).getNum(i)) {
							// Send error message out for the duplicate record ID
							std::cout << "Duplicate record ID " << recordData->getNum(i) << " at line " << lineCount << "." << std::endl;
							
							dataIndex--; // The data index is set back for invalid data
							errorCheck = true; // Error found
						}
					}
				}
			}
		}

		if (errorCheck == false) {
			storedNvraArray->add(recordData);
		}

		// Memory deallocation and Resetting recordData
		delete[] recordData;
		recordData = NULL;

	} while (std::getline(std::cin, strData)); // do-while loop until there is no data to read

	// Print data in reverse order
	for (int index = dataIndex; index >= 0; index--) {		
		std::cout << storedNvraArray->get(index) << std::endl;
	}

	// End of program
	return 0;
}