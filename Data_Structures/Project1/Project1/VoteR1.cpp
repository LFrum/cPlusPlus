/*
Lince Rumainum
Student ID: 112722337
CS2413 Data Structure
Project 1 VoteR1.cpp
*/

// include libraries
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "TemplatedArray.h"
#include "Comparator.h"
#include "NvraComparator.h"
#include "NvraRecord.h"
#include "Sorter.h"
#include "Search.h"
#include "Exceptions.h"

// List of functions
void takeInput();
void processInput(std::string fileName);
void manipulateData();
void outputData();
void processOutput(std::ostream& os);
void sortData();
void findData();
void processSearchNum(unsigned int col, unsigned int num, NvraComparator* searchCol);
void processSearchStr(unsigned int col, std::string str, NvraComparator* searchCol);
void searchMessage(unsigned int foundCount);

// Global variables
typedef TemplatedArray<NvraRecord> NvraArray;
NvraArray* storedNvraArray = new NvraArray(); // array of all data across all of the files

typedef TemplatedArray<NvraRecord> NvraArray;
NvraArray* currentNvraArray = new NvraArray(); // array of the current file being read

unsigned long totalLineCount = 0;			// The total lines number read
unsigned long totalValidData = 0;			// Valid records read
unsigned long totalRecordsInMemory = 0;		// All records without invalid data & duplicate IDs

int invalidCtr = 0;				// counter for invalid data input
int duplicateCtr = 0;			// counter for duplicate ID input
int fileReadCtr = 0;			// counter for number of input file read
unsigned int colSorted = 0;		// column that is sorted last

// Actual index of number and string on NvraRecord
unsigned int arrayNumIndex(unsigned int col);
unsigned int arrayStrIndex(unsigned int col);

// Main function
int main() {
	//-----------------------------------------------------------------------------------------------
	// Input Loop
	takeInput();
	
	if (fileReadCtr == 0) {
		// End of program
		return 0;
	}
	else {
		try {
			// sort by record ID at column 0
			NvraComparator* compareColID = new NvraComparator(0);

			try {
				// Sorting the first column (record ID)
				Sorter<NvraRecord>::sort(*storedNvraArray, *compareColID);
				colSorted = 0; // updated the column # that is sorted
			}
			catch (ExceptionIndexOutOfRange) {
				std::cout << "Index out of range!" << std::endl;
			}

			// Manipulation Loop
			manipulateData();

			// Exit message
			std::cout << "Thanks for using VoteR." << std::endl;
		}
		catch (ExceptionMemoryNotAvailable) {
			std::cout << "Memory is not available" << std::endl;
		}
		// End of program
		return 0;
	}
}

// Functions

// --------------- INPUT LOOP --------------- 
void takeInput() {
	// variable for input file 
	std::string inputFileName;
	std::ifstream inputFile;

	do {
		// Get file name from user
		std::cout << "Enter data file name: ";
		getline(std::cin, inputFileName);

		if (inputFileName != "") {
			// try to open file
			inputFile.open(inputFileName);
			if (inputFile) {
				try {
					// File is accessible
					// store current array in this variable
					currentNvraArray = new NvraArray();
					processInput(inputFileName); // read input file
					inputFile.close(); // close file
					fileReadCtr++; // increment file read

					// deallocation of memories
					delete currentNvraArray;
					currentNvraArray = NULL;

				}
				catch (ExceptionMemoryNotAvailable) {
					std::cout << "Memory is not available" << std::endl;
				}
			}			
			else if (!inputFile) {
				// File is not accessible
				std::cout << "File is not available." << std::endl;
			}
		}
	// will continue to manipulation loop if at least 1 file is read
	} while (inputFileName != "");
}

