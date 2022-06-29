/*
CS2363
C++
Dr. Goulden
HW Search and Simple Sorts
----------------------------------
Insertion Sort
----------------------------------
Lince Rumainum
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

void randomizeArray(int * a, int s);

int main(int argc, char argv[]) {

	string fileName;

	ofstream fin;
	fin.open("RandomNumbers.txt");

	if (!fin) {
		cout << "The file is not found" << endl;
		exit(1);
	}

	const int s = 10000;	

	int * a = new int[s];

	randomizeArray(a, s);

	for (int i = 0; i < s; ++i) {
		fin << a[i] << " ";
	}

	return 0;
}

void randomizeArray(int * a, int s) {
	for (int i = 0; i < s; ++i) {
		a[i] = rand() % 1000;
	}

}