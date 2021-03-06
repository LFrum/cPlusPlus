/*
CS2363
C++
Dr. Goulden
HW Advanced Sorts
----------------------------------------------
radix Sort
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

void radixSort(int * a, int s);

int partition(int * a, int i, int j);

void displayArray(int * a, int s);
void swapElement(int * a, int i, int j);
void copyArray(int * source, int * dest, int s);
void reverseArray(int * a, int s);

int main(int argc, char argv[]) {

	cout << "Welcome to the Radix Sort Application!" << endl << endl;

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
	radixSort(a, s);

	cout << endl;
	cout << "Sorted array:" << endl;
	//display the array
	displayArray(a, s);

	//Sorting the already sorted array
	radixSort(a, s);
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
	radixSort(a, s);
	cout << endl;
	cout << "The sorted array of reversed array:" << endl;
	//display the array
	displayArray(a, s);

	return 0;
}

void radixSort(int * a, int s) {
	const int SIZE = 10;

	if (s == 0)
		return;

	// Find the maximum number 
	int mx = a[0];
	for (int i = 1; i < s; i++) {
		if (a[i] > mx) {
			mx = a[i];
		}
	}

	// sort for every 10th decimal places
	for (int exp = 1; mx / exp > 0; exp *= 10){
		int * output = new int[s]; // output array
		int i;
		//int count[] = { 0 };
		int count[SIZE] = {0};

		// Store count of occurrences in count[]
		for (i = 0; i < s; i++) {
			count[(a[i] / exp) % 10]++;
		}			

		// Change count[i] so that count[i] now contains actual
		// position of this digit in output[]
		for (i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}			

		// Build the output array
		for (i = s - 1; i >= 0; i--) {
			output[count[(a[i] / exp) % 10] - 1] = a[i];
			count[(a[i] / exp) % 10]--;
		}
		
		// Copy the output array to a array
		copyArray(output, a, s);
	}
}

// exchange elements i and j in array a
// and increment a global ?exchangeCount? variable
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