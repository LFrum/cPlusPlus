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
	unsigned long int arraySize;							// data value 2 size
	DataType* arrayValues = NULL;							// data value 3 data

public:
	TemplatedArray();										// Array contructor
	TemplatedArray(unsigned long int specifiedCapacity);			// Array contructor with one input parameter
	virtual ~TemplatedArray();								// Array class destructor
	DataType get(unsigned long int index);						// Get element at specified index
	void addAt(DataType& item, unsigned long int index);		// Adding item into array at specified index
	void replaceAt(DataType& item, unsigned long int index);	// Replace item into array at specified index
	void removeAt(unsigned long int index);						// Remove item into array at specified index
};
#endif

template<typename DataType>
TemplatedArray<DataType>::TemplatedArray() {
	arrayCapacity = DEFAULT_ARRAY_CAPACITY;
	arrayValues = new DataType[DEFAULT_ARRAY_CAPACITY];
}

template<typename DataType>
TemplatedArray<DataType>::TemplatedArray(unsigned long int specifiedCapacity) {
	arrayCapacity = specifiedCapacity;
	arrayValues = new DataType[specifiedCapacity];
}

// frees array space as object is deleted
template<typename DataType>
TemplatedArray<DataType>::~TemplatedArray() {
	if (arrayValues != NULL) {
		delete[] arrayValues;
	}
	arrayValues = NULL;
	arraySize = 0;
}

// returns (copy of) array at specified index
template<typename DataType>
DataType TemplatedArray<DataType>::get(unsigned long int index) {
	return arrayValues[index];
}

// Adding item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::addAt(DataType& item, unsigned long int index) {
	bool resizeArray = false;

	// Check if index is out of bounds
	/*	if (index > arrayCapacity - 1) {
	throw new ExceptionIndexOutOfRange;
	}*/
	// If it is not out of bounds
	try {
		if (index > arrayCapacity - 1) {
			throw new ExceptionIndexOutOfRange;
		}
		//else {
		// increase size of the array
		arraySize++;

		// Double the array if the size < the capacity
		if (arraySize > arrayCapacity) {
			arrayCapacity = 2 * arrayCapacity;
			resizeArray = true;
		}

		if (resizeArray == false) {


			// insert item at index
			if (index == 0 && arraySize) {
				arrayValues[1] = arrayValues[0];
				arrayValues[0] = arrayValues[index];
			}
			else {
				for (unsigned long i = arraySize - 1; i > index; i--) {
					// move all entries to the next index in the array
					if (i != index) {
						arrayValues[i] = arrayValues[i - 1];
					}
					// insert item at specified index
					else {
						arrayValues[index] = item;
					}
				}
			}
		}
		else {
			// Make a new updated array
			TemplatedArray<DataType>* updatedArray = new TemplatedArray(arrayCapacity);

			// Copy all items up to index
			for (unsigned long i = 0; i < index; i++) {
				updatedArray->arrayValues[i] = arrayValues[i];
			}

			for (unsigned long i = arraySize - 1; i < index; i--) {
				// move all entries to the next index in the array
				if (i != index) {
					updatedArray->arrayValues[i] = arrayValues[i - 1];
				}
				// insert item at specified index
				else {
					updatedArray->arrayValues[index] = item;
				}
			}

			// Copy updated data to object's data
			delete[] arrayValues; // delete old object's data
			arrayValues = NULL; // set deleted data to null
			arrayValues = new DataType[arrayCapacity]; // set new capacity of object's data
			arrayValues = updatedArray->arrayValues;	// copy updated data

														// deallocation of memories
			delete[] updatedArray->arrayValues;
			updatedArray->arrayValues = NULL;
			updatedArray->~TemplatedArray();
		}
		//}
	}
	catch (ExceptionIndexOutOfRange) {
		std::cout << "Index out of range!" << std::endl;
	}
}

// Replace item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::replaceAt(DataType& item, unsigned long int index) {
	/*	// Check if index is out of bounds
	if (index > arrayCapacity - 1) {
	throw new ExceptionIndexOutOfRange;
	}
	// If it is not out of bounds
	else {
	// Overwrite the item value at specified index
	arrayValues[index] = item;
	}
	*/

	try {
		// Check if index is out of bounds
		if (index > arrayCapacity - 1) {
			throw new ExceptionIndexOutOfRange;
		}
		// Overwrite the item value at specified index
		arrayValues[index] = item;
	}
	catch (ExceptionIndexOutOfRange) {
		std::cout << "Index out of range!" << std::endl;
	}
}

// Remove item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::removeAt(unsigned long int index) {
	bool resizeArray = false;
	/*	// Check if index is out of bounds
	if (index > arrayCapacity - 1) {
	throw new ExceptionIndexOutOfRange;
	}
	*/
	try {
		// If it is not out of bounds
		//	else {

		// Check if index is out of bounds
		if (index > arrayCapacity - 1) {
			throw new ExceptionIndexOutOfRange;
		}

		// decrease size of the array
		arraySize--;

		// Cut the array's size to half of current size if the size < the capacity
		if (arraySize > 10 && (arraySize < (arrayCapacity / 2))) {
			arrayCapacity = arrayCapacity / 2;
			resizeArray = true;
		}

		if (resizeArray == false) {
			// insert item at index
			for (unsigned long int i = index; i < arraySize; i++) {
				// move all entries up (index before it; i.e. 3 -> 2, 4 -> 3, etc) in the array
				if (i != arraySize) {
					arrayValues[i] = arrayValues[i + 1];
				}
			}
		}
		else {
			TemplatedArray<DataType>* updatedArray = new TemplatedArray(arrayCapacity);

			for (unsigned long int i = 0; i < index; i++) {
				updatedArray->arrayValues[i] = arrayValues[i];
			}

			for (unsigned long int i = index; i < arraySize; i++) {
				updatedArray->arrayValues[i] = arrayValues[i + 1];
			}

			// Copy updated data to object's data
			delete[] arrayValues; // delete old object's data
			arrayValues = NULL; // set deleted data to null
			arrayValues = new DataType[arrayCapacity]; // set new capacity of object's data
			arrayValues = updatedArray->arrayValues;	// copy updated data

														// deallocation of memories
			delete[] updatedArray->arrayValues;
			updatedArray->arrayValues = NULL;
			updatedArray->~TemplatedArray();
		}
	}
	//	}
	catch (ExceptionIndexOutOfRange) {
		std::cout << "Index out of range!" << std::endl;
	}
}