#ifndef HASH_TABLE
#define HASH_TABLE

#include "Exceptions.h"
#include "Comparator.h"
#include "OULinkedList.h"
#include "OULinkedListEnumerator.h"
#include "Hasher.h"
#include <math.h>

const unsigned int SCHEDULE_SIZE = 25;			// the number of items in the size schedule
const unsigned int SCHEDULE[SCHEDULE_SIZE] = { 1, 2, 5, 11, 23, 53, 107, 223, 449, 907, 1823, 3659, 7309, 14621, 29243, 58511, 117023, 234067, 468157, 936319, 1872667, 3745283, 7490573, 14981147, 29962343 };		// the size schedule (all primes)
const unsigned int DEFAULT_SCHEDULE_INDEX = 3;	// the default position in the size schedule
const unsigned long DEFAULT_BASE_CAPACITY = SCHEDULE[DEFAULT_SCHEDULE_INDEX]; 	// the default size of the array
const float DEFAULT_MAX_LOAD_FACTOR = 0.9f;		// the default load factor used to determine when to increase the table size
const float DEFAULT_MIN_LOAD_FACTOR = 0.4f;		// the default load factor used to determine when to decrease the table size
//const unsigned long DEFAULT_TABLE_SIZE = floor(DEFAULT_BASE_CAPACITY*DEFAULT_MAX_LOAD_FACTOR);

template <typename T>
class HashTable {
	template <typename U>
	friend class HashTableEnumerator;						// necessary to allow the enumerator to access the table's private data
private:
	Comparator<T>* comparator = NULL;						// used to determine item equality
	Hasher<T>* hasher = NULL;								// used to compute hash value
	unsigned long size = 0;									// actual number of items currently in hash table
	float maxLoadFactor = DEFAULT_MAX_LOAD_FACTOR;			// the load factor used to determine when to increase the table size
	float minLoadFactor = DEFAULT_MIN_LOAD_FACTOR;			// the load factor used to determine when to decrease the table size
	unsigned int scheduleIndex = DEFAULT_SCHEDULE_INDEX;	// the index of current location in the size schedule
	unsigned long baseCapacity = DEFAULT_BASE_CAPACITY;		// the size of the array
	unsigned long totalCapacity = baseCapacity;				// the size of the array plus chains of more than one link
	OULinkedList<T>** table = NULL;							// table will be an array of pointers to OULinkedLists of type T
															// you may add additional member variables and functions here to support the operation of your code
	//OULinkedList<T>** newTable = NULL;
	//unsigned long bucketCtr = 0;							// the number of bucket that is not empty
//	void expandTable(OULinkedList<T>** currentTable);		// increase the capacity of table to fit the current data
//	void shrinkTable(OULinkedList<T>** currentTable);		// decrease the capacity of table to fit the current data
//	void copyTable(OULinkedList<T>** oldTable,
//		unsigned long newBaseCapacity);						// copy table value
	void expandTable();										// increase the capacity of table to fit the current data
	void shrinkTable();										// decrease the capacity of table to fit the current data
	void copyTable(unsigned long newBaseCapacity);			// copy table value
public:
	HashTable(Comparator<T>* comparator, Hasher<T>* hasher);			// creates an empty table of DEFAULT_BASE_CAPACITY
	HashTable(Comparator<T>* comparator, Hasher<T>* hasher,
		// if size given, creates empty table with size from schedule of sufficient capacity (considering maxLoadFactor)
		unsigned long size,
		float maxLoadFactor = DEFAULT_MAX_LOAD_FACTOR,
		float minLoadFactor = DEFAULT_MIN_LOAD_FACTOR);
	virtual ~HashTable();

	// if an equivalent item is not already present, insert item at proper location and return true
	// if an equivalent item is already present, leave table unchanged and return false
	bool insert(const T* item);

	// if an equivalent item is already present, replace item and return true
	// if an equivalent item is not already present, leave table unchanged and return false
	bool replace(const T* item);

