/*
Lince Rumainum
Student ID: 112722337
CS2413 Data Structure
Project 4 VoteR4.cpp
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
#include "AVLTree.h"
#include "AVLTreeEnumerator.h"
#include "AVLTreeOrder.h"


// List of functions
void takeInput();
// option: 'i' for initial file, 'm' for merge file, 'p' for purge file
void processInput(std::string fileName, char option);
void optionMenu();
void storeToArray();
void outputData();
void processOutput(std::ostream& os);
void mergeData();
void mergeTrees();
void purgeData();
void purgedTrees();
void printList();
void printOutLL(std::ostream& os);
void storeToHashTable();
void printHashTable();
void printOutHashTable(std::ostream& os);
void avlTree(std::string order);
void printAVLTree(std::ostream& os, AVLTreeOrder currentTreeOrder);
void sortData();
void findData();
void processSearchNum(unsigned int col, unsigned int num, NvraComparator* searchCol);
void processSearchStr(unsigned int col, std::string str, NvraComparator* searchCol);
void searchMessage(unsigned int foundCount);
void printOutTallies(std::ostream& os);

// Global variables
typedef TemplatedArray<NvraRecord> NvraArray;
NvraArray* storedNvraArray = new NvraArray(); // array of all data across all of the files

NvraComparator* compareColID = new NvraComparator(0);

typedef OULinkedList<NvraRecord> recordList;
recordList* storedList = new recordList(compareColID); // list of all data across all of the files

NvraHasher* idHasher = new NvraHasher[1];
typedef HashTable<NvraRecord> recordHashTable;
recordHashTable* idHashTable = new HashTable<NvraRecord>(compareColID, idHasher); // hash table based of record ID

typedef AVLTree<NvraRecord> recordsTree;
recordsTree* avlTreeRecords = new recordsTree(compareColID);	// avl tree of records
recordsTree* mergedTree = new recordsTree(compareColID);		// avl tree of merged records
recordsTree* purgedTree = new recordsTree(compareColID);		// avl tree of purged records

unsigned long totalLineCount = 0;			// The total lines number read
unsigned long totalValidData = 0;			// Valid records read
unsigned long totalRecordsInMemory = 0;		// All records without invalid data & duplicate IDs

int invalidCtr = 0;				// counter for invalid data input
int duplicateCtr = 0;			// counter for duplicate ID input
int purgedDuplicateCtr = 0;		// counter for duplicate ID input during purge
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

		// valid data process
		if (isInvalidData == false) {
			bool insertSuccessful = false;

			// initial file
			if (option == 'i') {				
				// if recordData inserted then it is NOT a duplicate
				insertSuccessful = avlTreeRecords->insert(recordData);
				if (insertSuccessful == false) {
					// duplicate is found, increment its counter
					duplicateCtr++;
					// Send error message out for the duplicate record ID
					std::cout << "Duplicate record ID " << recordData->getNum(0) << " at line " << lineCount << "." << std::endl;
				}
			}
			// purging file
			else if (option == 'p') {
				// insert data into the purged tree
				// this tree will be purged to existing tree later on
				purgedTree->insert(recordData);

				// purged data should not being count as totalRecordsInMemory
				// therefore count as duplicate here
				duplicateCtr++;
			}
			// merging file
			else if (option == 'm') {
				try {
					// insert data into the merged tree
					// this tree will be merged to existing main tree in parallel later on
					insertSuccessful = mergedTree->insert(recordData);

					if (insertSuccessful == false) { // duplicate within its own file
						// duplicate is found, increment its counter
						duplicateCtr++;

						// Send error message out for the duplicate record ID
						std::cout << "Duplicate record ID " << recordData->getNum(0) << " at line " << lineCount << "." << std::endl;
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
			storeToHashTable();
		}
	}
}
// --------------- END OF INPUT LOOP --------------- 

// --------------- OPTION LOOP --------------- 
void optionMenu() {
	// output option variable
	std::string option;

	do {
		// Get user options choice
		std::cout << "Enter (o)utput, (s)ort, (f)ind, (m)erge, (p)urge, (h)ash table, (pre)order, (in)order, (post)order or (q)uit: ";
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
		// User choose hash table
		else if (option == "h") {
			printHashTable();
		}
		// User choose preorder
		else if (option == "pre") {
			avlTree(option);
		}
		// User choose inorder
		else if (option == "in") {
			avlTree(option);
		}
		// User choose postorder
		else if (option == "post") {
			avlTree(option);
		}
	} while (option != "q"); // will quit the program when 'q' is entered
}
// --------------- END OF OPTION LOOP --------------- 

// user choose pre/in/post-order
void avlTree(std::string order) {
	AVLTreeOrder treeOrder;

	if (order == "pre") {
		treeOrder = AVLTreeOrder::preorder;
	}
	else if (order == "in") {
		treeOrder = AVLTreeOrder::inorder;
	}
	else if (order == "post") {
		treeOrder = AVLTreeOrder::postorder;
	}

	std::string outputFileName;
	std::ofstream outputFile;
	bool errorFile = false;

	do {
		// Get file name from user
		std::cout << "Enter output file name: ";
		getline(std::cin, outputFileName);

		// Output to console
		if (outputFileName == "") {
			printAVLTree(std::cout, treeOrder);
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
				printAVLTree(outputFile, treeOrder);
				// END OF OUTPUT TO FILE
				outputFile.close();
			}
		}
	} while (errorFile == true);
}

void printAVLTree(std::ostream& os, AVLTreeOrder currentTreeOrder) {
	if (avlTreeRecords->getSize() > 0) {
		typedef AVLTreeEnumerator<NvraRecord> recordTreeEnum;
		recordTreeEnum treeEnum = recordTreeEnum(avlTreeRecords, currentTreeOrder);
		unsigned long treeEnumSize = treeEnum.stackSize();

		try {
			for (unsigned long i = 0; i < treeEnumSize; i++) {
				try {
					os << treeEnum.next() << std::endl;
				}
				catch (ExceptionEnumerationBeyondEnd) {
					os << "Enumeration beyond end!" << std::endl;
				}
			}
		}
		catch (ExceptionEnumerationBeyondEnd) {
			os << "Enumeration beyond end!" << std::endl;
		}
	}
	// Print out internal tallies
	printOutTallies(os);
}

void storeToArray() {
	NvraRecord* recordData = NULL;
	// delete the old stored array and make a new one
	delete storedNvraArray;
	storedNvraArray = NULL;
	//storedNvraArray = new NvraArray();
	storedNvraArray = new NvraArray(avlTreeRecords->getSize());

	if (avlTreeRecords->getSize() > 0) {
		// create tree enumerator
		typedef AVLTreeEnumerator<NvraRecord> recordTreeEnum;
		recordTreeEnum treeEnum = recordTreeEnum(avlTreeRecords, AVLTreeOrder::inorder);
		unsigned long treeEnumSize = treeEnum.stackSize();

		try {
			for (unsigned long i = 0; i < treeEnumSize; i++) {
				recordData = new NvraRecord[1];
				try {
					// put tree node into the array
					*recordData = treeEnum.next();
					storedNvraArray->add(recordData);
				}
				catch (ExceptionEnumerationBeyondEnd) {
					std::cout << "Enumeration beyond end!" << std::endl;
				}
				delete[] recordData;
				recordData = NULL;
			}
		}
		catch (ExceptionEnumerationBeyondEnd) {
			std::cout << "Enumeration beyond end!" << std::endl;
		}
	}
}

// User choose hash table
void printHashTable() {
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
			printOutHashTable(std::cout);
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
				printOutHashTable(outputFile);
				outputFile.close();
				// END OF OUTPUT TO FILE
			}
		}
	} while (errorFile == true);
}

void printOutHashTable(std::ostream& os) {
	typedef HashTableEnumerator<NvraRecord> recordHashTable;
	//recordHashTable* hashTableEnum = new recordHashTable(idHashTable);
	recordHashTable hashTableEnum = recordHashTable(idHashTable);

	try {
		unsigned long bucketCtr = 0;
		for (unsigned long i = 0; i < idHashTable->getBaseCapacity(); i++) {
			// print data in the bucket to console
			unsigned long j = 0;
			unsigned long currentBucketEnum = hashTableEnum.getBucketEnum();

			// check if i is the current data's bucket number
			while (i == currentBucketEnum && hashTableEnum.hasNext()) {
				try {
					if (j == 0) { // first data in the bucket
						if (bucketCtr > 0) {
							// extra space between the buckets
							os << std::endl;
						}

						os << i << ": ";
						os << hashTableEnum.next() << std::endl;
						bucketCtr++;
					}
					else { // overflow data
						os << "OVERFLOW: ";
						os << hashTableEnum.next() << std::endl;
					}
					j++;
					// update current bucket
					currentBucketEnum = hashTableEnum.getBucketEnum();
				}
				catch (ExceptionHashTableAccess) {
					os << "Exception Hash Table Enumeration Beyond End!" << std::endl;
				}
			}
		}

	}
	catch (ExceptionHashTableAccess) {
		os << "Enumeration beyond end!" << std::endl;
	}

	// Print out hash table tallies and internal tallies
	os << std::endl;
	os << "Base Capacity: " << idHashTable->getBaseCapacity() << "; "
		<< "Total Capacity: " << idHashTable->getTotalCapacity() << "; "
		<< "Load Factor: " << idHashTable->getLoadFactor() << std::endl;
	printOutTallies(os);
}

void storeToHashTable() {
	// current data being read in
	NvraRecord* recordData = NULL;
	// delete the old hash table and make a new one
	delete idHashTable;
	idHashTable = NULL;

	if (avlTreeRecords->getSize() > 0) {
		// create tree enumerator
		typedef AVLTreeEnumerator<NvraRecord> recordTreeEnum;
		recordTreeEnum treeEnum = recordTreeEnum(avlTreeRecords, AVLTreeOrder::inorder);
		unsigned long treeEnumSize = treeEnum.stackSize();
		idHashTable = new HashTable<NvraRecord>(compareColID, idHasher, treeEnumSize); // hash table based of record ID

		try {
			for (unsigned long i = 0; i < treeEnumSize; i++) {
				recordData = new NvraRecord[1];
				try {
					// put tree node into the hash table
					*recordData = treeEnum.next();
					idHashTable->insert(recordData);
				}
				catch (ExceptionEnumerationBeyondEnd) {
					std::cout << "Enumeration beyond end!" << std::endl;
				}
				delete[] recordData;
				recordData = NULL;
			}
		}
		catch (ExceptionEnumerationBeyondEnd) {
			std::cout << "Enumeration beyond end!" << std::endl;
		}
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
				mergedTree = new recordsTree(compareColID);
				processInput(inputFileName, 'm'); // read input file
				inputFile.close(); // close file
				// merged avl trees
				mergeTrees();
				// store to array and hash table
				storeToArray();
				storeToHashTable();

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

void mergeTrees() {
	NvraComparator* compareID = NULL;
	compareID = new NvraComparator(0);

	// copy existing tree to a temporary tree
	typedef AVLTree<NvraRecord> recordsTree;
	recordsTree* tempTree = new recordsTree(compareID);
	tempTree = avlTreeRecords;
	*tempTree = *avlTreeRecords;
	avlTreeRecords = NULL;
	// create a new avl tree of records
	avlTreeRecords = new recordsTree(compareID);

	// create temp tree & merged tree enumerator
	typedef AVLTreeEnumerator<NvraRecord> recordTreeEnum;
	recordTreeEnum tempEnum = recordTreeEnum(tempTree, AVLTreeOrder::inorder);
	recordTreeEnum mergedEnum = recordTreeEnum(mergedTree, AVLTreeOrder::inorder);

	// insert the temp & merged trees in parrallel
	while (tempEnum.hasNext() && mergedEnum.hasNext()) {
		// merge data < old data
		if (compareID->compare(mergedEnum.peek(), tempEnum.peek()) == -1) {
			NvraRecord temp = mergedEnum.next();
			NvraRecord *recordData = new NvraRecord();
			recordData = &temp;

			avlTreeRecords->insert(recordData);
		}
		// merge data > old data
		else if (compareID->compare(mergedEnum.peek(), tempEnum.peek()) == 1) {
			NvraRecord temp = tempEnum.next();
			NvraRecord *recordData = new NvraRecord();
			recordData = &temp;

			avlTreeRecords->insert(recordData);
		}
		// merge data = old data, keep the new merged data
		else if (compareID->compare(mergedEnum.peek(), tempEnum.peek()) == 0) {
			NvraRecord temp = mergedEnum.next();
			NvraRecord *recordData = new NvraRecord();
			recordData = &temp;

			avlTreeRecords->insert(recordData);
			// duplicate, skip the current old data
			tempEnum.next();

			// duplicate is found, increment its counter
			duplicateCtr++;
		}
	}

	// insert the rest of temp tree, if any
	while (tempEnum.hasNext()) {
		NvraRecord temp = tempEnum.next();
		NvraRecord *recordData = new NvraRecord();
		recordData = &temp;
		avlTreeRecords->insert(recordData);
	}
	// insert the rest of merged tree, if any
	while (mergedEnum.hasNext()) {
		NvraRecord temp = mergedEnum.next();
		NvraRecord *recordData = new NvraRecord();
		recordData = &temp;
		avlTreeRecords->insert(recordData);
	}

	// update totalRecordsInMemory
	totalRecordsInMemory -= duplicateCtr;
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
				purgedTree = new recordsTree(compareColID);
				processInput(inputFileName, 'p'); // read input file
				inputFile.close(); // close file

				// purged avl trees
				purgedTrees();
				// store to array and hash table
				storeToArray();
				storeToHashTable();

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

void purgedTrees() {
	bool isItemRemoved = false;
	// create purgedEnum tree enumerator
	typedef AVLTreeEnumerator<NvraRecord> recordTreeEnum;
	recordTreeEnum purgedEnum = recordTreeEnum(purgedTree, AVLTreeOrder::inorder);

	while(purgedEnum.hasNext()){
		NvraRecord temp = purgedEnum.next();
		NvraRecord *recordData = new NvraRecord();
		recordData = &temp;

		// remove purge data from the main avl tree
		isItemRemoved = avlTreeRecords->remove(recordData);

		if (isItemRemoved == true) {
			// duplicate found, increment counter
			purgedDuplicateCtr++;
		}
	}
	// update totalRecordsInMemory
	totalRecordsInMemory -= purgedDuplicateCtr;
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
			printOutLL(std::cout);
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
				printOutLL(outputFile);
				// Close output file
				outputFile.close();
			}
		}
	} while (errorFile == true);	
}

void printOutLL(std::ostream& os) {
	try {
		OULinkedListEnumerator<NvraRecord> listOfRecords = storedList->enumerator();

		for (unsigned long i = 0; i < storedList->getSize(); i++) {
			// print to file
			try {
				os << listOfRecords.next() << std::endl;
			}
			catch (ExceptionEnumerationBeyondEnd) {
				os << "Exception Enumeration Beyond End!" << std::endl;
			}
		}
	}
	catch (ExceptionEnumerationBeyondEnd) {
		os << "Enumeration beyond end!" << std::endl;
	}

	// Print out internal tallies
	printOutTallies(os);

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
				processOutput(outputFile);
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
		os << "Index out of range!" << std::endl;
	}
	// Print out internal tallies
	printOutTallies(os);
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

	// the specified column is NOT sorted - do Linear Search
	if (colSorted != col) {
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

// Print out internal tallies
void printOutTallies(std::ostream& os) {
	os << "Data lines read: " << totalLineCount << "; "
		<< "Valid NVRA records read: " << totalValidData << "; "
		<< "NVRA records in memory: " << totalRecordsInMemory << std::endl;
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