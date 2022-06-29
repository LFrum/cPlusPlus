#ifndef HASH_TABLE_ENUMERATOR
#define HASH_TABLE_ENUMERATOR

#include "Enumerator.h"
#include "Exceptions.h"
#include "HashTable.h"

template <typename T>
class HashTableEnumerator : public Enumerator<T>
{
private:
	unsigned long bucket = 0;								// the current bucket during the enumeration process
	OULinkedListEnumerator<T>* chainEnumerator = NULL;		// used to move through the linked list of the current bucket
	HashTable<T>* hashTable = NULL;							// pointer to the HashTable being enumerated
															// you may add additional member variables and functions here to support the operation of your code
	//OULinkedListEnumerator<T> tempEnum = NULL;				// get a temporary current bucket's linked list
	OULinkedListEnumerator<T> currentBucketEnum = NULL;		// get the current bucket's linked list

public:
	HashTableEnumerator(HashTable<T>* hashTable);			// constructor needs a pointer to the HashTable to be enumerated
	virtual ~HashTableEnumerator();
	bool hasNext() const;									// true if there are elements that have not yet been returned via next()
	T next();												// throws ExceptionEnumerationBeyondEnd if no next item is available
	T peek() const;											// throws ExceptionEnumerationBeyondEnd if no next item is available
	unsigned long getBucketEnum();
};

// put implementation for HashTableEnumerator here

// constructor needs a pointer to the HashTable to be enumerated
template <typename T>
HashTableEnumerator<T>::HashTableEnumerator(HashTable<T>* hashTable) {
	if (hashTable->getSize() == 0) {
		throw new ExceptionHashTableAccess();
	}
	else {
		this->hashTable = hashTable;
	}

	// find the first non-empty bucket
	unsigned long firstBucket = bucket;

	if (this->hashTable->table[bucket]->getSize() == 0) {
		do {
			firstBucket++;
		} while ((this->hashTable->table[firstBucket]->getSize() == 0) && firstBucket < this->hashTable->getBaseCapacity());
	}
	if (firstBucket < this->hashTable->getBaseCapacity()) {
		bucket = firstBucket;
	}
	else { // empty table
		throw new ExceptionHashTableAccess();
	}

	currentBucketEnum = this->hashTable->table[bucket]->enumerator();
	this->chainEnumerator = &currentBucketEnum; // copy memory address
	*this->chainEnumerator = currentBucketEnum; // copy data

	// empty hash table
	if (chainEnumerator == NULL) {
		throw new ExceptionHashTableAccess();
	}
}

template <typename T>
HashTableEnumerator<T>::~HashTableEnumerator() {
	chainEnumerator = NULL;
	hashTable = NULL;
}

template <typename T>
unsigned long HashTableEnumerator<T>::getBucketEnum() {
	return bucket;
}

// true if there are elements that have not yet been returned via next()
template <typename T>
bool HashTableEnumerator<T>::hasNext() const {
	//bool hasNextStatus = false;

	// check if there is next on the same bucket
	if (chainEnumerator->hasNext() == true) {
		return true;
	}
	else {
		return false;
	}
}

// throws ExceptionHashTableAccess if no next item is available
template <typename T>
T HashTableEnumerator<T>::next() {
	T nextData;

	if (chainEnumerator->hasNext() == true) {
		nextData = chainEnumerator->next();

		// check if chainEnum needs to be updated to the next non-empty bucket, if any
		if (chainEnumerator->hasNext() == false) {
			// last bucket ended, update chainEnum to the new bucket
			unsigned long nextBucket = bucket + 1;
			if (nextBucket < hashTable->getBaseCapacity()) {
				bool nonEmptyBucket = false;
				currentBucketEnum = this->hashTable->table[nextBucket]->enumerator();

				while (nextBucket < hashTable->getBaseCapacity() && nonEmptyBucket == false) {
					if (currentBucketEnum.hasNext() == true) {
						// update bucket and chainEnum
						bucket = nextBucket;
						*chainEnumerator = this->hashTable->table[bucket]->enumerator();
						nonEmptyBucket = true;
					}
					else {
						nextBucket++;
						if (nextBucket < hashTable->getBaseCapacity()) {
							currentBucketEnum = this->hashTable->table[nextBucket]->enumerator();
						}
					}
				}			
			}
		}
	}
	else {
		// no next item is avaiable
		throw new ExceptionHashTableAccess();
	}

	return nextData;
}

// throws ExceptionHashTableAccess if no next item is available
template <typename T>
T HashTableEnumerator<T>::peek() const {
	if (chainEnumerator->hasNext() == true) {
		return chainEnumerator->peek();
	}
	else {
		// no item is avaiable
		throw new ExceptionHashTableAccess();
	}
}

#endif // !HASH_TABLE_ENUMERATOR