void processInput(std::string fileName) {
	// Variables
	int lineCount = 0; // The line number for the data
	unsigned long int dataIndex = 0; // the index of the data in the array
	std::ifstream currentInput(fileName);
	// Variables for objects
	NvraRecord* recordData = NULL;

	// Index number of each nvraRecord (both nums & strings)
	int nvraRecordCurrentIndex = 0;

	std::string strData = ""; // String from each line in the file	

	// Getting the first line of data
	std::getline(currentInput, strData);
	// Getting the second line of data
	std::getline(currentInput, strData);

	do {
		// Updating the line number for the current data
		lineCount++;

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
		bool isInvalidData = false;

		// Putting each individual nums and strings data to the nvra Record vector parsing it by comma
		while (std::getline(bigData, singleData, ',') && isInvalidData == false) {
			// For nums input
			try {
				if (nvraRecordCurrentIndex != 3 && nvraRecordCurrentIndex != 11 && nvraRecordCurrentIndex != 12) {
					// Check for invalid input
					if (singleData[0] != '-') {
						recordData->addNum(std::stoi(singleData));
					}
					else {
						isInvalidData = true;
						// Send error message out for invalid data at current line
						std::cout << "Invalid data at line " << lineCount << "." << std::endl;
						invalidCtr++;
					}
				}
				// For strings input
				else {
					recordData->addString(singleData);
				}
			}
			catch (ExceptionIndexOutOfRange) {
				std::cout << "Index Out Of Range" << std::endl;
			}
			nvraRecordCurrentIndex++;
		}


		if (isInvalidData == false) {
			// add data into the arrays
			currentNvraArray->add(recordData);
			storedNvraArray->add(recordData);

			// For record ID number
			unsigned int id = 0;
			if (dataIndex > 0) {
				// Compare to the previous record ID in the current file
				for (unsigned long j = 0; j < dataIndex; j++) { // make sure it does not compare to the last entry
					// Duplicate record ID number is found
					if (recordData->getNum(id) == currentNvraArray->get(j).getNum(id)) {
						// Send error message out for the duplicate record ID
						std::cout << "Duplicate record ID " << recordData->getNum(id) << " at line " << lineCount << "." << std::endl;

						try {
							// Removing the last added nvraRecord from the array since there is an error in data
							currentNvraArray->removeAt(dataIndex);
							storedNvraArray->removeAt(storedNvraArray->getSize() - 1);
							dataIndex--;
							duplicateCtr++;
						}
						catch (ExceptionIndexOutOfRange) {
							std::cout << "Error! Index is out of range!" << std::endl;
						}
					}
				}
			}

			if (fileReadCtr > 0) {
				// Compare to the previous record ID on previous file(s)
/*
				unsigned long oldFilesSize = storedNvraArray->getSize() - currentNvraArray->getSize();
				for (unsigned long j = 0; j < oldFilesSize; j++) { // make sure it does not compare to the last entry
					// Duplicate record ID number is found
					if (recordData->getNum(id) == storedNvraArray->get(j).getNum(id)) {
						duplicateCtr++;
						// Send error message out for the duplicate record ID
						//std::cout << "Duplicate record ID " << recordData->getNum(i) << " at line " << lineCount << "." << std::endl;

						try {
							// Removing nvraRecord from the array since there is an error in data
							// Retained the new record ID and removing the one in the old file
							storedNvraArray->removeAt(j);
						}
						catch (ExceptionIndexOutOfRange) {
							std::cout << "Error! Index is out of range!" << std::endl;
						}
					}
				}
*/
				unsigned long j = 0;
				unsigned long oldFilesSize = 0;
				do {
					oldFilesSize = storedNvraArray->getSize() - currentNvraArray->getSize();
					// Duplicate record ID number is found
					if (recordData->getNum(id) == storedNvraArray->get(j).getNum(id)) {
						duplicateCtr++;
						// Send error message out for the duplicate record ID
						//std::cout << "Duplicate record ID " << recordData->getNum(i) << " at line " << lineCount << "." << std::endl;

						try {
							// Removing nvraRecord from the array since there is an error in data
							// Retained the new record ID and removing the one in the old file
							storedNvraArray->removeAt(j);
							j--;
						}
						catch (ExceptionIndexOutOfRange) {
							std::cout << "Error! Index is out of range!" << std::endl;
						}
					}
					j++;
				} while (j < oldFilesSize);
			}

			dataIndex++; // increment data's index
		}

		// Memory deallocation and Resetting recordData
		delete[] recordData;
		recordData = NULL;

	} while (std::getline(currentInput, strData)); // do-while loop until there is no data to read

	dataIndex--; // the last dataIndex is 1 extra index

	totalLineCount += lineCount; // total line counts across all files being read
	totalValidData = totalLineCount - invalidCtr; // total valid data read
	totalRecordsInMemory = totalValidData - duplicateCtr; // total records read

}

// --------------- END OF INPUT LOOP --------------- 

