/*
Text_ComplexNumbers.cpp
Lince Rumainum
advanced c++
occc spring 2017
*/

#include <iostream>
#include "ComplexNumbers.h"
using namespace std;

int main() {

	cout << "Welcome to Complex Numbers Application!" << endl << endl;

	ComplexNumber a;
	cout << "Please enter a complex number (real part and imaginary part): " << endl;
	cin >> a;
	cout << "The complex number entered: " << a << endl;

	ComplexNumber b;
	cout << "Please enter a complex number (real part and imaginary part): " << endl;
	cin >> b;
	cout << "The complex number entered: " << b << endl;

	cout << "C2 is     the same as C4: " << (a == b ? "TRUE" : "FALSE") << endl;
	cout << "C2 is not the same as C4: " << (a != b ? "TRUE" : "FALSE") << endl;

	ComplexNumber c;
	c = a + b;
	cout << "c = a + b : " << c << endl;
	c += a;
	cout << "c += a : " << c << endl;
	c -= b;
	cout << "c -= b : " << c << endl;
	c = a - b;
	cout << "c = a - b : " << c << endl;
	c = a * b;
	cout << "c = a * b : " << c << endl;
	
	ComplexNumber x, y, z;
	x = y = z = c;
	cout << "x = " << endl;
	cout << "y = " << endl;
	cout << "z = " << endl;

	cout << "c cast to double is " << (double) c << endl;

	return 0;
}