/*
CS2363
C++
Dr. Goulden
HW Advanced Sorts
----------------------------------------------
Counting Sort
Note: constant variable SIZE needs to be big 
enough to store the numbers
----------------------------------------------
Lince Rumainum
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int exchangeCount = 0;
int comparisonCount = 0;

void countingSort(int * a, int s);

void displayArray(int * a, int s);
void swapElement(int * a, int i, int j);
bool compareElement(int * a, int i, int j);
void copyArray(int * source, int * dest, int s);
void reverseArray(int * a, int s);

int main(int argc, char argv[]) {

	cout << "Welcome to the Counting Sort Application!" << endl << endl;

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
	countingSort(a, s);

	cout << endl;
	cout << "Sorted array:" << endl;
	//display the array
	displayArray(a, s);

	//Reset the counters
	comparisonCount = 0;
	exchangeCount = 0;

	//Sorting the already sorted array
	countingSort(a, s);
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
	countingSort(a, s);
	cout << endl;
	cout << "The sorted array of reversed array:" << endl;
	//display the array
	displayArray(a, s);

	return 0;
}

void countingSort(int* a, int s)
{
	if (s == 0)
		return;

	// Find the maximum and minimum numbers
	const int SIZE = 10000;
	int maxNum = a[0];
	int minNum = a[0];
	int i, expo = 1;
	int count[SIZE];

	for (int i = 1; i < s; i++) {
		if (a[i] > maxNum) {
			maxNum = a[i];
		}
	}

	// temporary array 
	int * temp = new int[s];

	while (maxNum / expo > 0) {
		//reset count
		for (i = 0; i < 10; i++) {
			count[i] = 0;
		}

		//counting how many time the number is in the array
		for (i = 0; i < s; i++) {
			count[(a[i] / expo) % 10]++;
		}

		//count array for the actual position of the numbers
		for (i = 1; i < s; i++) {
			count[i] += count[i - 1];
		}

		for (i = s - 1; i >= 0; i--) {
			temp[count[(a[i] / expo) % 10] - 1] = a[i];
			count[(a[i] / expo) % 10]--;
		}

		copyArray(temp, a, s);

		expo *= 10;
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