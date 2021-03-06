//STL includes
#include <iostream>
#include <string>

//Project 1 includes
#include "TemplatedArray.h"

//Project 2 includes
#include "OULinkedList.h"

//Project 3 includes
#include "HashTable.h"
#include "NvraHasher.h"
#include "HashTableEnumerator.h"

//Project 4 includes
#include "AVLTree.h"
#include "AVLTreeEnumerator.h"
#include "AVLTreeOrder.h"

//Other includes
#include "IntComparator.h"
#include "IntHasher.h"

using namespace std;

void memTest() {
	IntComparator* iComp = new IntComparator();
	IntHasher* iHash = new IntHasher;

	for (int i = 0; i < 1000; i++) {
	//for (int i = 0; i < 1; i++) {
		TemplatedArray<int>* memTestStruct = new TemplatedArray<int>();
		for (int j = 0; j < 100; j++) {
			memTestStruct->add(&j);
		}
		for (int j = 99; j >= 0; j--) {
			memTestStruct->removeAt(j);
		}
		delete memTestStruct;
	}

	for (int i = 0; i < 1000; i++) {
	//for (int i = 0; i < 1; i++) {
		OULinkedList<int>* memTestStruct = new OULinkedList<int>(iComp);
		for (int j = 0; j < 50; j++) {
			memTestStruct->append(&j);
		}
		//for (int j = 51; j < 100; j++) {
		for (int j = 50; j < 100; j++) {
			memTestStruct->insert(&j);
		}
		for (int j = 0; j < 100; j++) {
			memTestStruct->replace(&j);
		}
		OULinkedListEnumerator<int>* memTestEnum = new OULinkedListEnumerator<int>(memTestStruct->enumerator());
		while (memTestEnum->hasNext())memTestEnum->next();
		delete memTestEnum;
		for (int j = 99; j >= 0; j--) {
			memTestStruct->remove(&j) ;
		}
		delete memTestStruct;
	}

	for (int i = 0; i < 1000; i++) {
	//for (int i = 0; i < 1; i++) {
		HashTable<int>* memTestStruct = new HashTable<int>(iComp, iHash);
		for (int j = 0; j < 100; j++) {
			//std::cout << "insert: " << memTestStruct->insert(&j) << std::endl;
			memTestStruct->insert(&j);
		}
		for (int j = 0; j < 100; j++) {
			memTestStruct->replace(&j);
		}
		for (int j = 0; j < 100; j++) {
			memTestStruct->find(&j);
		}
		HashTableEnumerator<int>* memTestEnum = new HashTableEnumerator<int>(memTestStruct);
		while (memTestEnum->hasNext())memTestEnum->next();
		delete memTestEnum;
		for (int j = 100; j >= 0; j--) {
			//std::cout << "remove: " << memTestStruct->remove(&j) << std::endl;
			memTestStruct->remove(&j);
		}
		delete memTestStruct;
	}

	for (int i = 0; i < 1000; i++) {
	//for (int i = 0; i < 1; i++) {
		AVLTree<int>* memTestStruct = new AVLTree<int>(iComp);
		for (int j = 0; j < 100; j++) {
			memTestStruct->insert(&j);
		}
		for (int j = 0; j < 100; j++) {
			memTestStruct->replace(&j);
		}
		for (int j = 0; j < 100; j++) {
			memTestStruct->find(&j);
		}
		AVLTreeEnumerator<int>* memTestEnum = new AVLTreeEnumerator<int>(memTestStruct, AVLTreeOrder::inorder);
		while (memTestEnum->hasNext())memTestEnum->next();
		delete memTestEnum;
		for (int j = 100; j >= 0; j--) {
			memTestStruct->remove(&j);
		}
		delete memTestStruct;
	}

	delete iComp;
	delete iHash;
}

int main() {

	// Mem test
	string tStr;
	do {
		getline(cin, tStr);
		memTest();
		cout << "done" << endl;
	} while (tStr != "q");
	return 0;
}