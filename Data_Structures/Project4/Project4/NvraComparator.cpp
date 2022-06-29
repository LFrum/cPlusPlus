//NvraComparator.cpp file

// include libraries and header(s)
#include <iostream>
#include <string>
#include <algorithm>
#include "NvraComparator.h"
#include "Comparator.h"

NvraComparator::NvraComparator(unsigned int column) {
	if (column < 24) {
		this->column = column;
	}
	else {
		throw new ExceptionIndexOutOfRange();
	}	
}

// returns -1 is item1 < item2, 
// returns 0 if item1 == item2,
// returns +1 if item1 > item2
int NvraComparator::compare(const NvraRecord& item1, const NvraRecord& item2) const {
	// Check which column is being compare
	int numIndex = -1;
	int strIndex = -1;
	int result = -2;

	// Numeric column
	if (column != 3 && column != 11 && column != 12) {
		unsigned int num1 = 0;
		unsigned int num2 = 0;
		
		if (column < 3) {
			numIndex = column;
		}
		else if (column > 3 && column < 11) {
			numIndex = column - 1;
		}
		else if (column > 12 && column < 24){
			numIndex = column - 3;
		}

		// get the numeric value of each item
		num1 = item1.getNum(numIndex);
		num2 = item2.getNum(numIndex);

		// compare num1 and num2
		if (num1 < num2) {
			result = -1;
		}
		else if (num1 == num2) {
			result = 0;
		}	
		else if (num1 > num2) {
			result = 1;
		}
	}
	// String column
	else { 
		if (column == 3) {
			strIndex = 0;
		}
		else if (column == 11) {
			strIndex = 1;
		}
		else if (column == 12) {
			strIndex = 2;
		}

		// http://stackoverflow.com/questions/23418390/how-to-convert-a-c-string-to-uppercase
		// #include <algorithm> to use std::transform
		// essentially ignore case when comparing the strings

		// get the string value of each item
		// string of item1
		std::string str1 = item1.getString(strIndex);	
		std::transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
		// string of item2
		std::string str2 = item2.getString(strIndex);
		std::transform(str2.begin(), str2.end(), str2.begin(), ::toupper);

		// compare str1 and str2
		if (str1 < str2) {
			result = -1;
		}
		else if (str1 == str2) {
			result = 0;
		}
		else if (str1 > str2) {
			result = 1;
		}
	}	

	// returns -1 is item1 < item2, 
	// returns 0 if item1 == item2,
	// returns +1 if item1 > item2
	return result; 
}