/*
ComplexNumbers.h
Lince Rumainum
advanced c++
occc spring 2017
*/

#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <iostream>
#include <cmath>
using namespace std;

class ComplexNumber {

private:
	double real, imaginary;

public:
	ComplexNumber() {
		real = 0;
		imaginary = 0;
	}

	ComplexNumber(double r, double i) {
		real = r;
		imaginary = i;
	}

	ComplexNumber(double r) {
		real = r;
		imaginary = 0;
	}

	operator double() {
		return real;
	}

	operator int() {
		return (int)real;
	}

	//The const is there to tell the code not to change either a or b
	// think of it as: a == b
	bool operator== (const ComplexNumber & rhs) const {
		return real == rhs.real && imaginary == rhs.imaginary;
	}

	// think of it as: a != b
	bool operator!= (const ComplexNumber & rhs) const {
		return !(*this == rhs);
	}

	ComplexNumber operator += (const ComplexNumber & rhs) {
		real += rhs.real;
		imaginary += rhs.imaginary;
		return *this;
	}

	ComplexNumber operator -= (const ComplexNumber & rhs) {
		real -= rhs.real;
		imaginary -= rhs.imaginary;
		return *this;
	}

	ComplexNumber operator *= (const ComplexNumber & rhs) {
		real = real * rhs.real - imaginary * rhs.imaginary;
		imaginary = real * rhs.imaginary + imaginary * rhs.real;
		return *this;
	}

	// think of it as: a = b + c;
	const ComplexNumber operator+ (const ComplexNumber & rhs) {
		ComplexNumber result = *this; // a copy of b
		result += rhs; // add c
		return result;
	}

	// think of it as: a = b - c;
	const ComplexNumber operator- (const ComplexNumber & rhs) {
		ComplexNumber result = *this; // a copy of b
		result -= rhs; // subtract c
		return result;
	}

	// think of it as: a = b * c;
	const ComplexNumber operator* (const ComplexNumber & rhs) {
		ComplexNumber result = *this; // a copy of b
		result *= rhs; // multiply by c
		return result;
	}

	friend ostream & operator << (ostream & out, const ComplexNumber & c) {
		//out << "(" << c.real << " + i " << c.imaginary << ")";
		out << "( " << c.real << (c.imaginary >= 0 ? " + " : " - ") << abs(c.imaginary) << " i )";
		return out;
	}

	friend istream & operator >> (istream & in, ComplexNumber & c) {
		in >> c.real >> c.imaginary;
		return in;
	}
};

#endif