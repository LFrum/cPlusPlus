/*
Lince Rumainum
Advanced C++
occc spring 2017
BagHW
Textbook Big C++
http://stackoverflow.com/questions/28357850/reading-data-in-from-file-and-inserting-into-linked-list-c
http://www.geeksforgeeks.org/write-a-function-that-counts-the-number-of-times-a-given-int-occurs-in-a-linked-list/
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <list>
#include <algorithm>
using namespace std;

//ALWAYS start on the head! Going downhill
struct BagNode {
	BagNode * next;
	string dataValue;
	int dataCount;
} myBagNode;

class BagList {
private: //private block 
	BagNode * head;
public:
	BagList() {
		//must fully defined all parameters in the constructor
		head = NULL;
	}

	void insert(string n) {
		if (head == NULL) { // empty list
			head = new BagNode;
			head->dataValue = n;
			head->next = NULL;
		}
		else { // create a new LinkedListNode
			BagNode * x = new BagNode;
			x->dataValue = n;
			// new head?
			if (n < head->dataValue) { // new head
				x->next = head;
				head = x;
			}
			else { // general insert
				BagNode * c = head;
				while (c->next != NULL && c->next->dataValue < n) {
					c = c->next;
				}
				x->next = c->next;
				c->next = x;
			}
		}
	}

	void transverse(string outputFileName) {
		BagNode * p;
		p = head;
		int counter = 1;
		ofstream outputFile;

		if (outputFileName == "") { //write to output file and display on console
			cout << "Please enter the file name for your output: ";
			getline(cin, outputFileName);
			
			outputFile.open(outputFileName);

			if (!outputFile) {
				cout << "The file is not found" << endl;
				exit(1);
			}

			while (p) {
				string currentString = p->dataValue;

				while (p->next != NULL && p->next->dataValue == p->dataValue) {
					counter++;
					p = p->next;
				}

				p->dataCount = counter;

				if (p->dataCount > 1) {
					cout << p->dataValue << " (" << p->dataCount << ")" << endl;
					outputFile << p->dataValue << " (" << p->dataCount << ")" << endl;
				}
				else {
					cout << p->dataValue << endl;
					outputFile << p->dataValue << endl;
				}

				p = p->next;
			}
		}
		else { //write to output file only
			outputFile.open(outputFileName);

			if (!outputFile) {
				cout << "The file is not found" << endl;
				exit(1);
			}

			while (p) {
				string currentString = p->dataValue;

				while (p->next != NULL && p->next->dataValue == p->dataValue) {
					counter++;
					p = p->next;
				}

				p->dataCount = counter;

				if (p->dataCount > 1) {					
					outputFile << p->dataValue << " (" << p->dataCount << ")" << endl;
				}
				else {
					outputFile << p->dataValue << endl;
				}
				p = p->next;
			}
		}

		cout << endl;
		outputFile.close();
	}

	string ToUpper(string str) {
		string output = str;
		int strLen = str.size();

		for (int i = 0; i < strLen; ++i) {
			output[i] = toupper(output[i]);
		}
		
		return output;
	}

	string isAlphaOnly(string initialDataValue) {
		string output = initialDataValue;
		for (int i = 0, ouputLength = output.size(); i < ouputLength; i++)
		{
			if (ispunct(output[i]))
			{
				output.erase(i, 1);
				--i;
				ouputLength = output.size();
			}
		}
		return output;
	}

};

int main(int argc, char argv[]) {

	cout << "Welcome to the Bag Node Application!" << endl << endl;

	BagList theList;
	string vInitial, v, vFinal;

	string inputFileName;
	string outputFileName;

	if (3 == argc) {
		inputFileName = argv[1];
		outputFileName = argv[2];
	}
	else if (2 == argc) {
		inputFileName = argv[1];
	}
	else {
		//StorySample.txt can be used for test purposes
		cout << "Please enter the file name: ";
		getline(cin, inputFileName);
	}

	ifstream inputFile;
	inputFile.open(inputFileName);

	if (!inputFile) {
		cout << "The file is not found" << endl;
		exit(1);
	}

	struct BagNode* head = NULL;

	
	while (inputFile >> vInitial) {
		v = theList.isAlphaOnly(vInitial);
		vFinal = theList.ToUpper(v);

		theList.insert(vFinal);
	}

	inputFile.close();

	theList.transverse(outputFileName);

	cout << "Bag Node Application completed!" << endl;
	cout << "Your output is saved in your output file!" << endl;

	return 0;
}

