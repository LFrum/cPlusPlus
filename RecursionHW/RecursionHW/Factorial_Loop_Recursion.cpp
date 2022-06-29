/*
C++
Monday 5:30 P.M.
Dr. Goulden
------------------------------------------------------------
Recursion HW
Loop and Recursive Fibonacci Function:
unsigned __int64 fac_loop(int n);
unsigned __int64 fac_rec(int n);
------------------------------------------------------------
Lince Rumainum
*/

#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

// Factorial loop -- base case
unsigned __int64 fac_loop(int n);

// Factorial loop -- recursive case
unsigned __int64 fac_rec(int n);

int main(int argc, char * argv[]) {

	int n;

	if (argc == 2) {
		n = atoi(argv[1]);
	}
	else {
		cout << "Please enter an integer: ";
		cin >> n;
	}

	clock_t start, finish;

	//Start time
	start = clock();

	// for factorial loop
	cout << n << "! = " << fac_loop(n) << endl;

	finish = clock();
	cout << "Elapased time approximately "
		<< ((finish - start) / CLOCKS_PER_SEC) << " seconds." << endl;

	//Start time
	start = clock();

	// for factorial recursive
	cout << n << "! = " << fac_rec(n) << endl;

	finish = clock();
	cout << "Elapased time approximately "
		<< ((finish - start) / CLOCKS_PER_SEC) << " seconds." << endl;

	return 0;
}

// base case algorithm
unsigned __int64 fac_loop(int n) {
	unsigned __int64 result = 1;

	if (n > 0) {
		for (int i = 1; i <= n; i++) {
			result *= i;
		}
	}
	return result;
}

// Recursive algorithm
unsigned __int64 fac_rec(int n) {
	unsigned __int64 result = 1;

	if (n > 0) {
		result = n * fac_rec(n - 1);
	}

	return result;
}
