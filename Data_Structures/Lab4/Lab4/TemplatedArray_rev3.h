//TemplatedArray.h
#pragma once

#ifndef TEMPLATED_ARRAY_H
#define TEMPLATED_ARRAY_H

#include "Exceptions.h"

const unsigned long DEFAULT_ARRAY_CAPACITY = 10;			// array's default capacity

template<typename DataType>
class TemplatedArray {
private:
	unsigned long int arrayCapacity;							// data value 1 capacity
	unsigned long int arraySize;								// data value 2 size
	DataType* arrayValues = NULL;								// data value 3 data

public:
	TemplatedArray();											// Array contructor
	TemplatedArray(unsigned long int specifiedCapacity);		// Array contructor with one input parameter
	virtual ~TemplatedArray();									// Array class destructor
	void add(DataType* item);
	DataType get(unsigned long int index);						// Get element at specified index
	void addAt(DataType *item, unsigned long int index);		// Adding item into array at specified index
	void replaceAt(DataType *item, unsigned long int index);	// Replace item into array at specified index
	void removeAt(unsigned long int index);						// Remove item into array at specified index
};
#endif

//------------------------------------------------------------------------------------------//
template<typename DataType>
TemplatedArray<DataType>::TemplatedArray() {
	arrayCapacity = DEFAULT_ARRAY_CAPACITY;
	arrayValues = new DataType[DEFAULT_ARRAY_CAPACITY];
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
template<typename DataType>
TemplatedArray<DataType>::TemplatedArray(unsigned long int specifiedCapacity) {
	arrayCapacity = specifiedCapacity;
	arrayValues = new DataType[specifiedCapacity];
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// frees array space as object is deleted
template<typename DataType>
TemplatedArray<DataType>::~TemplatedArray() {
	if (arrayValues != NULL) {
		delete[] arrayValues;
	}
	arrayValues = NULL;
	arraySize = 0;
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// returns (copy of) array at specified index
template<typename DataType>
void TemplatedArray<DataType>::add(DataType item) {
	arraySize++; // increment size array

				 // record if the size is still less than its capacity
	if (this->arraySize <= this->capacity) {
		this->arrayValues[arraySize - 1] = item;
	}
	// resize the array 
	else {
		int doubleCapacity = 2 * this->arrayCapacity;
		this->arrayCapacity = doubleCapacity;

		TemplatedArray<DataType>* updatedArray = new TemplatedArray(doubleCapacity);
		updatedArray->arrayValues = new NvraRecord[doubleCapacity];
		updatedArray->arrayValues = this->arrayValues;

		// copy old records
		for (int k = 0; k < size - 1; k++) {
			updatedArray->arrayValues[k] = this->arrayValues[k];
		}

		updatedArray->arrayValues[size - 1] = item;

		// Copy updated data to object's data
		delete[] data; // delete old object's data
		this->arrayValues = NULL; // set deleted data to null
		this->arrayValues = new DataType[doubleCapacity]; // set new capacity of object's data
		this->arrayValues = updatedArray->arrayValues; // copy updated data

													   // deallocation of memories
		delete[] updatedArray->arrayValues;
		updatedArray->arrayValues = NULL;
		//updatedArray->~NvraArray();
	}
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// returns (copy of) array at specified index
template<typename DataType>
DataType TemplatedArray<DataType>::get(unsigned long int index) {
	return this->arrayValues[index];
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// Adding item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::addAt(DataType *item, unsigned long int index) {
	if (index > arrayCapacity - 1) {
		throw new ExceptionIndexOutOfRange;
	}
	else {
		// increase size of the array
		this->arraySize++;

		// Double the array if the size < the capacity
		if (this->arraySize > this->arrayCapacity) {
			this->arrayCapacity = 2 * this->arrayCapacity;
		}

		// Make a new updated array
		//TemplatedArray<DataType>* updatedArray = new TemplatedArray(arrayCapacity);
		//DataType* updatedArray = new DataType[this->arrayCapacity];
		TemplatedArray<DataType>* updatedArray = new TemplatedArray(this->arrayCapacity);

		// Copying array into updated array
		// array before index
		for (unsigned long int i = 0; i < index; i++) {
			updatedArray->arrayValues[i] = this->arrayValues[i];
		}
		// array after index -- shifting original to its next index
		for (unsigned long int i = index + 1; i < arraySize; i++) {
			updatedArray->arrayValues[i] = this->arrayValues[i - 1];
		}
		// array at index
		updatedArray->arrayValues[index] = *item;
		// End of copying process

		// Copy updated data to object's data
		delete[] this->arrayValues; // delete old object's data
		this->arrayValues = NULL; // set deleted data to null
		this->arrayValues = new DataType[this->arrayCapacity]; // set new capacity of object's data
		this->arrayValues = updatedArray->arrayValues;	// copy updated data


														/*for (unsigned long int i = 0; i < arraySize; i++) {
														arrayValues[i] = updatedArray[i];
														}*/

														// deallocation of memories
		delete[] updatedArray;
		updatedArray = NULL;
		delete updatedArray;
	}
}

//------------------------------------------------------------------------------------------//
// Replace item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::replaceAt(DataType *item, unsigned long int index) {
	// Check if index is out of bounds
	if (index > arrayCapacity - 1) {
		throw new ExceptionIndexOutOfRange;
	}
	else {
		// Overwrite the item value at specified index
		this->arrayValues[index] = *item;
	}
}

//------------------------------------------------------------------------------------------//
// Remove item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::removeAt(unsigned long int index) {
	// Check if index is out of bounds
	if (index > this->arrayCapacity - 1) {
		throw new ExceptionIndexOutOfRange;
	}
	else {
		// decrease size of the array
		arraySize--;

		// Cut the array's size to half of current size if the size < the capacity
		if (this->arraySize > 10 && (this->arraySize < (this->arrayCapacity / 2))) {
			this->arrayCapacity = this->arrayCapacity / 2;
			//resizeArray = true;
		}

		//TemplatedArray<DataType>* updatedArray = new TemplatedArray(arrayCapacity);
		//DataType* updatedArray = new DataType[this->arrayCapacity];
		TemplatedArray<DataType>* updatedArray = new TemplatedArray(this->arrayCapacity);

		// array before index
		for (unsigned long int i = 0; i < index; i++) {
			updatedArray->arrayValues[i] = this->arrayValues[i];
		}
		// array after index -- shifting the array up to its next index i.e. 3 to 2
		for (unsigned long int i = index; i < arraySize; i++) {
			updatedArray->arrayValues[i] = this->arrayValues[i + 1];
		}

		// Copy updated data to object's data
		delete[] this->arrayValues; // delete old object's data
		this->arrayValues = NULL; // set deleted data to null
		this->arrayValues = new DataType[this->arrayCapacity]; // set new capacity of object's data
		this->arrayValues = updatedArray->arrayValues;	// copy updated data

														// deallocation of memories
		delete[] updatedArray;
		updatedArray = NULL;
		delete updatedArray;
	}
}
//------------------------------------------------------------------------------------------//
//-----------------------------------END OF TEMPLATE---------------------------------------//