// Signature must be retained. Implementation must be added.

#ifndef SEARCH_H
#define SEARCH_H

#include "Exceptions.h"
#include "TemplatedArray.h"
#include "Comparator.h"

// returns FIRST array location matching the given item (based on the comparator)
template <typename T>
long long binarySearch(const T& item, const TemplatedArray<T>& array, const Comparator<T>& comparator) {

	// implementation goes here
	
	long long low = 0;
	long long mid = 0;
	long long high = array.getSize() - 1;
	long long indexFound = -1;
	bool isfound = false;

	while (high >= low && isfound == false) {
		mid = (low + high) / 2;
		//if (key < list[mid])
		if (comparator.compare(item, array[mid]) == -1) {
			high = mid - 1;		
		}
		//else if (key == list[mid])
		else if (comparator.compare(item, array[mid]) == 0) {
			indexFound = mid;
			isfound = true;
		}
		else {// can also write: else if (key > list[mid])
			low = mid + 1;
		}
	}

	//}

	if (isfound == true) {
		int compareItem = 0; // 0 indicates it's the same item
		// look for the FIRST array location matching the given item 
		do {			
			if (indexFound > 0) {
				indexFound--;
				compareItem = comparator.compare(item, array[indexFound]);
			}
		} while (indexFound > 0 && compareItem == 0);

		// if indexFound = 0 and compareItem = 0, it's a match else it is not
		if ( indexFound != 0 || (indexFound == 0 && compareItem != 0) ) {
			// because the last comparison will be false, we have to add 1
			// if it's at index 0 and it's not the search item
			indexFound++;		
		}
	}
	else {
		indexFound = -(low + 1) ; // Now high < low can also be written as -(low + 1) or -low - 1
	}
	return indexFound;
}

#endif