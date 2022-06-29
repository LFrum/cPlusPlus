#ifndef OU_LINKED_LIST_ENUMERATOR
#define OU_LINKED_LIST_ENUMERATOR

#include "Enumerator.h"
#include "OULink.h"

template <typename T>
class OULinkedListEnumerator : public Enumerator<T>
{
private:
	OULink<T>* current;
	// you may add additional member variables and functions here to support the operation of your code
public:
	OULinkedListEnumerator(OULink<T>* first);
	virtual ~OULinkedListEnumerator();  // oops! forgot this the first time
	bool hasNext() const;
	T next();			// throws ExceptionEnumerationBeyondEnd if no next item is available
	T peek() const;		// throws ExceptionEnumerationBeyondEnd if no next item is available
};

// put implementation for OULinkedListEnumerator here

template <typename T>
OULinkedListEnumerator<T>::OULinkedListEnumerator(OULink<T>* first) {
	current = first;
}

// returns true if there is a next element
template <typename T>
bool OULinkedListEnumerator<T>::hasNext() const {
	if (current != NULL) {
		return true;
	}
	//if (current == NULL) {
	//	return false;
	//}
	//else if (current->next != NULL) {
	//	return true;
	//}
	else {
		return false;
	}
}

template <typename T>
OULinkedListEnumerator<T>::~OULinkedListEnumerator() {
}

// returns copy of next element and advances to next position
// throws ExceptionEnumerationBeyondEnd if no next item is available
template <typename T>
T OULinkedListEnumerator<T>::next() {
	if (current == NULL) {
		throw new ExceptionEnumerationBeyondEnd();
	}
	else {
		OULink<T>* newCurrent = current;
		current = current->next;
		return *newCurrent->data;
	}

}

// returns copy of next element without advancing position
// throws ExceptionEnumerationBeyondEnd if no next item is available
template <typename T>
T OULinkedListEnumerator<T>::peek() const {
	if (current == NULL) {
		throw new ExceptionEnumerationBeyondEnd();
	}
	else {
		T* item = current->data;
		return *item;
		//T* item = current->data;
		//return *current->data;
	}
}
#endif // !OU_LINKED_LIST_ENUMERATOR