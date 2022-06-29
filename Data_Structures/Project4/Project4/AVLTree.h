// AVLTree.h
// code help : powerpoint slides &
// Data Structures Featuring C++
// A Programmer's Persperctive
// by Dr. Sridhar Radhakrishnan, Dr. Wise, & Dr. Sekharan
// Chapter 6 & 7

#ifndef AVL_TREE
#define AVL_TREE
#include "Comparator.h"
#include "Exceptions.h"

template <typename T>
class AVLTree {
	template <typename U>
	friend class AVLTreeEnumerator;
private:
	Comparator<T>* comparator = NULL;				// used to determine tree order and item equality
	unsigned long size = 0;							// actual number of items currently in tree
	T* data = NULL;									// pointer to data at this node
	int diff = 0;									// height of right minus height of left
	AVLTree<T>* left = NULL;						// pointer to left subtree
	AVLTree<T>* right = NULL;						// pointer to right subtree
	void zig();										// right rotation
	void zag();										// left rotation
	void zigzag();									// left rotation on left subtree, followed by right rotation
	void zagzig();									// right rotation on right subtree, followed by left rotation
	void rebalance();								// check for and rebalance this node, if needed
public:
	AVLTree(Comparator<T>* comparator);				// creates empty linked tree with comparator
	virtual ~AVLTree();								// deletes all links and their data items

													// if an equivalent item is not already present, insert item in order and return true
													// if an equivalent item is already present, leave tree unchanged and return false
	bool insert(const T* item);

	// if an equivalent item is already present, replace item and return true
	// if an equivalent item is not already present, leave tree unchanged and return false
	bool replace(const T* item);

	// if an equivalent item is already present, remove item and return true
	// if an equivalent item is not already present, leave tree unchanged and return false
	bool remove(const T* item);

	// if an equivalent item is present, return a copy of the item
	// if an equivalent item is not present, throw a new ExceptionLinkedtreeAccess
	T find(const T* item) const;

	unsigned long getSize() const;					// returns the current number of items in the tree
};

// add public functions here

// creates empty linked tree with comparator
template<typename T>
AVLTree<T>::AVLTree(Comparator<T>* comparator) {
	this->comparator = comparator;	// used to determine tree order and item equality
	size = 0;						// actual number of items currently in tree
	data = NULL;					// pointer to data at this node
	diff = 0;						// height of right minus height of left
	left = NULL;					// pointer to left subtree
	right = NULL;					// pointer to right subtree
}

// deletes all links and their data items
template<typename T>
AVLTree<T>::~AVLTree() {
	this->size = 0;
	this->diff = 0;
	if (this->comparator != NULL) {
		this->comparator = NULL;
	}

	if (this->data != NULL) {
		delete this->data;
	}
	this->data = NULL;

	if (this->left != NULL) {
		delete this->left;
	}
	this->left = NULL;

	if (this->right != NULL) {
		delete this->right;
	}
	this->right = NULL;
}

// if an equivalent item is not already present, insert item in order and return true
// if an equivalent item is already present, leave tree unchanged and return false
template<typename T>
bool AVLTree<T>::insert(const T* item) {
	bool insertStatus = false;
	int oldDiff = 0;
	T* newItem = new T(*item);

	// empty tree
	if (this->data == NULL && this->size == 0) {
		data = newItem;
		insertStatus = true;
	}
	// make a new leaf node
	else {
		// check if it item < data
		if (comparator->compare(*item, *this->data) == -1) {
			if (this->left == NULL) { // new left child
				AVLTree<T> *newNode = new AVLTree<T>(comparator);
				//*newNode->data = *newItem;
				newNode->data = newItem;

				left = newNode;
				//left->data = newItem;
				this->diff--; // -1 difference
				insertStatus = true;
			}
			else { // compare with existing left child recursively
				oldDiff = left->diff;
				insertStatus = left->insert(item);
				if (oldDiff != left->diff && left->diff != 0) {
					this->diff--;
				}
			}
		}
		// check if it item > data
		else if (comparator->compare(*item, *this->data) == 1) {
			if (right == NULL) { // new right child
				AVLTree<T> *newNode = new AVLTree<T>(comparator);
				//*newNode->data = *item;
				newNode->data = newItem;

				right = newNode;
				//right->data = newItem;
				this->diff++; // +1 difference
				insertStatus = true;
			}
			else { // compare with existing right child recursively
				oldDiff = right->diff;
				insertStatus = right->insert(item);
				if (oldDiff != right->diff && right->diff != 0) {
					this->diff++;
				}
			}
		}
	}

	rebalance();
	if (insertStatus == true) {
		size++;
	}
	return insertStatus;
}

