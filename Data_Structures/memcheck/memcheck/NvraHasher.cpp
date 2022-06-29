//NvraHasher.cpp file

// include libraries and header(s)
#include <iostream>
#include "NvraHasher.h"

// implement a hash function appropriate for NvraRecords in NvraHasher.cpp
unsigned long NvraHasher::hash(const NvraRecord& item) const {
	// return the hash value, which is the record ID number of the NvraRecord
	return item.getNum(0);
}