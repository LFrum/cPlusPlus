//NvraArray.cpp file

// include libraries and header(s)
#include <iostream>
#include <string>
#include "NvraArray.h"

// constructs array with default capacity
NvraArray::NvraArray() {
	data = new NvraRecord[DEFAULT_ARRAY_CAPACITY];
}

// constructs array with specified capacity
NvraArray::NvraArray(int capacity) {
	this->capacity = capacity;
	data = new NvraRecord[capacity];
}

// frees array space as object is deleted
NvraArray::~NvraArray() {
}

// adds record, increments size, doubles capacity as necessary
void NvraArray::add(NvraRecord* record) {
	size++; // increment size array

	// record if the size is still less than its capacity
	if (size <= capacity) {
		data[size - 1] = *record;
	}
	// resize the array 
	else {
		// double the array's capacity
		capacity *= 2;

		// make an array to copy old array to
		NvraArray* updatedArray = new NvraArray(capacity);

		// copy old records
		for (int k = 0; k < size - 1; k++) {
			updatedArray->data[k] = data[k];
		}
		// add the newest item into the array
		updatedArray->data[size - 1] = *record;

		delete[] data; // delete old object's data
		data = NULL; // set deleted data to null

		data = new NvraRecord[capacity]; // set new capacity of object's data

		// copy updated data
		for (int k = 0; k < size; k++) {
			data[k] = updatedArray->data[k];
		}

		// deallocation of memories
		delete[] updatedArray->data;
		updatedArray->data = NULL;
		delete updatedArray;
	}
}
// -------------------------------------------------------------------------

// returns (copy of) record at index
NvraRecord NvraArray::get(int index) {
	return data[index];
}