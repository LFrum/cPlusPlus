#ifndef OU_LINK_H
#define OU_LINK_H

template <typename T>
class OULink {
	template <typename T2>
	friend class OULinkedList;

	template <typename T3>
	friend class OULinkedListEnumerator;
private:
	T* data = NULL;										// pointer to data item of any type
	OULink* next = NULL;								// pointer to next link
public:
	OULink(const T* item);
	virtual ~OULink();
};

// Implementation goes here
template <typename T>
OULink<T>::OULink(const T* item) {
	data = new T;
	*data = *item;
	if (data == NULL) {
		throw new ExceptionMemoryNotAvailable();
	}
	next = NULL;
}

// delete both data and next, this should go recursively 
// if start at first, it will goes to the the end and delete all of them
// make sure next set to NULL first, if not it will delete the rest of the LinkedList
template <typename T>
OULink<T>::~OULink() {
	//if (next != NULL) {
	//	next = NULL;
	//}
	if (data != NULL) {
		delete data;
		data = NULL;
	}
}
#endif // !OU_LINK_H