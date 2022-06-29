//TemplatedArray.h

#ifndef TEMPLATED_ARRAY_H
#define TEMPLATED_ARRAY_H

#include "Exceptions.h"

const int DEFAULT_ARRAY_CAPACITY = 10;						// array's default capacity

template<typename DataType1, class DataType2>
class TemplatedArray {
private:
	DataType1 arrayCapacity;								// data value 1 capacity
	DataType1 arraySize = 0;								// data value 2 size
	DataType2* arrayValues = NULL;							// data value 3 data

public:
	TemplatedArray();										// Array contructor
	TemplatedArray(DataType1 arrayCapacity, DataType2 arrayValues);				// Array contructor with one input parameter
	virtual ~TemplatedArray();								// Array class destructor
	DataType2 get(DataType1 index);							// Get element at specified index
	void addAt(DataType2* item, DataType1 index);			// Adding item into array at specified index
	void replaceAt(DataType2* item, DataType1 index);		// Replace item into array at specified index
	void removeAt(DataType1 index);							// Remove item into array at specified index

};
#endif



template<typename DataType1, class DataType2>
TemplatedArray<DataType1, DataType2>::TemplatedArray() {
	arrayCapacity = DEFAULT_ARRAY_CAPACITY;
	arraySize = 0;
	arrayValues = new DataType2[DEFAULT_ARRAY_CAPACITY];
}

template<typename DataType1, class DataType2>
TemplatedArray<DataType1, DataType2>::TemplatedArray(DataType1 specifiedCapacity, DataType2 arrayValues) {
	arrayCapacity = specifiedCapacity;
	arraySize = (specifiedCapacity / 2) + 1;
	arrayValues = new DataType2[specifiedCapacity];
}

// frees array space as object is deleted
template<typename DataType1, class DataType2>
TemplatedArray<DataType1, DataType2>::~TemplatedArray() {
}

// returns (copy of) record at index
template<typename DataType1, class DataType2>
DataType2 TemplatedArray<DataType1, DataType2>::get(DataType1 index) {
	return arrayValues[index];
}

// Adding item into array at specified index
template<typename DataType1, class DataType2>
void TemplatedArray<DataType1, DataType2>::addAt(DataType2* item, DataType1 index) {
	bool resizeArray = false;

	// Check if index is out of bounds
	if (index > arrayCapacity - 1 || index < 0) {
		throw new ExceptionIndexOutOfRange;
	}
	// If it is not out of bounds
	else {
		// increase size of the array
		arraySize++;

		// When the next item is NULL the index is at the last index in the array
		if (arrayValues[index + 1] == NULL) {
			arrayValues[index] = item;
		}
		// When the next item is not NULL, shift the existing item to its current index + 1
		else {
			// Double the array if the size < the capacity
			if (arraySize > arrayCapacity) {
				arrayCapacity = 2 * arrayCapacity;
				resizeArray = true;
			}

			if (resizeArray == false) {
				// insert item at index
				for (int i = arraySize - 1; i < index; i--) {
					// move all entries to the next index in the array
					if (i != index) {
						arrayValues[i + 1] = arrayValues[i];
					}
					// insert item at specified index
					else {
						arrayValues[index] = item;
					}
				}
			}
			else {
				// Make a new updated array
				TemplatedArray* updatedArray = new TemplatedArray(arrayCapacity);

				// Copy all items up to index
				for (int i = 0; i < index; i++) {
					updatedArray->arrayValues[i] = arrayValues[i];
				}

				// insert item at index & copy all items after accordingly
				for (int i = arraySize - 1; i < index; i--) {
					// move all entries to the next index in the array
					if (i != index) {
						updatedArray->arrayValues[i + 1] = arrayValues[i];
					}
					// insert item at specified index
					else {
						updatedArray->arrayValues[index] = item;
					}
				}

				// Copy updated data to object's data
				delete[] arrayValues; // delete old object's data
				arrayValues = NULL; // set deleted data to null
				arrayValues = new DataType2[arrayCapacity]; // set new capacity of object's data
				arrayValues = updatedArray->arrayValues;	// copy updated data

															// deallocation of memories
				delete[] updatedArray->arrayValues;
				updatedArray->arrayValues = NULL;
				updatedArray->~TemplatedArray();
			}

		}
	}
}


// Replace item into array at specified index
template<typename DataType1, class DataType2>
void TemplatedArray<DataType1, DataType2>::replaceAt(DataType2* item, DataType1 index) {
	// Check if index is out of bounds
	if (index > arrayCapacity - 1 || index < 0) {
		throw new ExceptionIndexOutOfRange;
	}
	// If it is not out of bounds
	else {
		// Overwrite the item value at specified index
		arrayValues[index] = item;
	}
}

// Remove item into array at specified index
template<typename DataType1, class DataType2>
void TemplatedArray<DataType1, DataType2>::removeAt(DataType1 index) {
	bool resizeArray = false;
	// Check if index is out of bounds
	if (index > arrayCapacity - 1 || index < 0) {
		throw new ExceptionIndexOutOfRange;
	}
	// If it is not out of bounds
	else {
		// decrease size of the array
		arraySize--;

		// When the next item is NULL the index is at the last index in the array
		if (arrayValues[index + 1] == NULL) {
			arrayValues[index] = NULL;
		}
		// When the next item is not NULL, shift the existing item to its current index - 1
		else {
			// Double the array if the size < the capacity
			if (arraySize > 10 && (arraySize < (arrayCapacity / 2))) {
				arrayCapacity = arrayCapacity / 2;
				resizeArray = true;
			}

			if (resizeArray == false) {
				// insert item at index
				for (int i = index; i > arraySize + 1; i++) {
					// move all entries up (index before it; i.e. 3 -> 2, 4 -> 3, etc) in the array
					if (i != arraySize) {
						arrayValues[i] = arrayValues[i + 1];
					}
					// set the last item to NULL
					else {
						arrayValues[i] = NULL;
					}
				}
			}
			else {
				TemplatedArray* updatedArray = new TemplatedArray(arrayCapacity);

				for (int i = 0; i < arraySize - 1; i++) {
					updatedArray->arrayValues[i] = arrayValues[i];
				}

				// Copy updated data to object's data
				delete[] arrayValues; // delete old object's data
				arrayValues = NULL; // set deleted data to null
				arrayValues = new DataType2[arrayCapacity]; // set new capacity of object's data
				arrayValues = updatedArray->arrayValues;	// copy updated data

															// deallocation of memories
				delete[] updatedArray->arrayValues;
				updatedArray->arrayValues = NULL;
				updatedArray->~TemplatedArray();
			}

		}

	}
}
