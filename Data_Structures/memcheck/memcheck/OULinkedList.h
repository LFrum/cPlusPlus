#ifndef OU_LINKED_LIST
#define OU_LINKED_LIST

#include "OULink.h"
#include "Comparator.h"
#include "OULinkedListEnumerator.h"

// OULinkedList stands for Ordered, Unique Linked List. It is a linked list that is always maintained in
// order (based on the comparator provided to it when the list is created) and that only contains unique
// items (that is, duplicates are not allowed)
template <typename T>
class OULinkedList {
private:
	Comparator<T>* comparator = NULL;				// used to determine list order and item equality
	unsigned long size = 0;							// actual number of items currently in list
	OULink<T>* first = NULL;						// pointer to first link in list
	OULink<T>* last = NULL;							// pointer to last link in list
													// you may add additional member variables and functions here to support the operation of your code
	OULink<T>* current = NULL;
public:
	OULinkedList(Comparator<T>* comparator);		// creates empty linked list with comparator
	virtual ~OULinkedList();						// deletes all links and their data items

	// if an equivalent item is not already present, insert item in order and return true
	// if an equivalent item is already present, leave list unchanged and return false
	bool insert(const T* item);

	// if item is greater than item at last, append item at end and return true
	// if item is less than or equal to item at last, leave list unchanged and return false
	bool append(const T* item);

	// if an equivalent item is already present, replace item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
	bool replace(const T* item);

	// if an equivalent item is already present, remove item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
	bool remove(const T* item);

	// if any items are present, return a copy of the first item
	// if no items are present, throw new ExceptionLinkedListAccess
	T get() const;

	// if an equivalent item is present, return a copy of the item
	// if an equivalent item is not present, throw a new ExceptionLinkedListAccess
	T find(const T* item) const;

	unsigned long getSize() const;					// returns the current number of items in the list

	OULinkedListEnumerator<T> enumerator() const;	// create an enumerator for this linked list
};

// put implementation for OULinkedList here
//------------------------------------------------------------------------------------------------------------------
// creates empty linked list with comparator
template <typename T>
OULinkedList<T>::OULinkedList(Comparator<T>* comparator) {
	this->comparator = comparator;		// used to determine list order and item equality
	size = 0;							// actual number of items currently in list
	first = NULL;						// pointer to first link in list
	last = NULL;						// pointer to last link in list
}

// deletes all links and their data items, set all the private members to NULL
template <typename T>
OULinkedList<T>::~OULinkedList() {
	if (comparator != NULL) {
		comparator = NULL;
	}
	if (size != 0) {
		size = 0;
	}

	OULink<T>* temp = first;
	while (first != NULL) {
		temp = first->next;
		delete first;
		first = temp;
	}

	delete temp;
	temp = NULL;
	
	delete first;
	first = NULL;
}

//------------------------------------------------------------------------------------------------------------------
// if an equivalent item is not already present, insert item in order and return true
// if an equivalent item is already present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T>::insert(const T* item) {
	bool insertStatus = false;

	if (first == NULL) { // empty list
		first = new OULink<T>(item);
		//last = new OULink<T>(item);
		last = first;
		insertStatus = true;
		size++;
	}
	else { // create a new OULink
		// new head
		if (comparator->compare(*item, *first->data) == -1) {

			if (first->next == NULL) { // new head node present
				OULink<T>* newData = new OULink<T>(item);
				newData->next = last;
				first = newData;				
				//first = new OULink<T>(item);
				//first->next = last;
				insertStatus = true;
				size++;
			}
			else { // new head node with more than one node present
				OULink<T>* newData = new OULink<T>(item);
				newData->next = first;
				first = newData;
				first->next = first;
				insertStatus = true;
				size++;
			}
		}
		else if (comparator->compare(*item, *first->data) == 0) {
			insertStatus = false;
		}
		else { // general insert
			current = first;
			while (current->next != NULL &&
				comparator->compare(*current->next->data, *item) == -1) {
				current = current->next;
			}

			// duplicate data
			if (current->next != NULL &&
				comparator->compare(*current->next->data, *item) == 0) {
				insertStatus = false;
			}
			else {// insert non-duplicate data
				  // last item 
				if (current->next == NULL) {
					append(item); // size incremented in append function
					insertStatus = true;
				}
				// item is somewhere between first and last
				else {
					OULink<T>* newData = new OULink<T>(item);
					newData->next = current->next;
					current->next = newData;
					insertStatus = true;
					size++;
				}

			}
		}
	}
	return insertStatus;
}

