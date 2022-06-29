#ifndef OU_LINKED_LIST_ENUMERATOR
#define OU_LINKED_LIST_ENUMERATOR

#include "Enumerator.h"
#include "OULink.h"
#include "Exceptions.h"

template <typename T>
class OULinkedListEnumerator : public Enumerator<T>
{
private:
	OULink<T>* current;
public:
	OULinkedListEnumerator(OULink<T>* first);
	bool hasNext() const;
	T next();
	T peek() const;
};

// Implementation goes here

template <typename T>
OULinkedListEnumerator<T>::OULinkedListEnumerator(OULink<T>* first) {
	current = first;
}

// returns true if there is a next element
template <typename T>
bool OULinkedListEnumerator<T>::hasNext() const {
	if (current == NULL) {
		return false;
	}
	else if (current->next != NULL) {
		return true;
	}
	else {
		return false;
	}
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
	if (current != NULL) {
		T* item = current->data;
		return *item;
	}
	else {
		throw new ExceptionEnumerationBeyondEnd();
	}
}
#endif // !OU_LINKED_LIST_ENUMERATOR