//TemplatedArray.h

#ifndef TEMPLATEDARRAY_H
#define TEMPLATEDARRAY_H

#include "Exceptions.h"

const unsigned long DEFAULT_ARRAY_CAPACITY = 10;				// array's default capacity

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
	void add(DataType* item);									// adds item, increments size, doubles capacity as necessary
	DataType get(unsigned long int index);						// Get element at specified index
	void addAt(DataType *item, unsigned long int index);		// Adding item into array at specified index, increments size, doubles capacity as necessary
	void replaceAt(DataType *item, unsigned long int index);	// Replace item into array at specified index
	void removeAt(unsigned long int index);						// Remove item into array at specified index, decrements size, halves capacity as necessary
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
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// adds item, increments size, doubles capacity as necessary
template<typename DataType>
void TemplatedArray<DataType>::add(DataType *item) {
	arraySize++; // increment size array

	// record if the size is still less than its capacity
	if (arraySize <= arrayCapacity) {
		arrayValues[arraySize - 1] = *item;
	}
	// resize the array 
	else {
		// double the array's capacity
		arrayCapacity *= 2;

		// make an array to copy old array to
		TemplatedArray<DataType>* updatedArray = new TemplatedArray(arrayCapacity);		

		// copy old records
		for (unsigned long int k = 0; k < arraySize - 1; k++) {
			updatedArray->arrayValues[k] = arrayValues[k];
		}
		// add the newest item into the array
		updatedArray->arrayValues[arraySize - 1] = *item;


		delete[] arrayValues; // delete old object's data
		arrayValues = NULL; // set deleted data to null

		arrayValues = new DataType[arrayCapacity]; // set new capacity of object's data

		// copy updated data
		for (unsigned long int k = 0; k < arraySize; k++) {
			arrayValues[k] = updatedArray->arrayValues[k];
		}

		// deallocation of memories
		delete[] updatedArray->arrayValues;
		updatedArray->arrayValues = NULL;
		delete updatedArray;
	}
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// returns (copy of) array at specified index
template<typename DataType>
DataType TemplatedArray<DataType>::get(unsigned long int index) {
	if (index >= arraySize || index >= arrayCapacity) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		return this->arrayValues[index];
	}
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// Adding item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::addAt(DataType *item, unsigned long int index) {
	if (index > arraySize) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		// increase size of the array
		arraySize++;

		if (this->arraySize <= arrayCapacity) {
			// if index equal to the current nuber of items in the array
			if (index == arraySize - 1) {
				arrayValues[index] = *item;
			}
			else {
				// Copying array into updated array
				// array before index stays the same
				// array after index -- shifting original to its next index, i.e. 4 to 5
				for (unsigned long int i = arraySize - 1; i > index; i--) {
					arrayValues[i] = arrayValues[i - 1];
				}
				// array at index
				arrayValues[index] = *item;
				// End of copying process			
			}
		}
		// Double the array if the size > the capacity
		else {
			// double the capacity size of the array
			arrayCapacity *= 2;

			// Make a new updated array
			TemplatedArray<DataType>* updatedArray = new TemplatedArray(arrayCapacity);

			// ------------Copying array into updated array
			// array before index
			for (unsigned long int i = 0; i < index; i++) {
				updatedArray->arrayValues[i] = arrayValues[i];
			}
			// array after index -- shifting original to its next index
			for (unsigned long int i = index; i < arraySize - 1; i++) {
				updatedArray->arrayValues[i + 1] = arrayValues[i];
			}
			// array at index
			updatedArray->arrayValues[index] = *item;
			// ------------End of copying process

			// Copy updated data to object's data
			delete[] arrayValues; // delete old array value
			arrayValues = NULL; // set deleted memories to null

			arrayValues = new DataType[arrayCapacity]; // set new capacity of the array

			// copy updated data
			for (unsigned long int k = 0; k < arraySize; k++) {
				arrayValues[k] = updatedArray->arrayValues[k];
			}

			// deallocation of memories
			delete[] updatedArray;
			updatedArray = NULL;
			delete updatedArray;
		}
	}
}

//------------------------------------------------------------------------------------------//
// Replace item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::replaceAt(DataType *item, unsigned long int index) {
	// Check if index is out of bounds
	if (index > arraySize) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		// Overwrite the item value at specified index
		arrayValues[index] = *item;
	}
}

//------------------------------------------------------------------------------------------//
// Remove item into array at specified index
template<typename DataType>
void TemplatedArray<DataType>::removeAt(unsigned long int index) {
	// Check if index is out of bounds
	if (index < arraySize && index >= 0) {
		// Cut the array's size to half of current size if the size < the capacity
		if (arraySize > 10 && (arraySize - 1 < (arrayCapacity / 2))) {
			arrayCapacity /= 2;

			// make an array to copy old values to
			TemplatedArray<DataType>* updatedArray = new TemplatedArray(arrayCapacity);
			updatedArray->arrayValues = new DataType[arrayCapacity];

			// decrease size of the array
			arraySize--;

			// copying array before index
			for (unsigned long int i = 0; i < index; i++) {
				updatedArray->arrayValues[i] = this->arrayValues[i];
			}
			// copying array at index forward -- shifting the array up to its next index i.e. 3 to 2
			for (unsigned long int i = index; i < arraySize; i++) {
				updatedArray->arrayValues[i] = arrayValues[i + 1];
			}

			// Copy updated data to object's data
			delete[] arrayValues; // delete old array values
			arrayValues = NULL; // set deleted memories to null
			arrayValues = new DataType[arrayCapacity]; // set new capacity of the array

																   // copy updated data
			for (unsigned long int k = 0; k < arraySize; k++) {
				arrayValues[k] = updatedArray->arrayValues[k];
			}

			// deallocation of memories
			delete[] updatedArray;
			updatedArray = NULL;
			delete updatedArray;
		}
		// Keep the same capacity for the array
		else {
			// decrease size of the array
			this->arraySize--;

			// array after index -- shifting the array up to its next index i.e. 3 to 2
			for (unsigned long int i = index; i < this->arraySize; i++) {
				arrayValues[i] = arrayValues[i + 1];
			}
		}
	}
	else {
		throw new ExceptionIndexOutOfRange();
	}
}
//------------------------------------------------------------------------------------------//
//-----------------------------------END OF TEMPLATE---------------------------------------//