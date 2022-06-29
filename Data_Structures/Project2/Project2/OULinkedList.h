// Chapter 4 Linked List Structures Class PowerPoint

#ifndef OU_LINKED_LIST
#define OU_LINKED_LIST

#include "OULink.h"
#include "Comparator.h"
#include "OULinkedListEnumerator.h"
#include "Exceptions.h"

// OULinkedList stands for Ordered, Unique Linked List. It is a linked list that is always maintained in
// order (based on the comparator provided to it when the list is created) and that only contains unique
// items (that is, duplicates are not allowed)
template <typename T>
class OULinkedList {
	template <typename T2>
	friend class OULinkedListEnumerator;
private:
	Comparator<T>* comparator = NULL;				// used to determine list order and item equality
	unsigned long size = 0;							// actual number of items currently in list
	OULink<T>* first = NULL;						// pointer to first link in list
	OULink<T>* last = NULL;							// pointer to last link in list
public:
	OULinkedList(Comparator<T>* comparator);		// creates empty linked list with comparator
	virtual ~OULinkedList();						// deletes all links and their data items, set all the private members to NULL

	// if an equivalent item is not already present, insert item in order and return true
	// if an equivalent item is already present, leave list unchanged and return false
	bool insert(const T* item);

	// if item is greater than item at last, append item at end and return true
	// if item is less than or equal to item at last, leave list unchanged and return false
	bool append(const T* item);

	// if an equivalent item is already present, replace item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
	bool replace(T* item);

	// if an equivalent item is already present, remove item and return true
	// if an equivalent item is not already present, leave list unchanged and return false
	bool remove(T* item);

	// if any items are present, return a copy of the first item
	// if no items are present, throw new ExceptionLinkedListAccess
	T get() const;

	// if an equivalent item is present, return a copy of the first such item
	// if an equivalent item is not present, throw a new ExceptionLinkedListAccess
	T find(const T* item) const;

	unsigned long getSize() const;					// returns the current number of items in the list

	OULinkedListEnumerator<T> enumerator() const;	// create an enumerator for this linked list
};

// Implementation goes here
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
	if (first != NULL) {
		first = NULL;
	}
	if (last != NULL) {
		last = NULL;
	}
}

//------------------------------------------------------------------------------------------------------------------
// if an equivalent item is not already present, insert item in order and return true
// if an equivalent item is already present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T>::insert(const T* item) {
	bool insertStatus = false;

	if (first == NULL) { // empty list
		first = new OULink<T>(item);
		last = new OULink<T>(item);
		insertStatus = true;
		size++;
	}
	else { // create a new OULink
		OULink<T>* newData = new OULink<T>(item); 
		// new head
		if (comparator->compare(*item, *first->data) == -1) {
			
			if (first->next == NULL) { // only 1 node present
				newData->next = last;
				first = newData;
				//first->next = last;
				insertStatus = true;
				size++;
			}
			else { // new first with more than one node present
				newData->next = first;
				first = newData;
				insertStatus = true;
				size++;
			}
		}
		else if (comparator->compare(*item, *first->data) == 0) {			
			insertStatus = false;
		}
		else { // general insert
			OULink<T>* current = first;
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
				else{
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
		last = new OULink<T>(item);
		appendStatus = true;
	}
	// last data < item then append item
	else if (comparator->compare(*last->data, *item) == -1) {
		OULink<T>* newLast = new OULink<T>(item);
		OULink<T>* temp = last;
		
		if (size == 1) {
			newLast->next = temp->next;
			temp->next = newLast;
			last = newLast;	
			first->next = last;
		}
		else {
			newLast->next = temp->next;
			temp->next = newLast;
			last = newLast;		
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
bool OULinkedList<T>::replace(T* item) {
	bool replaceStatus = false;
	OULink<T>* current = first;
	OULink<T>* newItem = new OULink<T>(item);

	if (comparator->compare(*current->data, *item) == 0) {
		newItem->next = first->next;
		first = newItem;
		replaceStatus = true; // item is present
	}
	else {
		while (current->next != NULL && comparator->compare(*current->next->data, *item) != 0) {
			current = current->next;
		}

		if (comparator->compare(*current->next->data, *item) == 0) {
			newItem->next = current->next->next;
			current->next = newItem;
			replaceStatus = true; // item is present
		}
	}

	return replaceStatus;
}

//------------------------------------------------------------------------------------------------------------------
// if an equivalent item is already present, remove item and return true
// if an equivalent item is not already present, leave list unchanged and return false
template <typename T>
bool OULinkedList<T>::remove(T* item) {
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
		OULink<T>* current = first;
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
			OULink<T>* current = first;
			while (current->next != NULL && comparator->compare(*current->next->data, *item) != 0) {
				current = current->next;
			}

			if (current->next != NULL && comparator->compare(*current->next->data, *item) == 0) {
				return *current->next->data; // item is present
			}
			else { // item is not present
				throw new ExceptionLinkedListAccess(); // item is NOT present
			}
		}
	}
	// empty list
	else{
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
	OULinkedListEnumerator<T>* currentEnumerator = new OULinkedListEnumerator<T>(first);
	return *currentEnumerator;
}
#endif // !OU_LINKED_LIST