	// if an equivalent item is already present, remove item and return true
	// if an equivalent item is not already present, leave table unchanged and return false
	bool remove(const T* item);

	// if an equivalent item is present, return a copy of the item
	// if an equivalent item is not present, throw a new ExceptionHashTableAccess
	T find(const T* item) const;

	unsigned long getSize() const;						// returns the current number of items in the table
	unsigned long getBaseCapacity() const;				// returns the current base capacity of the table
	unsigned long getTotalCapacity() const;				// returns the current total capacity of the table
	float getLoadFactor() const;						// returns the current load factor of the table
	unsigned long getBucketNumber(const T* item) const;	// returns the bucket number for an item using its hash function mod array size
};

// put implementation for HashTable here

// creates an empty table of DEFAULT_BASE_CAPACITY
template <typename T>
HashTable<T>::HashTable(Comparator<T>* comparator, Hasher<T>* hasher) {	
	this->comparator = comparator;
	this->hasher = hasher;	
	this->size = 0;
	this->maxLoadFactor = DEFAULT_MAX_LOAD_FACTOR;
	this->minLoadFactor = DEFAULT_MIN_LOAD_FACTOR;
	this->scheduleIndex = DEFAULT_SCHEDULE_INDEX;
	this->baseCapacity = DEFAULT_BASE_CAPACITY;
	this->totalCapacity = baseCapacity;
	this->table = new OULinkedList<T>* [DEFAULT_BASE_CAPACITY];

	if (table == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}
	else{
		for (unsigned long i = 0; i < DEFAULT_BASE_CAPACITY; i++)
		{
			table[i] = new OULinkedList<T>(comparator);
			if (table[i] == NULL) {
				throw new ExceptionMemoryNotAvailable();
			}
		}
	}

}

template <typename T>
HashTable<T>::HashTable(Comparator<T>* comparator, Hasher<T>* hasher,
	// if size given, creates empty table with size from schedule of sufficient capacity (considering maxLoadFactor)
	unsigned long size, float maxLoadFactor, float minLoadFactor) {
	this->comparator = comparator;
	this->hasher = hasher;
	this->size = size;
	this->maxLoadFactor = maxLoadFactor;
	this->minLoadFactor = minLoadFactor;

	// pick a new scheduleIndex based on maxLoadFactor
	scheduleIndex = 0;
	unsigned long initialTotalCapacity = SCHEDULE[scheduleIndex];
	float currentLoadFactor = (float) size / (float) initialTotalCapacity;

	while (currentLoadFactor > maxLoadFactor) {
		// increment index
		scheduleIndex++;
		// update capacities and load factor
		baseCapacity = SCHEDULE[scheduleIndex];
		// initialize totalCapacity as baseCapacity and add overflow data if any later on
		totalCapacity = baseCapacity;
		currentLoadFactor = (float)size / (float)totalCapacity;
	}

	baseCapacity = SCHEDULE[scheduleIndex];
	totalCapacity = baseCapacity; // initialize as baseCapacity and add overflow data if any
	table = new OULinkedList<T>* [baseCapacity];

	if (table == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}
	else {
		for (unsigned long i = 0; i < baseCapacity; i++)
		{
			table[i] = new OULinkedList<T>(comparator);
			if (table[i] == NULL) {
				throw new ExceptionMemoryNotAvailable();
			}
		}
	}

}

template <typename T>
HashTable<T>::~HashTable() {
	// set all pointer variables to NULL
	if (comparator != NULL) {
		comparator = NULL;
	}
	if (hasher != NULL) {
		hasher = NULL;
	}
	if (table != NULL) {		
		for (unsigned long i = 0; i < baseCapacity; i++) {
			if (table[i] != NULL) {
				delete table[i];
				table[i] = NULL;
			}
		}
		delete[] table;
		table = NULL;
	}

	// set other variables to their default values
	size = 0;
	maxLoadFactor = DEFAULT_MAX_LOAD_FACTOR;
	minLoadFactor = DEFAULT_MIN_LOAD_FACTOR;
	scheduleIndex = DEFAULT_SCHEDULE_INDEX;
	baseCapacity = DEFAULT_BASE_CAPACITY;
	totalCapacity = baseCapacity;
}

