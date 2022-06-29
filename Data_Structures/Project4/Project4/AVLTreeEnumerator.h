// AVLTreeEnumerator.h
// code help : powerpoint slides &
// Data Structures Featuring C++
// A Programmer's Persperctive
// by Dr. Sridhar Radhakrishnan, Dr. Wise, & Dr. Sekharan
// Chapter 6
//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
#ifndef AVL_TREE_ENUMERATOR
#define AVL_TREE_ENUMERATOR

#include <stack>
#include "Enumerator.h"
#include "AVLTreeOrder.h"
#include "AVLTree.h"

template <typename T>
class AVLTreeEnumerator : public Enumerator<T>
{
private:
	AVLTreeOrder order;
	std::stack<const AVLTree<T>*> traversalStack;
	void buildTraversalStack(const AVLTree<T>* current);
public:
	AVLTreeEnumerator(const AVLTree<T>* root, AVLTreeOrder order);
	virtual ~AVLTreeEnumerator();
	bool hasNext() const;
	T next();						// throws ExceptionEnumerationBeyondEnd if no next item is available
	T peek() const;					// throws ExceptionEnumerationBeyondEnd if no next item is available
	AVLTreeOrder getOrder();		// returns the order of this enumerator (preorder, inorder, or postorder)
	unsigned long stackSize();
};

// put implementation here
template <typename T>
AVLTreeEnumerator<T>::AVLTreeEnumerator(const AVLTree<T>* root, AVLTreeOrder order) {
	if (order != AVLTreeOrder::inorder && order != AVLTreeOrder::preorder && order != AVLTreeOrder::postorder) {
		throw new ExceptionAVLTreeAccess();
	}
	else {
		this->order = order;
	}

	if (root->data != NULL && root->getSize() > 0){
		buildTraversalStack(root);
	}
	else {
		throw new ExceptionAVLTreeAccess();
	}
}

template <typename T>
AVLTreeEnumerator<T>::~AVLTreeEnumerator() {
	unsigned long treeSize = stackSize();
	for (unsigned long i = 0; i < treeSize; i++) {
		traversalStack.top() = NULL;
		traversalStack.pop();
	}
}

template <typename T>
bool AVLTreeEnumerator<T>::hasNext() const {
	if (traversalStack.empty()) {
		return false;
	}
	else {
		return true;
	}
}

// throws ExceptionEnumerationBeyondEnd if no next item is available
template <typename T>
T AVLTreeEnumerator<T>::next() {
	T* nextData;

	if (hasNext() == true) {
		nextData = new T;
		// take the data on top of the stack
		nextData = traversalStack.top()->data;
		// remove the data from the top of the stack
		traversalStack.pop();
	}
	else {
		throw new ExceptionEnumerationBeyondEnd();
	}

	return *nextData;
}

// throws ExceptionEnumerationBeyondEnd if no next item is available
template <typename T>
T AVLTreeEnumerator<T>::peek() const {
	T* peekData = NULL;

	if (hasNext() == true) {
		peekData = new T;

		// take the data on top of the stack
		peekData = traversalStack.top()->data;
	}
	else {
		throw new ExceptionEnumerationBeyondEnd();
	}

	return *peekData;
}

// returns the order of this enumerator (preorder, inorder, or postorder)
template <typename T>
AVLTreeOrder AVLTreeEnumerator<T>::getOrder() {
	return order;
}

template <typename T>
void AVLTreeEnumerator<T>::buildTraversalStack(const AVLTree<T>* current) {
	if (current->data == NULL) {
		return;
	}
	else {
		// since it's building the stack, reverse the output order 
		if (order == AVLTreeOrder::preorder) { //preorder
			// output: root, left, right
			if (current->right != NULL) {
				buildTraversalStack(current->right);
			}
			if (current->left != NULL) {
				buildTraversalStack(current->left);
			}
			if (current->data != NULL) {
				traversalStack.push(current);
			}
		}
		else if (order == AVLTreeOrder::inorder) { // inorder
			// output: left, root, right
			if (current->right != NULL) {
				buildTraversalStack(current->right);
			}
			if (current->data != NULL) {
				traversalStack.push(current);
			}
			if (current->left != NULL) {
				buildTraversalStack(current->left);
			}
		}
		else if (order == AVLTreeOrder::postorder) { // postorder
			// output: left, right, root
			if (current->data != NULL) {
				traversalStack.push(current);
			}
			if (current->right != NULL) {
				buildTraversalStack(current->right);
			}
			if (current->left != NULL) {
				buildTraversalStack(current->left);
			}
		}
	}
}

template <typename T>
unsigned long AVLTreeEnumerator<T>::stackSize() {
	return traversalStack.size();
}
#endif // !AVL_TREE_ENUMERATOR