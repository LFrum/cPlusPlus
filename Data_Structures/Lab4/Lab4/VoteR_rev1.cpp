/*
Lince Rumainum
Student ID: 112722337
CS2413 Data Structure
Lab 4 VoteR.cpp
*/

// include libraries
#include <iostream>
#include <string>
#include <sstream>
#include "NvraRecord.h"
#include "TemplatedArray.h"
#include "Exceptions.h"

// Main function
int main() {
	// Variables
	int lineCount = 0; // The line number for the data
					   //int dataIndex = -1;
	unsigned long int dataIndex = 0;
	//bool errorCheck = false;

	// Variables for objects

	//typedef TemplatedArray<NvraRecord> *storedNvraArray();

	TemplatedArray<NvraRecord> storedNvraArray;
	//TemplatedArray<NvraRecord> storedNvraArray();

	//*storedNvraArray = &storedNvraArray;
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

		// Resetting error check
		//errorCheck = false; 

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
			}
			// For strings input
			else {
				recordData->addString(singleData);
			}
			nvraRecordCurrentIndex++;
		}

		storedNvraArray.addAt(*recordData, dataIndex);

		try {
			// Input error check for the array nums input
			for (int i = 0; i < MAX_NUMS; i++) {
				// Check for negative input error
				if (recordData->getNum(i) < 0) {
					// Send error message out for invalid data at current line
					std::cout << "Invalid data at line " << lineCount << "." << std::endl;

					storedNvraArray.removeAt(dataIndex);

					//dataIndex--; // The data index is set back for invalid data
					//errorCheck = true; // Error found
				}
				// Check for duplicate in record ID number list
				else {
					// For record ID number
					if (i == 0 && dataIndex > 0) {
						// Compare to the previous record ID
						for (unsigned long int j = 0; j < dataIndex; j++) { // make sure it does not compare to the last entry
																			// Duplicate record ID number is found

							if (recordData->getNum(i) == storedNvraArray.get(j).getNum(i)) {
								// Send error message out for the duplicate record ID
								std::cout << "Duplicate record ID " << recordData->getNum(i) << " at line " << lineCount << "." << std::endl;

								storedNvraArray.removeAt(dataIndex);

								//dataIndex--; // The data index is set back for invalid data
								//errorCheck = true; // Error found
							}
						}
					}
				}
			}
		}
		catch (ExceptionIndexOutOfRange) {
			std::cout << "Error! Index is out of range!" << std::endl;
		}

		// Memory deallocation and Resetting recordData
		delete[] recordData;
		recordData = NULL;

		dataIndex++;

	} while (std::getline(std::cin, strData)); // do-while loop until there is no data to read

	dataIndex--; // the last dataIndex is 1 extra index

				 // Print data in reverse order
	unsigned long int printIndex = dataIndex;
	do {
		std::cout << storedNvraArray.get(printIndex);
		printIndex--;
	} while (printIndex != 0);

	// print at printIndex = 0
	std::cout << storedNvraArray.get(printIndex);

	// End of program
	return 0;
}