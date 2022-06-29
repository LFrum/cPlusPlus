/*
CS2363
C++
Dr. Goulden
HW Advanced Sorts
------------------------------------
Quick Sort with Set Median of Three
------------------------------------
Lince Rumainum
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int exchangeCount = 0;
int comparisonCount = 0;

void quickSort(int * a, int s);
// sort from index i to index j inclusive:
void quickSort(int * a, int i, int j);

void setMedianOfThree(int * a, int i, int j);
int partition(int * a, int i, int j);

void displayArray(int * a, int s);
void swapElement(int * a, int i, int j);
bool compareElement(int * a, int i, int j);
void copyArray(int * source, int * dest, int s);
void reverseArray(int * a, int s);

int main(int argc, char argv[]) {

	cout << "Welcome to the Quick Sort Application!" << endl << endl;

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

	//Display the array and do the exchange sort
	cout << "The RANDOM array:" << endl;
	displayArray(a, s);
	quickSort(a, s);

	cout << endl;
	cout << "Sorted array:" << endl;
	//display the array
	displayArray(a, s);

	//Sorting the already sorted array
	quickSort(a, s);
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
	quickSort(a, s);
	cout << endl;
	cout << "The sorted array of reversed array:" << endl;
	//display the array
	displayArray(a, s);

	return 0;
}

void quickSort(int * a, int s) {
	quickSort(a, 0, s - 1);
}

void quickSort(int * a, int i, int j) {
	if (i >= j) {
		return;
	}
	setMedianOfThree(a, i, j);
	int pIndex = partition(a, i, j);
	quickSort(a, i, pIndex);
	quickSort(a, pIndex + 1, j);
}

void setMedianOfThree(int * a, int i, int j){
	int midIndex = (i + j) / 2;

	if (compareElement(a,midIndex,i) && compareElement(a, midIndex,j)) {
		swapElement(a, i, midIndex);
	}
	else if (compareElement(a, j, i) && compareElement(a, j, midIndex)) {
		swapElement(a, i, j);
	}
}

int partition(int * a, int i, int j) {
	int pIndex = a[i];
	int k = i - 1;
	int m = j + 1;

	while (k < m) {
		k++;
		while (a[k] < pIndex) {
			++comparisonCount;
			k++;
		}
		m--;
		while (a[m] > pIndex) {
			++comparisonCount;
			m--;
		}
		if (k < m) {
			swapElement(a, k, m);
		}
	}
	return m;
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