// increase the capacity of table to fit the current data
template <typename T>
//void HashTable<T>::expandTable(OULinkedList<T>** currentTable) {
void HashTable<T>::expandTable() {
	scheduleIndex++;
	// new base capacity
	unsigned long newBaseCap = SCHEDULE[scheduleIndex];

	copyTable(newBaseCap);
}

// decrease the capacity of table to fit the current data
template <typename T>
//void HashTable<T>::shrinkTable(OULinkedList<T>** currentTable) {
void HashTable<T>::shrinkTable() {
	scheduleIndex--;
	// new base capacity
	unsigned long newBaseCap = SCHEDULE[scheduleIndex];

	copyTable(newBaseCap);
}

// decrease the capacity of table to fit the current data
template <typename T>
//void HashTable<T>::copyTable(OULinkedList<T>** oldTable, unsigned long newBaseCapacity) {
void HashTable<T>::copyTable(unsigned long newBaseCapacity) {
	//create a new hashTable with increased/decreased capacity
	OULinkedList<T>** newTable = new OULinkedList<T>* [newBaseCapacity];
	if (newTable == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}

	for (unsigned long i = 0; i < newBaseCapacity; i++){
		newTable[i] = new OULinkedList<T>(comparator);
		if (newTable[i] == NULL) {
			throw new ExceptionMemoryNotAvailable();
		}
	}	

	// put data from old table into the new table and rehashing all data
	for (unsigned int bucketNum = 0; bucketNum < baseCapacity; bucketNum++){
		// create enumerator for current table
		OULinkedListEnumerator<T> currentTableEnum = table[bucketNum]->enumerator();

		// go through the list in the bucket if any
		while (currentTableEnum.hasNext() == true){
			// get new bucket number for the new table
			unsigned long newBucketNum = hasher->hash(currentTableEnum.peek()) % newBaseCapacity;
			// get current data
			T currentData = currentTableEnum.next();

			// insert current data into new table
			newTable[newBucketNum]->insert(&currentData);
		}
	}

/*
	// remove data from old table
	for (unsigned int bucketNum = 0; bucketNum < baseCapacity; bucketNum++) {
		// create enumerator for current table
		OULinkedListEnumerator<T> currentTableEnum = table[bucketNum]->enumerator();

		// go through the list in the bucket if any
		while (currentTableEnum.hasNext() == true) {
			// get current data
			T currentData;
			currentData = currentTableEnum.next();
			// insert current data into new table
			table[bucketNum]->remove(&currentData);
		}
	}	
*/

	// deallocate old table
	for (unsigned long i = 0; i < baseCapacity; i++) {
		delete table[i];
		table[i] = NULL;
	}

	delete[] table;
	table = NULL;
	
	//table = new OULinkedList<T>*[newBaseCapacity];
	// overwrite global table with newTable
	//table = newTable;


	// create a new global table with new base capacity
	table = new OULinkedList<T>*[newBaseCapacity];

	for (unsigned long i = 0; i < newBaseCapacity; i++) {
		table[i] = new OULinkedList<T>(comparator);
	}

	// put data from new table into the global table
	for (unsigned int bucketNum = 0; bucketNum < newBaseCapacity; bucketNum++) {
		// create enumerator for current table
		OULinkedListEnumerator<T> newTableEnum = newTable[bucketNum]->enumerator();

		// go through the list in the bucket if any
		while (newTableEnum.hasNext() == true) {
			// get current data
			T currentData = newTableEnum.next();
			// insert current data into global table
			table[bucketNum]->insert(&currentData);
		}
	}
/*
	// remove all data from temporary new table
	for (unsigned int bucketNum = 0; bucketNum < newBaseCapacity; bucketNum++) {
		// create enumerator for current table
		OULinkedListEnumerator<T> newTableEnum = table[bucketNum]->enumerator();

		// go through the list in the bucket if any
		while (newTableEnum.hasNext() == true) {
			// get current data
			T currentData;
			currentData = newTableEnum.next();
			// remove data from new table
			newTable[bucketNum]->remove(&currentData);
		}
	}
*/
	// deallocate newTable
	for (unsigned long i = 0; i < newBaseCapacity; i++) {
		delete newTable[i];
		newTable[i] = NULL;
	}

	delete[] newTable;
	newTable = NULL;

	baseCapacity = newBaseCapacity;
	totalCapacity = baseCapacity;
}

