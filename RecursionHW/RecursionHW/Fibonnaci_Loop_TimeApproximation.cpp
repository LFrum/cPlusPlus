/*
C++
Monday 5:30 P.M.
Dr. Goulden
------------------------------------------------
Recursion HW
Loop and Recursive Fibonacci Function:
unsigned __int64 fibonacci_loop(int);
Finding the largest value of n for the fibonacci (n)
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

	//Because we start on n = 39, the actual n is added to 39

	n = 52 - 39; //For 1 hour
	cout << "Fib(" << 52 << ") = " << fib_loop(n) << endl;
	n = 59 - 39; //For 1 day
	cout << "Fib(" << 59 << ") = " << fib_loop(n) << endl;
	n = 63 - 39; //For 1 week
	cout << "Fib(" << 63 << ") = " << fib_loop(n) << endl;
	n = 71 - 39; //For 1 year
	cout << "Fib(" << 71 << ") = " << fib_loop(n) << endl;
	n = 81 - 39; //For 1 century
	cout << "Fib(" << 81 << ") = " << fib_loop(n) << endl;
	n = 85 - 39; //For 1 millenium
	cout << "Fib(" << 85 << ") = " << fib_loop(n) << endl;
	n = 90 - 39; //For 10,000 years
	cout << "Fib(" << 90 << ") = " << fib_loop(n) << endl;
	n = 100 - 39; //For 1,000,000 years
	cout << "Fib(" << 100 << ") = " << fib_loop(n) << endl;
	n = 117 - 39; //For 5 billion years
	cout << "Fib(" << 117 << ") = " << fib_loop(n) << endl;
	n = 120 - 39; //For 15 billion years
	cout << "Fib(" << 120 << ") = " << fib_loop(n) << endl;

	return 0;
}

unsigned __int64 fib_loop(int n) {
	unsigned __int64 result = 1;
	unsigned __int64 a = 9; //From data acquired n = 39
	unsigned __int64 b = 13; //From data acquired n = 40

	for (int i = 3; i <= n; i++) {
		result = a + b;
		a = b;
		b = result;
	}

	return result;
}