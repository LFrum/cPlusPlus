/*
Lince Rumainum
Student ID: 112722337
CS2413 Data Structure
Lab 2 VoteR.cpp
*/

// include libraries
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Declare structures and function
struct nvraRecord;
struct nvraArray;
nvraArray* doubleNvraArray(nvraArray* currentNvraArray);

// Structure that holds the data of nvra records
struct nvraRecord {
	int nums[21]; // holds the numeric data, in column order
	std::string strings[3]; // holds the string data, in column order
};

// Structure of the array  
struct nvraArray {
	int capacity; // maximum capacity, in records
	nvraRecord* data = NULL; // pointer to array of records
};


// This function will copy old array into new array
nvraArray* doubleNvraArray(nvraArray* currentNvraArray) {
	// Double the capacity of new array and copy the old array into the new array
	nvraArray* updatedNvraArray = new nvraArray;
	updatedNvraArray->data = new nvraRecord[2 * currentNvraArray->capacity];
	updatedNvraArray->capacity = 2 * currentNvraArray->capacity;
	
	// Copy the data from the old array into the new array
	for (int i = 0; i < currentNvraArray->capacity; i++) {
		updatedNvraArray->data[i] = currentNvraArray->data[i];
	}

	// Deallocating the memories of old array and its data
	delete[] currentNvraArray->data; // Deleting the old data of nvraRecord
	delete currentNvraArray; //Deleting the old data array

	return updatedNvraArray;
}

// Main function
int main() {
	// Variables
	int lineCount = 0; // The line number for the data
	int dataIndex = - 1;

	// Variables for nvraRecord
	int nvraRecordCurrentIndex = 0; // Index number of each nvraRecord (both nums & strings)
	int nvraRecordNumsIndex = 0; // Index number of nvraRecord's nums
	int nvraRecordStrIndex = 0; // Index number of nvraRecord's strings

	// Pointer of nvraArray
	nvraArray* storedNvraArray = new nvraArray;
	storedNvraArray->capacity = 10; // Initialize array to size 10
	storedNvraArray->data = new nvraRecord[storedNvraArray->capacity]; // Initialize data size

	std::string strData = ""; // String from each line in the file	

	// Getting the first line of data
	std::getline(std::cin, strData);
	// Getting the second line of data
	std::getline(std::cin, strData);

	do {
		// Updating the line number for the current data
		lineCount++;
		dataIndex++;

		if (lineCount > storedNvraArray->capacity) {
			// Double the capacity of stored nvraArray & copy array data
			storedNvraArray = doubleNvraArray(storedNvraArray);
		}	

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
		nvraRecordNumsIndex = 0;
		nvraRecordStrIndex = 0;

		// Putting each individual nums and strings data to the nvra Record vector parsing it by comma
		while (std::getline(bigData, singleData, ',')) {
			// For nums input
			if (nvraRecordCurrentIndex != 3 && nvraRecordCurrentIndex != 11 && nvraRecordCurrentIndex != 12) {
				storedNvraArray->data[dataIndex].nums[nvraRecordNumsIndex] = std::stoi(singleData);
				nvraRecordNumsIndex++; // Increment number's index for next input
			}
			// For strings input
			else {
				storedNvraArray->data[dataIndex].strings[nvraRecordStrIndex] = singleData;
				nvraRecordStrIndex++; // Increment string's index for next input
			}
			nvraRecordCurrentIndex++;
		}		

		// Input error check for the array nums input
		for (int i = 0; i < nvraRecordNumsIndex; i++) {
			// Check for negative input error
			if (storedNvraArray->data[dataIndex].nums[i] < 0) {
				// Send error message out for invalid data at current line
				std::cout << "Invalid data at line " << lineCount << "." << std::endl;

				//This will overwrite previous for the next line read
				dataIndex--;
			}
			// Check for duplicate in record ID number list
			else {
				// For record ID number
				if (i == 0 && dataIndex > 0) {
					// Compare to the previous record ID
					for (int j = 0; j < dataIndex; j++) { // make sure it does not compare to the last entry
						// Duplicate record ID number is found
						if (storedNvraArray->data[dataIndex].nums[i] == storedNvraArray->data[j].nums[i]) {
							// Send error message out for the duplicate record ID
							std::cout << "Duplicate record ID " << storedNvraArray->data[dataIndex].nums[i] << " at line " << lineCount << "." << std::endl;

							//This will overwrite previous data for the next line it reads
							dataIndex--;
						}
					}
				}
			}
		}

	} while (std::getline(std::cin, strData)); // do-while loop until there is no data to read

	// The maximum number of data in each nvraRecord (nums and strings)
	int recordMaxIndex = nvraRecordNumsIndex + nvraRecordStrIndex;

	// Print data in reverse order
	for (int index = dataIndex; index >= 0; index--) {
		// Reset index of array nums and strings
		nvraRecordNumsIndex = 0;
		nvraRecordStrIndex = 0;

		for (int i = 0; i < recordMaxIndex; i++) {
			// Print integer data
			if (i != recordMaxIndex - 1 && i != 3 && i != 11 && i != 12) {
				std::cout << storedNvraArray->data[index].nums[nvraRecordNumsIndex] << ";";
				nvraRecordNumsIndex++;
			}
			// Print string data
			else if (i != recordMaxIndex - 1 && (i == 3 || i == 11 || i == 12)) {
				std::cout << storedNvraArray->data[index].strings[nvraRecordStrIndex] << ";";
				nvraRecordStrIndex++;
			}
			// Print last data with a new line (We know the data is an integer)
			else {
				std::cout << storedNvraArray->data[index].nums[nvraRecordNumsIndex] << std::endl;
			}
		}
	}

	// End of program
	return 0;
}