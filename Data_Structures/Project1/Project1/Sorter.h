// Signature must be retained. Implementation must be added.
// Use quick sort algorithm from psuedocode Data Structure CS 2413 class exam I
// Signature must be retained. Implementation must be added.
#ifndef SORT_H
#define SORT_H

#include "Exceptions.h"
#include "TemplatedArray.h"
#include "Comparator.h"
#include <math.h> 

template <typename T>
class Sorter {
private:
	// additional member functions (methods) and variables (fields) may be added
	static void quicksort(TemplatedArray<T>& numbers, unsigned long left, unsigned long right, const Comparator<T>& comparator);
public:
	static void sort(TemplatedArray<T>& array, const Comparator<T>& comparator);
};

// implementation goes here
template<typename T>
void Sorter<T>::sort(TemplatedArray<T>& array, const Comparator<T>& comparator) {
	// Do quicksort
	quicksort(array, 0, array.getSize() - 1, comparator);
}

// Quicksort implementation
template<typename T>
void Sorter<T>::quicksort(TemplatedArray<T>& items, unsigned long left, unsigned long right, const Comparator<T>& comparator) {
	if (left < right) {
		unsigned long i = 0; // low
		unsigned long j = 0; // high
		unsigned long midpoint = 0; // pivot point

		unsigned long iCounter = 0;
		T* tempLow = NULL;
		T* tempHigh = NULL;

		// Pick middle element as pivot
		midpoint = (unsigned long) floor((left + right) / 2);

		// starting index on the left side of pivot
		if (left != 0) {
			i = left - 1;
		}
		else {
			i = left;
		}

		// starting index on the right side of pivot
		j = right + 1;

		do {
			// if item at index i <= items at index midpoint then increment i
			do {
				if (i != 0) {
					i++;
				}
				else if (i == 0 && iCounter > 0) {
					i++;
				}
				else if (i == 0 && iCounter == 0) {
					iCounter++;
				}
			} while (i < items.getSize() && (comparator.compare(items[i], items[midpoint]) == -1 ||
				comparator.compare(items[i], items[midpoint]) == 0));

			// if item at index j >= items at index midpoint then decrement j
			do {
				if (j != 0) {
					j--;
				}
			} while (j!=0 && j >= i && (comparator.compare(items[midpoint], items[j]) == -1 ||
				comparator.compare(items[midpoint], items[j]) == 0));

			// swap items at index i and j
			if (i < j) {
				tempLow = new T[1];
				tempHigh = new T[1];

				if (tempLow != NULL && tempHigh != NULL) {
					// Swap numbers on i and j index
					// update i and j
					*tempLow = items[i];
					*tempHigh = items[j];
					items.replaceAt(tempHigh, i);
					items.replaceAt(tempLow, j);

					// deallocation memories
					delete[] tempLow;
					tempLow = NULL;
					delete[] tempHigh;
					tempHigh = NULL;
				}
				else {
					throw ExceptionMemoryNotAvailable();
				}
			}
		} while (i < j);

		if (i < midpoint) {
			j = i;
		}

		// swap items at index midpoint and j
		tempLow = new T[1];
		tempHigh = new T[1];

		if (tempLow != NULL && tempHigh != NULL) {
			// Swap numbers on midpoint and j index
			// update midpoint and j
			*tempLow = items[j];
			*tempHigh = items[midpoint];
			items.replaceAt(tempHigh, j);
			items.replaceAt(tempLow, midpoint);

			// deallocation memories
			delete[] tempLow;
			tempLow = NULL;
			delete[] tempHigh;
			tempHigh = NULL;
		}
		else {
			throw ExceptionMemoryNotAvailable();
		}

		// recursion
		if (j != 0) {
			quicksort(items, left, j - 1, comparator);
		}
		if (j != items.getSize() - 1) {
			quicksort(items, j + 1, right, comparator);
		}
	}
}
#endif