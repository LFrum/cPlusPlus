/*
C++
Monday 5:30 P.M.
Dr. Goulden
------------------------------------------------------------
Recursion HW
Loop and Recursive Fibonacci Function:
unsigned __int64 fibonacci_recursive(int);
------------------------------------------------------------
Lince Rumainum
*/

#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

//unsigned __int64 * memo;

// Fibonacci loop -- recursive case
unsigned __int64 fib_rec(int n);

int main(int argc, char * argv[]) {

	int n;
	unsigned __int64 result;

	if (argc == 2) {
		n = atoi(argv[1]);
	}
	else {
		cout << "Please enter the integer for fibonacci: ";
		cin >> n;
	}

	clock_t start, finish;

	//memo = new unsigned __int64[n + 1];

	//for (int i = 0; i < (n + 1); ++i) {
	//	memo[i] = 0;
	//}

	//Start time
	start = clock();

	//for fibonacci recursive
	cout << "Fib(" << n << ") = " << fib_rec(n) << endl;

	finish = clock();
	cout << "Elapased time approximately "
		<< ((finish - start) / CLOCKS_PER_SEC) << " seconds." << endl;
	n++;

	return 0;
}


unsigned __int64 fib_rec(int n) {

	unsigned __int64 result = 1;

	if (n > 2) {
		//if (memo[n] != 0) {
		//	result = memo[n];
		//}
		//else {
			result = fib_rec(n - 1) + fib_rec(n - 2);
		//	memo[n] = result;
		//}
	}

return result;
}