// if an equivalent item is already present, replace item and return true
// if an equivalent item is not already present, leave tree unchanged and return false
template<typename T>
bool AVLTree<T>::replace(const T* item) {
	bool replaceStatus = false;

	// current data = item
	if (comparator->compare(*data, *item) == 0) {
		T* newItem = new T(*item);
		//*this->data = *item;
		*data = *newItem;
		replaceStatus = true;
	}
	// current item < data
	else if (comparator->compare(*item, *data) == -1) {
		if (left != NULL) {
			replaceStatus = left->replace(item);
		}
	}
	// current item > data
	else if (comparator->compare(*item, *data) == 1) {
		if (right != NULL) {
			replaceStatus = right->replace(item);
		}
	}

	return replaceStatus;
}

// if an equivalent item is already present, remove item and return true
// if an equivalent item is not already present, leave tree unchanged and return false
template<typename T>
bool AVLTree<T>::remove(const T* item) {
	bool removeStatus = false;
	int oldDiff = 0;

	if (data == NULL && size == 0) {
		return false;
	}
	else {
		// check if it item < data
		if (comparator->compare(*item, *this->data) == -1) {
			if (left == NULL)return false;
			oldDiff = left->diff;
			if (!left->remove(item))return false;
			removeStatus = true;

			if (left != NULL && left->data == NULL) {
				delete left;
				left = NULL;
				diff++;
			}

			else if ((left == NULL) || (left->diff != oldDiff && left->diff == 0)) {
				diff++;
			}
		}
		else if (comparator->compare(*item, *this->data) == 1) {
			if (right == NULL)return false;
			oldDiff = right->diff;
			if (!right->remove(item)) return false;
			removeStatus = true;

			if (right != NULL && right->data == NULL) {
				delete right;
				right = NULL;
				diff--;
			}

			else if ((right == NULL) || (right->diff != oldDiff && right->diff == 0)) {
				diff--;
			}
		}
		else {
			removeStatus = true;
			// unconditionally delete data
			delete data;
			data = NULL;

			// two children -> get successor
			if (right != NULL && left != NULL) {
				// find inorder successor
				AVLTree<T>* inordSucc = right;
				while (inordSucc->left != NULL) {
					inordSucc = inordSucc->left;
				}
				data = new T(*(inordSucc->data));

				oldDiff = this->right->diff;

				// delete inorder successor
				this->right->remove(inordSucc->data);

				if (right != NULL && right->data == NULL) {
					delete right;
					right = NULL;
					diff--;
				}
				else if ((this->right == NULL) || (this->right->diff != oldDiff && this->right->diff == 0)) {
					diff--;
				}

			}
			// one child to left
			else if (left != NULL) {
				// reset data
				data = new T(*left->data);

				// reset left
				delete left;
				left = NULL;

				// reset diff
				this->diff = 0;
			}
			// one child to right
			else if (right != NULL) {
				// reset data
				data = new T(*right->data);

				// reset right
				delete right;
				right = NULL;

				// reset diff
				this->diff = 0;
			}
		}
	}

	if (removeStatus == true) {
		size--;
		rebalance();
	}
	return removeStatus;
}


