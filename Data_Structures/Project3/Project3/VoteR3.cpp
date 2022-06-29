/*
Lince Rumainum
Student ID: 112722337
CS2413 Data Structure
Project 2 VoteR2.cpp
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
#include "OULink.h"
#include "OULinkedList.h"
#include "OULinkedListEnumerator.h"
#include "NvraHasher.h"
#include "Hasher.h"
#include "HashTable.h"
#include "HashTableEnumerator.h"


// List of functions
void takeInput();
// option: 'i' for initial file, 'm' for merge file, 'p' for purge file
void processInput(std::string fileName, char option);
void optionMenu();
void outputData();
void processOutput(std::ostream& os);
void sortData();
void findData();
void mergeData();
void purgeData();
void printList();
void printHashTable();
void storeToArray();
void storeToHashTable();
void processSearchNum(unsigned int col, unsigned int num, NvraComparator* searchCol);
void processSearchStr(unsigned int col, std::string str, NvraComparator* searchCol);
void searchMessage(unsigned int foundCount);

// Global variables
typedef TemplatedArray<NvraRecord> NvraArray;
NvraArray* storedNvraArray = new NvraArray(); // array of all data across all of the files

NvraComparator* compareColID = new NvraComparator(0);

typedef OULinkedList<NvraRecord> recordList;
recordList* storedList = new recordList(compareColID); // list of all data across all of the files

//Hasher<NvraRecord>* idHasher = NULL;
//idHasher = new Hasher<NvraRecord>[1]; // recordID hasher function

NvraHasher* idHasher = new NvraHasher[1];
typedef HashTable<NvraRecord> recordHashTable;
recordHashTable* idHashTable = new HashTable<NvraRecord>(compareColID, idHasher); // hash table based of record ID

unsigned long totalLineCount = 0;			// The total lines number read
unsigned long totalValidData = 0;			// Valid records read
unsigned long totalRecordsInMemory = 0;		// All records without invalid data & duplicate IDs

int invalidCtr = 0;				// counter for invalid data input
int duplicateCtr = 0;			// counter for duplicate ID input
int fileReadCtr = 0;			// counter for number of input file read
unsigned int colSorted = 0;		// column that is sorted last, default is recordID column

// Actual index of number and string on NvraRecord
unsigned int arrayNumIndex(unsigned int col);
unsigned int arrayStrIndex(unsigned int col);

// Main function
int main() {
	//-----------------------------------------------------------------------------------------------
	// prompt for first input file data
	// Prompt user for initial data
	takeInput();

	if (fileReadCtr == 0) {
		// End of program
		return 0;
	}
	else {

		// Option Loop
		optionMenu();

		// Exit message
		std::cout << "Thanks for using VoteR." << std::endl;

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
	bool inputStatus = false;

	do {
		// Get file name from user
		std::cout << "Enter data file name: ";
		getline(std::cin, inputFileName);

		if (inputFileName != "") {
			// try to open file
			inputFile.open(inputFileName);
			if (inputFile) {
				// File is accessible
				processInput(inputFileName, 'i'); // read input file
				inputFile.close(); // close file
				if (totalValidData > 0) {
					fileReadCtr++; // increment file read
					inputStatus = true;
				}
				else {
					std::cout << "No valid records found." << std::endl;
				}
			}
			else if (!inputFile) {
				// File is not accessible
				std::cout << "File is not available." << std::endl;
			}
		}
		// will continue to manipulation loop if at least 1 file is read
	} while (inputStatus == false && inputFileName != "");
}

void processInput(std::string fileName, char option) {
	// Variables
	int lineCount = 0; // The line number for the data
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
			bool insertSuccessful = false;
			bool isItemRemoved = false;
			// initial file & purging file
			if (option == 'i') {				
				// if recordData inserted then it is NOT a duplicate
				insertSuccessful = storedList->insert(recordData);
				if (insertSuccessful == false) {
					// duplicate is found, increment its counter
					duplicateCtr++;
					// Send error message out for the duplicate record ID
					std::cout << "Duplicate record ID " << recordData->getNum(0) << " at line " << lineCount << "." << std::endl;
				}
			}
			// purging file
			else if (option == 'p') {
				// purge data from already stored data
				isItemRemoved = storedList->remove(recordData);

				idHashTable->remove(recordData);

				// count the data that was read to be removed from data being read in
				duplicateCtr++;

				if (isItemRemoved == true) {
					// duplicate found, increment counter
					duplicateCtr++;
				}
			}
			// merging file
			else if (option == 'm') {
				try {
					insertSuccessful = storedList->insert(recordData);
					//idHashTable->insert(recordData);
					if (insertSuccessful == false) {
						// duplicate is found, increment its counter
						duplicateCtr++;
						// replace old ID with new ID data
						storedList->replace(recordData);
						//idHashTable->replace(recordData);
						//std::cout << *recordData << std::endl;
					}
				}
				catch (ExceptionLinkedListAccess) {
					std::cout << "Exception Enumeration Beyond End!" << std::endl;
				}
			}
		}

		// Memory deallocation and Resetting recordData
		delete[] recordData;
		recordData = NULL;

	} while (std::getline(currentInput, strData)); // do-while loop until there is no data to read

	totalLineCount += lineCount; // total line counts across all files being read
	totalValidData = totalLineCount - invalidCtr; // total valid data read
	totalRecordsInMemory = totalValidData - duplicateCtr; // total records read

	if (option == 'i') {
		if (totalValidData > 0) {
			storeToArray();
		}
	}
	else if (option == 'p' || option == 'm') {
		storeToArray();	
	}
}

void storeToArray() {
	NvraRecord* recordData = NULL;
	// delete the old stored array and make a new one
	delete storedNvraArray;
	storedNvraArray = NULL;
	storedNvraArray = new NvraArray();

	try {
		// create enumerator
		OULinkedListEnumerator<NvraRecord> listOfRecords = storedList->enumerator();
		for (unsigned long i = 0; i < storedList->getSize(); i++) {
			recordData = new NvraRecord[1];			

			try {
				// put linked list into the array
				*recordData = listOfRecords.next();
				storedNvraArray->add(recordData);

			}
			catch (ExceptionEnumerationBeyondEnd) {
				std::cout << "Exception Enumeration Beyond End!" << std::endl;
			}
			delete[] recordData;
			recordData = NULL;
		}
	}
	catch (ExceptionEnumerationBeyondEnd) {
		std::cout << "Enumeration beyond end!" << std::endl;
	}
}

// --------------- END OF INPUT LOOP --------------- 

// --------------- OPTION LOOP --------------- 
void optionMenu() {
	// output option variable
	std::string option;

	// store initial data to hash table
	storeToHashTable();

	do {
		// Get user options choice
		std::cout << "Enter (o)utput, (s)ort, (f)ind, (m)erge, (p)urge, (r)ecords, (h)ash table, or (q)uit: ";
		std::getline(std::cin, option);

		// User choose output
		if (option == "o") {
			outputData();
		}
		// User choose sort
		else if (option == "s") {
			sortData();
		}
		// User choose find
		else if (option == "f") {
			findData();
		}
		// User choose merge
		else if (option == "m") {
			mergeData();
		}
		// User choose purge
		else if (option == "p") {
			purgeData();
		}
		// User choose record
		else if (option == "r") {
			printList();
		}
		// User choose hash table
		else if (option == "h") {
			printHashTable();
		}
	} while (option != "q"); // will quit the program when 'q' is entered
}
// --------------- END OF OPTION LOOP --------------- 

// User choose hash table
void printHashTable() {
	// store data into hash table before displaying hash table
	//storeToHashTable();

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
			typedef HashTableEnumerator<NvraRecord> recordHashTable;
			//recordHashTable* hashTableEnum = new recordHashTable(idHashTable);
			recordHashTable hashTableEnum = recordHashTable(idHashTable);

			try {
				unsigned long bucketCtr = 0;
				for (unsigned long i = 0; i < idHashTable->getBaseCapacity(); i++) {
						// print data in the bucket to console
						unsigned long j = 0;
						unsigned long currentBucketEnum = hashTableEnum.getBucketEnum();
						//std::cout << "currentBucketEnum: " << currentBucketEnum << std::endl;
						//std::cout << "hashTableEnum.hasNext(): " << hashTableEnum.hasNext() << std::endl;

						// check if i is the current data's bucket number
						while (i == currentBucketEnum && hashTableEnum.hasNext()) {
							try {
								if (j == 0) { // first data in the bucket
									if (bucketCtr > 0) {
										// extra space between the buckets
										std::cout << std::endl;
									}

									std::cout << i << ": ";
									std::cout << hashTableEnum.next() << std::endl;
									bucketCtr++;
								}
								else { // overflow data
									std::cout << "OVERFLOW: ";
									std::cout << hashTableEnum.next() << std::endl;
								}
								j++;
								// update current bucket
								currentBucketEnum = hashTableEnum.getBucketEnum();
							}
							catch (ExceptionHashTableAccess) {
								std::cout << "Exception Hash Table Enumeration Beyond End!" << std::endl;
							}
						}
				}

			}
			catch (ExceptionHashTableAccess) {
				std::cout << "Enumeration beyond end!" << std::endl;
			}

			// Print out internal tallies
			std::cout << std::endl;
			std::cout << "Base Capacity: " << idHashTable->getBaseCapacity() << "; "
				<< "Total Capacity: " << idHashTable->getTotalCapacity() << "; "
				<< "Load Factor: " << idHashTable->getLoadFactor() << std::endl;
			std::cout << "Data lines read: " << totalLineCount << "; "
				<< "Valid NVRA records read: " << totalValidData << "; "
				<< "NVRA records in memory: " << totalRecordsInMemory << std::endl;
			// END OF OUTPUT TO CONSOLE
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

				typedef HashTableEnumerator<NvraRecord> recordHashTable;
				recordHashTable* hashTableEnum = new recordHashTable(idHashTable);

				if (hashTableEnum == NULL) {
					throw new ExceptionMemoryNotAvailable();
				}
				else {
					try {
						for (unsigned long i = 0; i < idHashTable->getBaseCapacity(); i++) {
							// check if i is the current data's bucket number
							if (i == hashTableEnum->getBucketEnum() && hashTableEnum->hasNext() == true) {
								// print data in the bucket to console
								unsigned long j = 0;
								do {
									try {
										if (j == 0) { // first data in the bucket
											outputFile << i << ": ";
											outputFile << hashTableEnum->next() << std::endl;
										}
										else { // overflow data
											outputFile << "OVERFLOW: ";
											outputFile << hashTableEnum->next() << std::endl;
										}
										j++;
									}
									catch (ExceptionHashTableAccess) {
										outputFile << "Exception Hash Table Enumeration Beyond End!" << std::endl;
									}
								} while (hashTableEnum->hasNext() == true && i == hashTableEnum->getBucketEnum());

								// check if there is anymore bucket with data
								if (hashTableEnum->hasNext() == true) {
									// extra space for the next bucket
									outputFile << std::endl;
								}
							}
						}
					}
					catch (ExceptionHashTableAccess) {
						outputFile << "Enumeration beyond end!" << std::endl;
					}
				}

				// Print out internal tallies
				outputFile << std::endl;
				outputFile << "Base Capacity: " << idHashTable->getBaseCapacity() << "; "
					<< "Total Capacity: " << idHashTable->getTotalCapacity() << "; "
					<< "Load Factor: " << idHashTable->getLoadFactor() << std::endl;
				outputFile << "Data lines read: " << totalLineCount << "; "
					<< "Valid NVRA records read: " << totalValidData << "; "
					<< "NVRA records in memory: " << totalRecordsInMemory << std::endl;

				outputFile.close();
			}
		}
	} while (errorFile == true);
}

void storeToHashTable() {
	NvraRecord* recordData = NULL;
	// delete the old hash table and make a new one
	delete idHashTable;
	idHashTable = NULL;
	idHashTable = new HashTable<NvraRecord>(compareColID, idHasher); // hash table based of record ID

	try {
		// create enumerator
		OULinkedListEnumerator<NvraRecord> listOfRecords = storedList->enumerator();
		for (unsigned long i = 0; i < storedList->getSize(); i++) {
			recordData = new NvraRecord[1];

			try {
				// put linked list into the array
				*recordData = listOfRecords.next();
				idHashTable->insert(recordData);
			}
			catch (ExceptionEnumerationBeyondEnd) {
				std::cout << "Exception Enumeration Beyond End!" << std::endl;
			}
			delete[] recordData;
			recordData = NULL;
		}
	}
	catch (ExceptionEnumerationBeyondEnd) {
		std::cout << "Enumeration beyond end!" << std::endl;
	}
}

// User chose "(m)erge"
void mergeData() {
	// variable for input file 
	std::string inputFileName;
	std::ifstream inputFile;
	bool inputStatus = false;

	do {
		// Get file name from user
		std::cout << "Enter data file name: ";
		getline(std::cin, inputFileName);

		if (inputFileName != "") {
			// try to open file
			inputFile.open(inputFileName);
			if (inputFile) {
				// File is accessible
				processInput(inputFileName, 'm'); // read input file
				inputFile.close(); // close file
				inputStatus = true;
				storeToHashTable();
			}
			else if (!inputFile) {
				// File is not accessible
				std::cout << "File is not available." << std::endl;
			}
		}
		// will continue to manipulation loop if at least 1 file is read
	} while (inputStatus == false && inputFileName != "");
}

// User chose "(p)urge"
void purgeData() {
	// variable for input file 
	std::string inputFileName;
	std::ifstream inputFile;
	bool inputStatus = false;

	do {
		// Get file name from user
		std::cout << "Enter data file name: ";
		getline(std::cin, inputFileName);

		if (inputFileName != "") {
			// try to open file
			inputFile.open(inputFileName);
			if (inputFile) {
				// File is accessible
				processInput(inputFileName, 'p'); // read input file
				inputFile.close(); // close file	
				inputStatus = true;
			}
			else if (!inputFile) {
				// File is not accessible
				std::cout << "File is not available." << std::endl;
			}
		}
		// will continue to manipulation loop if at least 1 file is read
	} while (inputStatus == false && inputFileName != "");
}

// User chose "(r)ecord"
void printList() {
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
			try {
				OULinkedListEnumerator<NvraRecord> listOfRecords = storedList->enumerator();
				for (unsigned long i = 0; i < storedList->getSize(); i++) {
					// print to file
					try {
						std::cout << listOfRecords.next() << std::endl;
					}
					catch (ExceptionEnumerationBeyondEnd) {
						std::cout << "Exception Enumeration Beyond End!" << std::endl;
					}
				}
			}
			catch (ExceptionEnumerationBeyondEnd) {
				std::cout << "Enumeration beyond end!" << std::endl;
			}

			// Print out internal tallies
			std::cout << "Data lines read: " << totalLineCount << "; "
				<< "Valid NVRA records read: " << totalValidData << "; "
				<< "NVRA records in memory: " << totalRecordsInMemory << std::endl;

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
				try {
					OULinkedListEnumerator<NvraRecord> listOfRecords = storedList->enumerator();

					for (unsigned long i = 0; i < storedList->getSize(); i++) {					
						// print to file
						try {
							outputFile << listOfRecords.next() << std::endl;
						}
						catch (ExceptionEnumerationBeyondEnd) {
							std::cout << "Exception Enumeration Beyond End!" << std::endl;
						}
					}
				}
				catch (ExceptionEnumerationBeyondEnd) {
					std::cout << "Enumeration beyond end!" << std::endl;
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
				//std::cout << "totalRecordsInMemory: " << totalRecordsInMemory << std::endl;
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
		//std::cout << "totalRecordsInMemory: " << totalRecordsInMemory << std::endl;
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
			if (userInput == 0) {
				// sort using the hash table
				// storing data into the hash table automatically sorting the data by record ID
				storeToHashTable();
			}
			else {
				// sort using the templated array
				compareCol = new NvraComparator(userInput);
				Sorter<NvraRecord>::sort(*storedNvraArray, *compareCol);			
			}
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

					// search for record ID using hash table
					if (userInput == 0) {
						unsigned int foundCtr = 0;
						// setup searchRecord
						NvraRecord* searchRecord = NULL;
						searchRecord = new NvraRecord[1];
						searchRecord->setNum(intInput, 0);
						*searchRecord = idHashTable->find(searchRecord);
						if (searchRecord != NULL) {
							// since record ID is unique, if it is in the system then there is only 1
							std::cout << *searchRecord << std::endl;
							foundCtr++;
						}
						// show how many records found, if any
						searchMessage(foundCtr);

						// deallocate memory
						delete[] searchRecord;
						searchRecord = NULL;
					}
					// search for other data beside record ID column
					else {
						// Search for the specified data
						processSearchNum(userInput, intInput, searchColumn);					
					}
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

	// search for record ID using hash table
/*	if (colSorted == 0) {
		unsigned int foundCtr = 0;
		// setup searchRecord
		NvraRecord* searchRecord = NULL;
		searchRecord = new NvraRecord[1];
		searchRecord->setNum(num, 0);
		*searchRecord = idHashTable->find(searchRecord);
		if (searchRecord != NULL) {
			// since record ID is unique, if it is in the system then there is only 1
			std::cout << *searchRecord << std::endl;
			foundCtr++;
		}
		// show how many records found, if any
		searchMessage(foundCtr);

		// deallocate memory
		delete searchRecord;
		searchRecord = NULL;
	}*/
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