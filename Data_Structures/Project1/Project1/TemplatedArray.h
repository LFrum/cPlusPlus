// These definitions may be used as a basis for your templated array class. However, you are
// not required to use them exactly as they are. You may change details as you see fit.
// Nonetheless, you must retain the signatures of all public member functions (methods) and
// their described functionality, so that they may be used in unit tests.

#ifndef TEMPLATED_ARRAY_H
#define TEMPLATED_ARRAY_H

#include "Exceptions.h"

const unsigned long DEFAULT_ARRAY_CAPACITY = 10;		// capacity used in no arg constructor

template <typename T>
class TemplatedArray {
private:
	unsigned long capacity = DEFAULT_ARRAY_CAPACITY;	// maximum capacity, in items
	unsigned long size = 0;								// actual number of items currently in array
	T* data = NULL;										// pointer to array of any type
	void doubleCapacity();								// method to double array capacity
	void halveCapacity();								// method to halve array capacity 
public:
	TemplatedArray();								    // constructs array with default capacity
	TemplatedArray(unsigned long capacity);			    // constructs array with specified capacity
	virtual ~TemplatedArray();						    // frees array space as object is deleted
	void add(const T* item);						    // adds item, increments size, doubles capacity as necessary
	void addAt(const T* item, unsigned long index);	    // adds item at index, shifts following, doubles capacity as necessary
	void replaceAt(const T* item, unsigned long index); // replaces item at index, otherwise unchanged
	void removeAt(unsigned long index);				    // removes item at index, shifts following back
	T get(unsigned long index) const;				    // returns (copy of) item at index
	unsigned long getCapacity() const;				    // returns the current capacity of the array
	unsigned long getSize() const;					    // returns the current number of items in the array
	T operator[](unsigned long index) const;		    // returns (copy of) item at index
};

// implementation goes here

// method to double array capacity
template <typename T>
void TemplatedArray<T>::doubleCapacity() {
	capacity *= 2;
}
// method to halve array capacity 
template <typename T>
void TemplatedArray<T>::halveCapacity() {
	capacity /= 2;
}

// constructs array with default capacity
template <typename T>
TemplatedArray<T>::TemplatedArray() {
	capacity = DEFAULT_ARRAY_CAPACITY;
	data = new T[DEFAULT_ARRAY_CAPACITY];
	if (data == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}
}
// constructs array with specified capacity
template <typename T>
TemplatedArray<T>::TemplatedArray(unsigned long capacity) {
	this->capacity = capacity;
	data = new T[capacity];
	if (data == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}
}
// frees array space as object is deleted
template<typename DataType>
TemplatedArray<DataType>::~TemplatedArray() {
	delete[] data;
}

// adds item, increments size, doubles capacity as necessary
template <typename T>
void TemplatedArray<T>::add(const T* item) {
	unsigned long index = size; // specified what index item is going to
	addAt(item, index); // use the addAt function to add the item
}
// adds item at index, shifts following, doubles capacity as necessary
template <typename T>
void TemplatedArray<T>::addAt(const T* item, unsigned long index) {
	if (index > size) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		// increase size of the array
		size++;

		if (size <= capacity) {
			// if index equal to the current number of items in the array
			if (index == size - 1) {
				data[index] = *item;
			}
			else {
				// Copying array into updated array
				// array before index stays the same
				// array after index -- shifting original to its next index, i.e. 4 to 5
				for (unsigned long int i = size - 1; i > index; i--) {
					data[i] = data[i - 1];
				}
				// array at index
				data[index] = *item;
				// End of copying process			
			}
		}
		// Double the array if the size > the capacity
		else {
			// double the capacity size of the array
			doubleCapacity();

			// Make a new updated array
			TemplatedArray<T>* updatedArray = new TemplatedArray(capacity);
			// Check if memory is available
			if (updatedArray != NULL) {
				// ------------Copying array into updated array
				// array before index
				for (unsigned long int i = 0; i < index; i++) {
					updatedArray->data[i] = data[i];
				}
				// array after index -- shifting original to its next index
				for (unsigned long int i = index; i < size - 1; i++) {
					updatedArray->data[i + 1] = data[i];
				}
				// array at index
				updatedArray->data[index] = *item;
				// ------------End of copying process

				// Copy updated data to object's data
				delete[] data; // delete old array value
				data = NULL; // set deleted memories to null
				data = new T[capacity]; // set new capacity of the array
				// Check if memory is available
				if (data != NULL) {
					// copy updated data
					for (unsigned long int k = 0; k < size; k++) {
						data[k] = updatedArray->data[k];
					}

					// deallocation of memories
					delete updatedArray;
					updatedArray = NULL;
					//delete updatedArray;
				}
				else {
					throw new ExceptionMemoryNotAvailable();
				}
			}
			else {
				throw new ExceptionMemoryNotAvailable();
			}
		}
	}
}

// replaces item at index, otherwise unchanged
template <typename T>
void TemplatedArray<T>::replaceAt(const T* item, unsigned long index) {
	// Check if index is out of bounds
	if (index >= size) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		// Overwrite the item value at specified index
		data[index] = *item;
	}
}

// removes item at index, shifts following back
template <typename T>
void TemplatedArray<T>::removeAt(unsigned long index) {
	// Check if index is out of bounds
	if (index < size && index >= 0) {
		// Cut the array's size to half of current size if the size < the capacity
		if (size > 10 && (size - 1 < (capacity / 2))) {
			// halves capacity
			halveCapacity();

			// make an array to copy old values to
			TemplatedArray<T>* updatedArray = new TemplatedArray(capacity);
			if (updatedArray != NULL){
				// decrease size of the array
				size--;

				// copying array before index
				for (unsigned long int i = 0; i < index; i++) {
					updatedArray->data[i] = data[i];
				}
				// copying array at index forward -- shifting the array up to its next index i.e. 3 to 2
				for (unsigned long int i = index; i < size; i++) {
					updatedArray->data[i] = data[i + 1];
				}

				// Copy updated data to object's data
				delete[] data; // delete old array values
				data = NULL; // set deleted memories to null
				data = new T[capacity]; // set new capacity of the array

				if (data != NULL) {
					// copy updated data
					for (unsigned long int k = 0; k < size; k++) {
						data[k] = updatedArray->data[k];
					}

					// deallocation of memories
					delete updatedArray;
					updatedArray = NULL;
					//delete updatedArray;
				}
				else {
					throw new ExceptionMemoryNotAvailable();
				}
			}
			else {
				throw new ExceptionMemoryNotAvailable();
			}
		}
		// Keep the same capacity for the array
		else {
			// decrease size of the array
			this->size--;

			// array after index -- shifting the array up to its next index i.e. 3 to 2
			for (unsigned long int i = index; i < this->size; i++) {
				data[i] = data[i + 1];
			}
		}
	}
	else {
		throw new ExceptionIndexOutOfRange();
	}
}

// returns (copy of) item at index
template <typename T>
T TemplatedArray<T>::get(unsigned long index) const {
	if (index >= size || index >= capacity) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		return data[index];
	}
}
// returns the current capacity of the array
template <typename T>
unsigned long TemplatedArray<T>::getCapacity() const {
	return capacity;
}
// returns the current number of items in the array
template <typename T>
unsigned long TemplatedArray<T>::getSize() const {
	return size;
}
// returns (copy of) item at index
template <typename T>
T TemplatedArray<T>::operator[](unsigned long index) const {
	if (index >= size || index >= capacity) {
		throw new ExceptionIndexOutOfRange();
	}
	else {
		return data[index];
	}
}
#endif