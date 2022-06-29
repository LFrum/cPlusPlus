//TemplatedArray.h

#ifndef TEMPLATED_ARRAY_H
#define TEMPLATED_ARRAY_H

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
	this->arrayCapacity = DEFAULT_ARRAY_CAPACITY;
	this->arrayValues = new DataType[DEFAULT_ARRAY_CAPACITY];
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
template<typename DataType>
TemplatedArray<DataType>::TemplatedArray(unsigned long int specifiedCapacity) {
	this->arrayCapacity = specifiedCapacity;
	this->arrayValues = new DataType[specifiedCapacity];
	new TemplatedArray[specifiedCapacity];
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// frees array space as object is deleted
template<typename DataType>
TemplatedArray<DataType>::~TemplatedArray() {
	if (this->arrayValues != NULL) {
		delete[] this->arrayValues;
	}
	this->arrayValues = NULL;
	this->arraySize = 0;
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// adds item, increments size, doubles capacity as necessary
template<typename DataType>
void TemplatedArray<DataType>::add(DataType *item) {
	arraySize++; // increment size array

				 // record if the size is still less than its capacity
	if (this->arraySize <= this->arrayCapacity) {
		this->arrayValues[arraySize - 1] = *item;
	}
	// resize the array 
	else {
		//double the capacity of the array
		this->arrayCapacity *= 2;

		TemplatedArray<DataType>* updatedArray = new TemplatedArray(this->arrayCapacity);
		updatedArray->arrayValues = new DataType[this->arrayCapacity];

		// copy old records
		updatedArray->arrayValues = this->arrayValues;
		// add the newest item into the array
		updatedArray->arrayValues[arraySize - 1] = *item;

		delete[] arrayValues; // delete old object's data
		this->arrayValues = NULL; // set deleted data to null

		this->arrayValues = new DataType[this->arrayCapacity]; // set new capacity of object's data

															   // copy updated data
		this->arrayValues = updatedArray->arrayValues;

		// deallocation of memories
		delete[] updatedArray->arrayValues;
		updatedArray->arrayValues = NULL;
		//updatedArray->~TemplatedArray();
		delete updatedArray;
	}
}
//------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------//
// returns (copy of) array at specified index
template<typename DataType>
DataType TemplatedArray<DataType>::get(unsigned long int index) {
	if (index > this->arraySize) {
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
	if (index > this->arraySize) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		// increase size of the array
		this->arraySize++;

		if (this->arraySize <= this->arrayCapacity) {
			// if index equal to the current number of items in the array
			if (index == this->arraySize - 1) {
				this->arrayValues[index] = *item;
			}
			else {
				// -------------Copying array into updated array
				// array before index stays the same
				// array after index -- shifting original to its next index, i.e. 4 to 5
				for (unsigned long int i = this->arraySize - 1; i > index; i--) {
					this->arrayValues[i] = this->arrayValues[i - 1];
				}
				// array at index
				this->arrayValues[index] = *item;
				// -------------End of copying process			
			}
		}
		// arraySize > arrayCapacity
		// Double the array if the size > the capacity
		else {
			// double the capacity size of the array
			this->arrayCapacity *= 2;

			// Make a new updated array
			TemplatedArray<DataType>* updatedArray = new TemplatedArray(this->arrayCapacity);

			// --------Copying array into updated array
			// array before index
			for (unsigned long int i = 0; i < index; i++) {
				updatedArray->arrayValues[i] = this->arrayValues[i];
			}

			// array after index -- shifting original to its next index
			for (unsigned long int i = this->arraySize - 1; i > index; i--) {
				updatedArray->arrayValues[i] = this->arrayValues[i - 1];
			}

			// array at index
			updatedArray->arrayValues[index] = *item;
			// --------End of copying process


			delete[] this->arrayValues; // delete old object's data
			this->arrayValues = NULL; // set deleted data to null

			this->arrayValues = new DataType[this->arrayCapacity]; // set new capacity of object's data

			this->arrayValues = updatedArray->arrayValues; // copy updated data

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
	if (index > this->arraySize) {
		throw new ExceptionIndexOutOfRange();
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
	if (index > this->arraySize - 1 || index > this->arrayCapacity || index < 0) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		// decrease size of the array
		this->arraySize--;

		if (this->arraySize >(this->arrayCapacity / 2)) {
			// array after index -- shifting the array up to its next index i.e. 3 to 2
			for (unsigned long int i = index; i < this->arraySize; i++) {
				this->arrayValues[i] = this->arrayValues[i + 1];
			}
		}
		// Cut the array's capacity to half of the current capacity if size < capacity/2
		else {
			// Update array's capacity to 1/2 its original capacity
			this->arrayCapacity /= 2;

			TemplatedArray<DataType>* updatedArray = new TemplatedArray(this->arrayCapacity);

			// array before index
			for (unsigned long int i = 0; i < index; i++) {
				updatedArray->arrayValues[i] = this->arrayValues[i];
			}
			// array after index -- shifting the array up to its next index i.e. 3 to 2
			for (unsigned long int i = index; i < this->arraySize; i++) {
				updatedArray->arrayValues[i] = this->arrayValues[i + 1];
			}

			delete[] this->arrayValues; // delete old object's data
			this->arrayValues = NULL; // set deleted data to null

									  // set new capacity of object's data
			this->arrayValues = new DataType[this->arrayCapacity];

			this->arrayValues = updatedArray->arrayValues;

			// deallocation of memories
			delete[] updatedArray;
			updatedArray = NULL;
			delete updatedArray;
		}
	}
}
//------------------------------------------------------------------------------------------//
//-----------------------------------END OF TEMPLATE---------------------------------------//