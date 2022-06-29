/*
CS2363
C++
Dr. Goulden
HW Search and Simple Sorts
----------------------------------
Selection Sort
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

void selectionSort(int * a, int s);

void displayArray(int * a, int s);
void swapElement(int * a, int i, int j);
bool compareElement(int * a, int i, int j);
void copyArray(int * source, int * dest, int s);
void reverseArray(int * a, int s);

int main(int argc, char argv[]) {

	cout << "Welcome to the Selection Sort Application!" << endl << endl;

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
	selectionSort(a, s);

	cout << endl;
	cout << "Sorted array:" << endl;
	//display the array
	displayArray(a, s);

	//Display the metrics
	cout << "The metrics of random array" << endl;
	cout << "Comparisons: " << comparisonCount << endl;
	cout << "Exchanges  : " << exchangeCount << endl;

	//Reset the counters
	comparisonCount = 0;
	exchangeCount = 0;

	//Sorting the already sorted array
	selectionSort(a, s);
	cout << endl;
	cout << "The sorted array of already SORTED array:" << endl;
	//display the array
	displayArray(a, s);

	//Display the metrics 
	cout << "The metrics of sorted array" << endl;
	cout << "Comparisons: " << comparisonCount << endl;
	cout << "Exchanges  : " << exchangeCount << endl << endl;

	//Reverse the array
	cout << "The REVERSED array:" << endl;
	reverseArray(a, s);
	//display the array the reverse array
	displayArray(a, s);

	//Reset the counters
	comparisonCount = 0;
	exchangeCount = 0;

	//Sorting the reverse array
	selectionSort(a, s);
	cout << endl;
	cout << "The sorted array of reversed array:" << endl;
	//display the array
	displayArray(a, s);

	//Display the metrics 
	cout << "The metrics of reversed array" << endl;
	cout << "Comparisons: " << comparisonCount << endl;
	cout << "Exchanges  : " << exchangeCount << endl;

	return 0;
}

void selectionSort(int * a, int s) {
	int minIndex;
	int minInt = a[0];

	for (int i = 0; i < s - 1 ; i++) {
		minIndex = i;
		for (int j = i + 1; j < s; j++) {
			if (!compareElement(a, minIndex, j)) {
				minIndex = j;
				minInt = a[j];
			}
		}
		if (minIndex != i) {
			swapElement(a, i, minIndex);
		}		
	}
}

bool compareElement(int * a, int i, int j) {
	++comparisonCount;
	return a[i] <= a[j];
}

// exchange elements i and j in array a
// and increment a global “swapCount” variable
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