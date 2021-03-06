// TestData.cpp : Defines the entry point for the console application.
//

#include <iostream>

void addAt(int *item, unsigned long int index) {
	unsigned long int arraySize = 10;
	unsigned long int arrayCapacity = 10;
	int* arrayValues = new int[10];


	std::cout << "item is " << *item << " index is " << index << std::endl;

	std::cout << "arraySize is " << arraySize << " max index is " << arraySize - 1 << std::endl;

	for (int i = 0; i < arraySize; i++) {
		arrayValues[i] = i;
		std::cout << "array at " << i << ": " << arrayValues[i] << std::endl;
	}
	std::cout << std::endl;

	// increase size of the array
	arraySize++;

	std::cout << "before if statement, array size is " << arraySize << std::endl;
	if (arraySize <= arrayCapacity) {
		// if index equal to the current nuber of items in the array
		if (index == arraySize - 1) {
			arrayValues[index] = *item;
		}
		else {
			// Copying array into updated array
			// array before index stays the same
			// array after index -- shifting original to its next index, i.e. 4 to 5

			std::cout << "arraySize is " << arraySize << " max index is " << arraySize - 1 << std::endl;

			std::cout << "start at " << index + 1 << " max index is " << arraySize - 1 << std::endl;

			for (unsigned long int i = arraySize - 1; i > index; i--) {
				arrayValues[i] = arrayValues[i-1];
				std::cout << "array at " << i << ": " << arrayValues[i - 1] << std::endl;
			}
			// array at index
			arrayValues[index] = *item;

			std::cout << "array at " << index << ": " << arrayValues[index] << std::endl;
			// End of copying process			
		}
	}
	// Double the array if the size > the capacity
	else {
		// double the capacity size of the array
		unsigned long int doubledCapacity = 2 * arrayCapacity;
		arrayCapacity = doubledCapacity;
		//this->arrayValues = new DataType[this->arrayCapacity]; // set new capacity of object's data

		// Make a new updated array
		int* updatedArray = new int[arrayCapacity];

		std::cout << "arraySize is " << arraySize << " max index is " << arraySize - 1 << std::endl;

		// Copying array into updated array
		// array before index
		for (unsigned long int i = 0; i < index; i++) {
			updatedArray[i] = arrayValues[i];
			std::cout << "array at " << i << ": " << arrayValues[i] << std::endl;
		}

		for (unsigned long int i = arraySize - 1; i > index; i--) {
			updatedArray[i] = arrayValues[i - 1];
			std::cout << "array at " << i << ": " << arrayValues[i - 1] << std::endl;
		}
		// array at index
		updatedArray[index] = *item;
		std::cout << "array at " << index << ": " << *item << std::endl;

		// End of copying process

		// Copy updated data to object's data
		delete[] arrayValues; // delete old object's data
		arrayValues = NULL; // set deleted data to null

		arrayValues = new int[arrayCapacity]; // set new capacity of object's data
															   // copy updated data
		for (unsigned long int k = 0; k < arraySize; k++) {
			arrayValues[k] = updatedArray[k];
		}

		// deallocation of memories
		delete[] updatedArray;
		updatedArray = NULL;
		delete updatedArray;

	}
}
void removeAt(unsigned long int index) {
	unsigned long int arraySize = 11;
	unsigned long int arrayCapacity = 20;
	int* arrayValues = new int[arrayCapacity];

	for (int i = 0; i < arraySize; i++) {
		arrayValues[i] = i;
		std::cout << "array at " << i << ": " << arrayValues[i] << std::endl;
	}
	std::cout << std::endl;



	std::cout << "value: " << arrayValues[index] << " at index " << index << std::endl;

	std::cout << "before if statement, array size is " << arraySize << std::endl;
	
	// Cut the array's size to half of current size if the size < the capacity
	if (arraySize > 10 && (arraySize - 1 <= (arrayCapacity / 2))) {
		//unsigned long int halvesCapacity = this->arrayCapacity / 2;
		//this->arrayCapacity = halvesCapacity;
		arrayCapacity /= 2;
		std::cout << "In updated array loop with capacity of " << arrayCapacity << std::endl;

		// Make a new updated array
		int* updatedArray = new int[arrayCapacity];

		// decrease size of the array
		arraySize--;

		// array before index
		for (unsigned long int i = 0; i < index; i++) {
			updatedArray[i] = arrayValues[i];
			std::cout << "updatedArray at " << i << ": " << updatedArray[i] << std::endl;
		}
		// array after index -- shifting the array up to its next index i.e. 3 to 2
		for (unsigned long int i = index; i < arraySize; i++) {
			updatedArray[i] = arrayValues[i + 1];
			std::cout << "updatedArray at " << i << ": " << updatedArray[i] << std::endl;
		}

		std::cout << std::endl;

		// Copy updated data to object's data
		delete[] arrayValues; // delete old object's data
		arrayValues = NULL; // set deleted data to null

		arrayValues = new int[arrayCapacity]; // set new capacity of object's data
		for (unsigned long int k = 0; k < arraySize; k++) {
			arrayValues[k] = updatedArray[k];	// copy updated data
			std::cout << "arrayValues at " << k << ": " << arrayValues[k] << std::endl;
		}

		// deallocation of memories
		delete[] updatedArray;
		updatedArray = NULL;
		delete updatedArray;
	}
	else {
		// decrease size of the array
		arraySize--;
		// array before index
		std::cout << "before FOR LOOP statement, array size is " << arraySize << std::endl;

		for (unsigned long int i = 0; i < index; i++) {
			arrayValues[i] = arrayValues[i];
			std::cout << "array at " << i << ": " << arrayValues[i] << std::endl;
		}

		// array after index -- shifting the array up to its next index i.e. 3 to 2
		for (unsigned long int i = index; i < arraySize; i++) {
			arrayValues[i] = arrayValues[i + 1];

			std::cout << "array at " << i << ": " << arrayValues[i + 1] << std::endl;
		}
	}
}
int main()
{
	int a = 8;
	int* b = &a;

	addAt(b, 2);
	//removeAt(2);

    return 0;
}

