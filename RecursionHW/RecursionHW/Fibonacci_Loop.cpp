/*
C++
Monday 5:30 P.M.
Dr. Goulden
------------------------------------------------
Recursion HW
Loop and Recursive Fibonacci Function:
unsigned __int64 fibonacci_loop(int);
------------------------------------------------
Lince Rumainum
*/

#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

unsigned __int64 * memo;

// Fibonacci loop
unsigned __int64 fib_loop(int n);

int main(int argc, char * argv[]) {

	int n;
	unsigned __int64 result;

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

	//End time
	finish = clock();

	cout << "Elapased time approximately "
		<< ((finish - start) / CLOCKS_PER_SEC) << " seconds." << endl;

	// for fibonacci loop
	cout << "Fib(" << n << ") = " << fib_loop(n) << endl;
	
	//Finding the maximum fibonacci number possible for the unsigned 64-bits
	do {
		n++;	
	} while ( fib_loop(n) < (pow(2, 63)) );
	
	// Print maximum fibonacci
	cout << endl << "The max fibonacci for 64-bit int (" << n << ") = " << fib_loop(n) << endl;

	return 0;
}

unsigned __int64 fib_loop(int n) {
	unsigned __int64 result = 1;
	unsigned __int64 a = 1;
	unsigned __int64 b = 1;

	for (int i = 3; i <= n; i++) {
		result = a + b;
		a = b;
		b = result;
	}
	
	return result;
}