// --------------- MANIPULATION LOOP --------------- 
void manipulateData() {
	// output option variable
	std::string option;

	do {
		// Get user options choice
		std::cout << "Enter (o)utput, (s)ort, (f)ind, or (q)uit: " << std::endl;
		std::getline(std::cin, option);

		// User choose output
		if (option == "o") {
			outputData();
		}
		// User choose sort
		if (option == "s") {
			sortData();
		}
		// User choose find
		if (option == "f") {
			findData();
		}

	} while (option != "q"); // will quit the program when 'q' is entered
}

// --------- OUTPUT LOOP --------------- 
void outputData() {
	// variable for output file 
	std::string outputFileName;
	std::ofstream outputFile;
	bool errorFile = false;

	do {
		// Get file name from user
		std::cout << "Enter output file name: ";
		getline(std::cin, outputFileName);

		// Output to console
		if (outputFileName == "") {
			processOutput(std::cout);
		}
		else if (outputFileName != "") {
			// try to open file
			outputFile.open(outputFileName);
			if (!outputFile) {
				// File is not accessible
				std::cout << "File is not available." << std::endl;
				errorFile = true;
			}
			else {
				// File is accessible, 
				for (unsigned int k = 0; k < totalRecordsInMemory; k++) {
					// Maximum number of data record
					unsigned int recordMaxIndex = 24;

					unsigned int nvraRecordNumsIndex = 0;	// Index for numbers
					unsigned int nvraRecordStrIndex = 0;	// Index for strings

					for (unsigned int i = 0; i < recordMaxIndex; i++) {
						// Print integer data
						if (i != recordMaxIndex - 1 && i != 3 && i != 11 && i != 12) {
							outputFile << storedNvraArray->get(k).getNum(nvraRecordNumsIndex) << ";";
							nvraRecordNumsIndex++;
						}
						// Print string data
						else if (i != recordMaxIndex - 1 && (i == 3 || i == 11 || i == 12)) {
							outputFile << storedNvraArray->get(k).getString(nvraRecordStrIndex) << ";";
							nvraRecordStrIndex++;
						}
						// Print last data (We know the data is an integer)
						else {
							outputFile << storedNvraArray->get(k).getNum(nvraRecordNumsIndex);
						}
					}
					outputFile << std::endl;
				}

				// Print out internal tallies
				outputFile << "Data lines read: " << totalLineCount << "; "
					<< "Valid NVRA records read: " << totalValidData << "; "
					<< "NVRA records in memory: " << totalRecordsInMemory << std::endl;

				// Close output file
				outputFile.close();
			}
		}
	} while (errorFile == true);

}

void processOutput(std::ostream& os) {
	try {
		for (unsigned long i = 0; i < totalRecordsInMemory; i++) {
			os << storedNvraArray->get(i) << std::endl;
		}	
	}
	catch (ExceptionIndexOutOfRange) {
		std::cout << "Index out of range!" << std::endl;
	}
	// Print out internal tallies
	std::cout << "Data lines read: " << totalLineCount << "; "
		<< "Valid NVRA records read: " << totalValidData << "; "
		<< "NVRA records in memory: " << totalRecordsInMemory << std::endl;
}
// --------- END OF OUTPUT LOOP -----

// --------- SORT LOOP --------------- 
void sortData() {
	// sort variables
	std::string strInput = "";
	int userInput = -1;

	// Get user options choice
	std::cout << "Enter sort field (0-23): ";
	std::getline(std::cin, strInput);
	userInput = std::stoi(strInput);

	// Valid user input
	if (userInput >= 0 && userInput < 24) {
		// Sort the data in the specified column
		NvraComparator* compareCol = NULL;
		try {
			compareCol = new NvraComparator(userInput);
			Sorter<NvraRecord>::sort(*storedNvraArray, *compareCol);
			colSorted = userInput; // update the column that is sorted		
		}
		catch (ExceptionMemoryNotAvailable) {
			std::cout << "Memory is not available" << std::endl;		
		}
		// deallocation of memories
		delete[] compareCol;
		compareCol = NULL;
	}
}
// --------- END OF SORT LOOP --------


