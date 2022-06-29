/*
CS2363
C++
Dr. Goulden
HW Advanced Sorts
----------------------------------
Merge Sort
Textbook pg 452 - 453
----------------------------------
Lince Rumainum
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int exchangeCount = 0;
int comparisonCount = 0;

// parameter n is false for binary mergeSort, true for natural
void mergeSort(int * a, int s, bool n);

void mergeSort(int * a, int i, int j);
void mergeSort(int * a, int i, int midIndex, int j);

void displayArray(int * a, int s);
void swapElement(int * a, int i, int j);
bool compareElement(int * a, int i, int j);
void copyArray(int * source, int * dest, int s);
void reverseArray(int * a, int s);

int main(int argc, char argv[]) {

	cout << "Welcome to the Merge Sort Application!" << endl << endl;

	string fileName;

	if (2 == argc) {
		fileName = argv[1];
	}
	else {
		//RandomNumbers.txt can be used for 10,000 random numbers data
		cout << "Please enter the file name: ";
		getline(cin, fileName);
	}

	ifstream fin;
	fin.open(fileName);

	if (!fin) {
		cout << "The file is not found" << endl;
		exit(1);
	}

	int s;
	fin >> s;
	int * a = new int[s];

	for (int i = 0; i < s; ++i) {
		fin >> a[i];
	}

	int choice;

	do {
		cout << "Do you want to do: " << endl;
		cout << "1. Natural MergeSort" << endl;
		cout << "2. Binary MergeSort" << endl << endl;
		cin >> choice;

		if (choice != 1 && choice != 2) {
			cout << "Invalid input! Enter 1 or 2 only!" << endl;
		} 
	} while (choice != 1 && choice != 2);

	//false for binary mergeSort, true for natural
	bool n; 

	if (choice == 1) {
		n = true;
		cout << "You choose natural mergesort" << endl << endl;
	}
	else {
		n = false;
		cout << "You choose binary mergesort" << endl << endl;
	}

	//Display the array and do the exchange sort
	cout << "The RANDOM array:" << endl;
	displayArray(a, s);
	mergeSort(a, s, n);

	cout << endl;
	cout << "Sorted array:" << endl;
	//display the array
	displayArray(a, s);

	//Sorting the already sorted array
	mergeSort(a, s, n);
	cout << endl;
	cout << "The sorted array of already SORTED array:" << endl;
	//display the array
	displayArray(a, s);

	//Reverse the array
	cout << "The REVERSED array:" << endl;
	reverseArray(a, s);
	//display the array the reverse array
	displayArray(a, s);

	//Sorting the reverse array
	mergeSort(a, s, n);
	cout << endl;
	cout << "The sorted array of reversed array:" << endl;
	//display the array
	displayArray(a, s);

	return 0;
}

// parameter n is false for binary mergeSort, 
// parameter n is true for natural mergeSort
void mergeSort(int * a, int s, bool n) {
	if (n == false) {
		mergeSort(a, 0, s - 1);
	}
	else {
		return;
	}
}

void mergeSort(int * a, int i, int j) {
	if (i == j) {
		return;
	}

	int midIndex = (i + j) / 2;

	mergeSort(a, i, midIndex);
	mergeSort(a, midIndex + 1, j);
	
	mergeSort(a, i, midIndex, j);
}

void mergeSort(int * a, int i, int midIndex, int j) {
	int s = j - i + 1;

	int * b = new int [s];

	int i1 = i;
	int i2 = midIndex + 1;
	int k = 0; 

	while (i1 <= midIndex && i2 <= j) {
		if (a[i1] < a[i2]) {
			b[k] = a[i1];
			i1++;
		}
		else {
			b[k] = a[i2];
			i2++;
		}
		k++;
	}

	// Note that only one of the two while loops below is executed

	//Copy any remaining enteries of the first half
	while (i1 <= midIndex) {
		b[k] = a[i1];
		i1++;
		k++;
	}

	while (i2 <= j) {
		b[k] = a[i2];
		i2++;
		k++;
	}

	//Copy back from the temporary vector
	for (k = 0; k < s; k++) {
		a[i + k] = b[k];
	}
}

bool compareElement(int * a, int i, int j) {
	++comparisonCount;
	return a[i] <= a[j];
}

// exchange elements i and j in array a
// and increment a global “exchangeCount” variable
void swapElement(int * a, int i, int j) {
	++exchangeCount;
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}

void displayArray(int * a, int s) {
	if (s <= 200) {
		for (int i = 0; i < s; ++i) {
			if (i % 10 == 0) {
				cout << endl;
			}
			cout << setw(7) << a[i];
		}
	}
	else {
		for (int i = 0; i < 100; ++i) {
			if (i % 10 == 0) {
				cout << endl;
			}
			cout << setw(7) << a[i];
		}
		cout << endl;
		cout << endl;
		for (int i = s - 100; i < s; ++i) {
			if (i % 10 == 0) {
				cout << endl;
			}
			cout << setw(7) << a[i];
		}
	}
	cout << endl;
}

// copy the first s elements from source into dest
void copyArray(int * source, int * dest, int s) {
	for (int j = 0; j < s; ++j) {
		dest[j] = source[j];
	}
}

// reverse the s elements in array a
void reverseArray(int * a, int s) {
	for (int k = 0; k < s / 2; k++) {
		swapElement(a, k, s - k - 1);
	}

}