// if an equivalent item is present, return a copy of the item
// if an equivalent item is not present, throw a new ExceptionLinkedtreeAccess
template<typename T>
T AVLTree<T>::find(const T* item) const {
	T dataFound;

	// empty tree
	if (data == NULL && size == 0) {
		throw new ExceptionAVLTreeAccess();
	}
	else {
		// current data = item
		if (comparator->compare(*data, *item) == 0) {
			dataFound = *data;
		}
		// current item < data
		else if (comparator->compare(*item, *data) == -1) {
			if (left != NULL) {
				dataFound = left->find(item);
			}
			else { // item is not present
				throw new ExceptionAVLTreeAccess();
			}
		}
		// current item > data
		else if (comparator->compare(*item, *data) == 1) {
			if (right != NULL) {
				dataFound = right->find(item);
			}
			else { // item is not present
				throw new ExceptionAVLTreeAccess();
			}
		}
	}
	return dataFound;
}

// returns the current number of items in the tree
template<typename T>
unsigned long AVLTree<T>::getSize() const {
	return size;
}


// add additional private functions here
// right rotation
template<typename T>
void AVLTree<T>::zig()
{
	if (left == NULL) {  // no left, no way to zig
		return;
	}
	// keep track of diff of node and left for changes
	int gdiff = diff;
	int pdiff = left->diff;

	// modify the tree
	AVLTree<T>* olnr = left;  // olnr is "old left, new right"
	left = olnr->left;
	olnr->left = olnr->right;
	olnr->right = right;
	right = olnr;

	// note that the modifications kept the node itself in place, so we need to swap its data with its olnr's
	T* tempData = data;
	data = olnr->data;
	olnr->data = tempData;

	// update the diff fields for node and new right
	if (pdiff < 0) {  // if imbalance was outside left heavy (left-left violation)
		diff = gdiff + 2;
		right->diff = gdiff - pdiff + 1;
	}
	else {  // otherwise imbalance was inside left heavy (left-right violation)
		diff = pdiff + 1;
		right->diff = gdiff + 1;
	}
}

// left rotation
template<typename T>
void AVLTree<T>::zag()
{
	if (right == NULL) {  // no right, no way to zig
		return;
	}
	// keep track of diff of node and right for changes
	int gdiff = diff;
	int pdiff = right->diff;

	// modify the tree
	AVLTree<T>* ornl = right;  // ornl is "old right, new left"
	right = ornl->right;
	ornl->right = ornl->left;
	ornl->left = left;
	left = ornl;

	// note that the modifications kept the node itself in place, so we need to swap its data with its ornl's
	T* tempData = data;
	data = ornl->data;
	ornl->data = tempData;

	// update the diff fields for node and new left
	if (pdiff > 0) {  // if imbalance was outside right heavy (right-right violation)
		diff = gdiff - 2;
		left->diff = gdiff - pdiff - 1;
	}
	else {  // otherwise imbalance was inside right heavy (right-left violation)
		diff = pdiff - 1;
		left->diff = gdiff - 1;
	}
}

// left rotation on left subtree, followed by right rotation
// zigzag - call zag on the child then zig on itself
template<typename T>
void AVLTree<T>::zigzag() {
	// if root data is NULL, emnpty tree
	if (data == NULL) {
		return;
	}
	else {
		left->zag();
		zig();
	}
}

// right rotation on right subtree, followed by left rotation
// zagzig - call zig on the child then zag on itself
template<typename T>
void AVLTree<T>::zagzig() {
	// if root data is NULL, emnpty tree
	if (data == NULL) {
		return;
	}
	else {
		right->zig();
		zag();
	}
}

// check for and rebalance this node, if needed
template<typename T>
void AVLTree<T>::rebalance() {

	if ((diff >= -1) && (diff <= 1)) {
		return;
	}
	else if (diff < -1) {
		if (left->diff <= 0) {
			zig();
		}
		else if (left->diff > 0) {
			zigzag();
		}
	}
	else if (diff > 1) {
		if (right->diff >= 0) {
			zag();
		}
		else if (right->diff < 0) {
			zagzig();
		}
	}
}
#endif // !AVL_TREE