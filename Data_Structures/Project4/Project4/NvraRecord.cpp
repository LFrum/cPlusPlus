//NvraRecord.cpp file

// include libraries and header(s)
#include <iostream>
#include <string>
#include "NvraRecord.h"

// overloaded output operator that sends one formatted record to ostream
std::ostream& operator<< (std::ostream& os, const NvraRecord& record) {
	// Maximum number of data record
	unsigned long recordMaxIndex = MAX_NUMS + MAX_STRINGS;

	unsigned long nvraRecordNumsIndex = 0; // Index for numbers
	unsigned long nvraRecordStrIndex = 0;	 // Index for strings

	for (unsigned long i = 0; i < recordMaxIndex; i++) {
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
		// Print last data (We know the data is an integer)
		else {
			os << record.nums[nvraRecordNumsIndex];
		}
	}
	return os;
}

// puts num in array, increments counter
void NvraRecord::addNum(unsigned int num) {
	if (numCtr < MAX_NUMS) {
		nums[numCtr] = num;
		numCtr++;
	}
	else {
		throw new ExceptionIndexOutOfRange();
	}
}

// puts string in array, increments counter
void NvraRecord::addString(std::string string) {
	if (strCtr < MAX_STRINGS) {
		strings[strCtr] = string;
		strCtr++;
	}
	else {
		throw new ExceptionIndexOutOfRange();
	}
}

// returns (copy of) num at index in array
unsigned int NvraRecord::getNum(unsigned int index) const {
	if (index >= MAX_NUMS) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		return nums[index];
	}
}

// returns (copy of) string at index in array
std::string NvraRecord::getString(unsigned int index) const {
	if (index >= MAX_STRINGS) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		return strings[index];
	}
}

// sets nums[index] to num, doesn't change counter
void NvraRecord::setNum(unsigned int num, unsigned int index) {
	if (index >= MAX_NUMS) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		nums[index] = num;
	}
}

// sets strings[index] to string, doesn't change counter
void NvraRecord::setString(std::string string, unsigned int index) {
	if (index >= MAX_STRINGS) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		strings[index] = string;
	}
}