// --------- FIND LOOP --------------- 
void findData() {
	// variables to search data
	unsigned int userInput;
	unsigned int intInput;
	std::string strInput = "";

	// Get user options choice
	std::cout << "Enter search field (0-23): ";
	std::getline(std::cin, strInput);
	userInput = std::stoi(strInput);

	// Valid user input
	if (userInput < 24) {
		try {
			NvraComparator* searchColumn = NULL;
			searchColumn = new NvraComparator(userInput);

			// Valid user input - numeric column
			if (userInput != 3 && userInput != 11 && userInput != 12) {
				// Get user's input
				std::cout << "Enter non-negative field value: ";
				std::getline(std::cin, strInput);

				if (strInput[0] != '-') {
					intInput = std::stoi(strInput);
					// Search for the specified data
					processSearchNum(userInput, intInput, searchColumn);
				}
			}
			// Valid user input - string column
			else {
				// Get user's input
				std::cout << "Enter exact text on which to search: ";
				getline(std::cin, strInput);
				if (strInput != "") {
					// Search for the specified data
					processSearchStr(userInput, strInput, searchColumn);
				}
			}
			// deallocation of memories
			delete[] searchColumn;
			searchColumn = NULL;
		}
		catch (ExceptionMemoryNotAvailable) {
			std::cout << "Memory is not available" << std::endl;
		}
	}
}

void processSearchNum(unsigned int col, unsigned int num, NvraComparator* searchCol) {
	unsigned int foundCtr = 0;
	unsigned int numIndex = arrayNumIndex(col);

	// the specified column is NOT sorted - do Linear Search
	if (colSorted != col) {
	//if (isSortCol[col] == false) {
		for (unsigned int i = 0; i < totalRecordsInMemory; i++) {
			if (num == storedNvraArray->get(i).getNum(numIndex)) {
				std::cout << storedNvraArray->get(i) << std::endl;
				foundCtr++;
			}
		}
	}
	else { // sorted column, do Binary Search
		NvraRecord* item = NULL;
		item = new NvraRecord[1];
		item->setNum(num, col);

		// do binary search and return the first index the item is located in the array
		long long searchIndex = binarySearch<NvraRecord>(*item, *storedNvraArray, *searchCol);
		if (searchIndex >= 0) {
			std::cout << storedNvraArray->get((unsigned long)searchIndex) << std::endl;
			foundCtr++;
		}

		// deallocation of memories
		delete[] item;
		item = NULL;
	}

	// show how many records found, if any
	searchMessage(foundCtr);
}

void processSearchStr(unsigned int col, std::string str, NvraComparator* searchCol) {
	unsigned int foundCtr = 0;
	unsigned int strIndex = arrayStrIndex(col);

	// the specified column is NOT sorted - do Linear Search
	if (colSorted != col) {
		for (unsigned int i = 0; i < totalRecordsInMemory; i++) {
			if (str == storedNvraArray->get(i).getString(strIndex)) {
				std::cout << storedNvraArray->get(i) << std::endl;
				foundCtr++;
			}
		}
	}
	else { // sorted column, do Binary Search
		NvraRecord* item = NULL;
		item = new NvraRecord[1];
		item->setString(str, col);

		// do binary search and return the first index the item is located in the array
		long long searchIndex = binarySearch<NvraRecord>(*item, *storedNvraArray, *searchCol);
		if (searchIndex >= 0) {
			std::cout << storedNvraArray->get((unsigned long)searchIndex) << std::endl;
			foundCtr++;
		}

		// deallocation of memories
		delete[] item;
		item = NULL;
	}

	// show how many records found, if any
	searchMessage(foundCtr);
}

void searchMessage(unsigned int foundCount) {
	std::cout << "NVRA records found: " << foundCount << "." << std::endl;
}
// --------- END OF FIND LOOP --------

// --------------- END OF MANIPULATION LOOP --------------- 

// ------------- ADDITIONAL FUNCTIONS ------------------
// Actual index of number and string on NvraRecord
unsigned int arrayNumIndex(unsigned int col) {
	unsigned int numIndex = 2;

	// Numeric column
	if (col < 3) {
		numIndex = col;
	}
	else if (col > 3 && col < 11) {
		numIndex = col - 1;
	}
	else if (col > 12 && col < 24) {
		numIndex = col - 2;
	}
	return numIndex;
}

unsigned int arrayStrIndex(unsigned int col) {
	unsigned int strIndex = 2;
	// String column
	if (col == 3) {
		strIndex = 0;
	}
	else if (col == 11) {
		strIndex = 1;
	}
	else if (col == 12) {
		strIndex = 2;
	}
	return strIndex;
}