//------------------------------------------------------------------------------------------------------------------
// if item is greater than item at last, append item at end and return true
// if item is less than or equal to item at last, leave list unchanged and return false
template <typename T>
bool OULinkedList<T>::append(const T* item) {
	bool appendStatus = false;
	//OULink<T>* newData = new OULink<T>(item);

	if (first == NULL && last == NULL) { // empty list
		first = new OULink<T>(item);
		last = first;
		appendStatus = true;
	}
	// last data < item then append item
	else if (comparator->compare(*last->data, *item) == -1) {
		if (size == 1) {
			last = new OULink<T>(item);
			first->next = last;
		}
		else {
			OULink<T>* newData = new OULink<T>(item);
			newData->next = last->next;
			last->next = newData;
			last = newData;
		}
		appendStatus = true;
	}
	// item is less than or equal to item at last
	else {
		appendStatus = false;
	}

	if (appendStatus == true) {
		size++;
	}

	return appendStatus;
}

//------------------------------------------------------------------------------------------------------------------
// if an equivalent item is already present, replace item and return true
// if an equivalent item is not already present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T>::replace(const T* item) {
	bool replaceStatus = false;
	current = first;

	if (comparator->compare(*current->data, *item) == 0) {
		delete first->data;
		first->data = new T(*item);

		replaceStatus = true; // item is present
	}
	else {
		while (current->next != NULL && comparator->compare(*current->next->data, *item) != 0) {
			current = current->next;
		}

		if (current->next != NULL && comparator->compare(*current->next->data, *item) == 0) {
			delete current->next->data;
			current->next->data = new T(*item);

			replaceStatus = true; // item is present
		}
	}

	return replaceStatus;
}

//------------------------------------------------------------------------------------------------------------------
// if an equivalent item is already present, remove item and return true
// if an equivalent item is not already present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T>::remove(const T* item) {
	bool removeStatus = false;

	if (first == NULL) { // empty list
		removeStatus = false;
	}
	else if (comparator->compare(*first->data, *item) == 0) {
		OULink<T>* temp = first;
		first = first->next;
		delete temp;
		removeStatus = true;
	}
	else {
		current = first;
		while (current->next != NULL && comparator->compare(*current->next->data, *item) == -1) {
			current = current->next;
		}
		if (current->next == NULL) {
			removeStatus = false;
		}
		else if (comparator->compare(*current->next->data, *item) == 0) {
			OULink<T> *temp = current->next;
			current->next = current->next->next;
			delete temp;
			removeStatus = true;
		}
	}

	if (removeStatus == true) {
		size--;
	}

	return removeStatus;
}

//------------------------------------------------------------------------------------------------------------------
// if any items are present, return a copy of the first item
// if no items are present, throw new ExceptionLinkedListAccess
template <typename T>
T OULinkedList<T>::get() const {
	if (first == NULL) {
		throw new ExceptionLinkedListAccess();
	}
	else if (first->data != NULL) {
		return *first->data;
	}
	else {
		throw new ExceptionLinkedListAccess();
	}
}

//------------------------------------------------------------------------------------------------------------------
// if an equivalent item is present, return a copy of the first such item
// if an equivalent item is not present, throw a new ExceptionLinkedListAccess
template <typename T>
T OULinkedList<T>::find(const T* item) const {
	if (first == NULL) {
		throw new ExceptionLinkedListAccess();
	}
	else if (first != NULL) {
		if (comparator->compare(*first->data, *item) == 0) {
			return *first->data;
		}
		else {
			OULink<T>* currentFind = first;
			while (currentFind->next != NULL && comparator->compare(*currentFind->next->data, *item) != 0) {
				currentFind = currentFind->next;
			}

			if (currentFind->next != NULL && comparator->compare(*currentFind->next->data, *item) == 0) {
				T dataFound = *currentFind->next->data;
				return dataFound; // item is present
			}
			else { // item is not present
				throw new ExceptionLinkedListAccess(); // item is NOT present
			}
		}
	}
	// empty list
	else {
		throw new ExceptionLinkedListAccess();
	}
}

//------------------------------------------------------------------------------------------------------------------
// returns the current number of items in the list
template <typename T>
unsigned long OULinkedList<T>::getSize() const {
	return size;
}

//------------------------------------------------------------------------------------------------------------------
// create an enumerator for this linked list
template <typename T>
OULinkedListEnumerator<T> OULinkedList<T>::enumerator() const {

	//OULinkedListEnumerator<T>* currentEnumerator = new OULinkedListEnumerator<T>(first);
	//return *currentEnumerator;
	OULinkedListEnumerator<T> currentEnumerator = OULinkedListEnumerator<T>(first);
	return currentEnumerator;
}
#endif // !OU_LINKED_LIST