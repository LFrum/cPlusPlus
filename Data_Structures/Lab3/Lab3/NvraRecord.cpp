//NvraRecord.cpp file

// include libraries and header(s)
#include <iostream>
#include <string>
#include "NvraRecord.h"

// overloaded output operator that sends one formatted record to ostream
std::ostream& operator<< (std::ostream& os, const NvraRecord& record) {
	// Maximum number of data record
	int recordMaxIndex = MAX_NUMS + MAX_STRINGS;

	int nvraRecordNumsIndex = 0; // Index for numbers
	int nvraRecordStrIndex = 0;	 // Index for strings

	for (int i = 0; i < recordMaxIndex; i++) {
		// Print integer data
		if (i != recordMaxIndex - 1 && i != 3 && i != 11 && i != 12) {		
			os << record.nums[nvraRecordNumsIndex] << ";";
			nvraRecordNumsIndex++;
		}
		// Print string data
		else if (i != recordMaxIndex - 1 && (i == 3 || i == 11 || i == 12)) {
			os << record.strings[nvraRecordStrIndex] << ";";
			nvraRecordStrIndex++;
		}
		// Print last data with a new line (We know the data is an integer)
		else {
			os << record.nums[nvraRecordNumsIndex];
		}
	}
	return os;
}

// puts num in array, increments counter
void NvraRecord::addNum(int num) {
	this->nums[numCtr] = num;
	numCtr++;
}

// puts string in array, increments counter
void NvraRecord::addString(std::string string) {
	this->strings[strCtr] = string;
	strCtr++;
}

// returns (copy of) num at index in array
int NvraRecord::getNum(int index) {
	return this->nums[index];
}

// returns (copy of) string at index in array
std::string NvraRecord::getString(int index) {
	return this->strings[index];
}