// if an equivalent item is not already present, insert item at proper location and return true
// if an equivalent item is already present, leave table unchanged and return false
template <typename T>
bool HashTable<T>::insert(const T* item) {
	bool insertStatus = false;		
	// find the bucket number of item
	unsigned long bucketNum = getBucketNumber(item);

	// try to insert item into the bucket
	insertStatus = table[bucketNum]->insert(item);

	if (insertStatus == true) {
		// increment size of hash table
		size++;

		// overflow item, increment total capacity
		if (table[bucketNum]->getSize() > 1)
		{
			totalCapacity++;
		}

		float currentLoadFactor = (float)size / (float)baseCapacity;

		if (currentLoadFactor > maxLoadFactor) {
			expandTable();
		}
	}	

	return insertStatus;
}

// if an equivalent item is already present, replace item and return true
// if an equivalent item is not already present, leave table unchanged and return false
template <typename T>
bool HashTable<T>::replace(const T* item) {
	bool replaceStatus = false;

	// find the bucket number of item
	unsigned long bucketNum = getBucketNumber(item);

	// find the item needed to be replace
	if (table[bucketNum]->getSize() > 0) {
		replaceStatus = table[bucketNum]->replace(item);
	}

	return replaceStatus;
}

// if an equivalent item is already present, remove item and return true
// if an equivalent item is not already present, leave table unchanged and return false
template <typename T>
bool HashTable<T>::remove(const T* item) {
	bool removeStatus = false;
	// find the bucket number of item
	unsigned long bucketNum = getBucketNumber(item);

	// find the item needed to be removed
	if (table[bucketNum]->getSize() > 0) {
		removeStatus = table[bucketNum]->remove(item);
	}
	
	// if not found, return false
	if (removeStatus == true) {
		// overflow item decrease by 1
		if (table[bucketNum]->getSize() > 1)
		{
			totalCapacity--;
		}

		// decrease size of hash table
		size--;

		// calculate current load factor
		float currentLoadFactor = (float)size / (float)baseCapacity;

		if (currentLoadFactor < minLoadFactor) {
			shrinkTable();
		}
	}

	return removeStatus;
}

// if an equivalent item is present, return a copy of the item
// if an equivalent item is not present, throw a new ExceptionHashTableAccess
template <typename T>
T HashTable<T>::find(const T* item) const {
	// find the bucket number of item
	unsigned long bucketNum = getBucketNumber(item);

	if (table[bucketNum]->getSize() != 0) {
		// find in OULinkedList
		return table[bucketNum]->find(item);
	}
	// empty list
	else {
		throw new ExceptionHashTableAccess();
	}
}

// returns the current number of items in the table
template <typename T>
unsigned long HashTable<T>::getSize() const {
	return size;
}

// returns the current base capacity of the table
template <typename T>
unsigned long HashTable<T>::getBaseCapacity() const {
	return baseCapacity;
}

// returns the current total capacity of the table
template <typename T>
unsigned long HashTable<T>::getTotalCapacity() const {
	return totalCapacity;
}

// returns the current load factor of the table
template <typename T>
float HashTable<T>::getLoadFactor() const {
	return (float) size / (float) totalCapacity;
}

// returns the bucket number for an item using its hash function mod array size
template <typename T>
unsigned long HashTable<T>::getBucketNumber(const T* item) const {
	return hasher->hash(*item) % baseCapacity;
}
#endif // !HASH_TABLE