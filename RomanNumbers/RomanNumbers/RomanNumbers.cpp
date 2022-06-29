/*
Lince Rumainum
Homework I
Roman Numbers
C++
------------------------
References:
Exercise 3.6 Textbook pg 151
Exercise 4.12 Textbook pg 223
Exercise 4.13 Textbook pg 223
http://www.cplusplus.com/forum/general/13135/ Converting string to integer
http://www.cplusplus.com/forum/beginner/50617/ Coverting number to roman numeral
http://stackoverflow.com/questions/23418390/how-to-convert-a-c-string-to-uppercase
*/

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <algorithm>

using namespace std;

bool convertRomanToDecimal(string s, int & d);
bool convertDecimalToRoman(int d, string & s);
int romanNumeral(string s, string one, string five, string ten, string fifty, string oneHundred, string fiveHundred, string oneThousand);

int main()
{
	int conversionChoice; // Number from list of options
	string s; // String of the roman numbers
	int d; // Decimal of the roman numbers
	bool validInput = 1; // Input validation

	// Greeting message
	cout << "Welcome to Roman Numbers Conversion!" << endl;
	
	do {
		// List of options
		cout << "Here are your options:\n"
			<< "1. Roman to Decimal,\n"
			<< "2. Decimal to Roman, or\n"
			<< "3. Exit\n"
			<< "Pick one of the numbers above: ";
		cin >> conversionChoice;

		if (conversionChoice != 1 && conversionChoice != 2 && conversionChoice != 3) {
			cout << "Invalid choice! Please enter the number 1 or 2 or 3 only next time!" << endl;
			validInput = 0;
		}
		// 1. Roman to Decimal
		else if (conversionChoice == 1) {
			s = "";
			d = -1;

			validInput = convertRomanToDecimal(s, d);
			
			if (d == 0) {
				cout << "Invalid input!\n";
			}
			else if (d > 0) {
				cout << "The decimal number: " << d << endl << endl;
			}
			else {
				cout << "Invalid input!\n";
				validInput = false;
			}
		}
		// 2. Decimal to Roman
		else if (conversionChoice == 2) {
			d = -1;

			cin.ignore();

			cout << "Enter the decimals number: ";
			getline(cin, s);

			if (s.length() > 4) {	//INVALID INPUT - LIMIT TO 9,999
				validInput = 0;
			}

			for (int i = 0; i < s.length(); i++) {
				if (!isdigit(s[i])) {	//INVALID INPUT - NUMERICAL INPUT ONLY
					validInput = 0;
				}
			}

			validInput = convertDecimalToRoman(d, s);

		}
		// 3. Exit
		else {
			validInput = 0;
		}
	} while (validInput == true);

	return 0;
}

bool convertRomanToDecimal(string s, int & d)
{
	cin.ignore();

	cout << "Enter the Roman numeral: ";
	getline(cin, s);
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	
	if (s.length() > 15) {		// INVALID INPUT - LIMIT TO 9,999 which is MMMMMMMMMCMXCIX
		return false;
	}

	for (int i = 0; i < s.length(); i++) {
		if (!isalpha(s[i])) {	// INVALID INPUT - ALPHABETICAL INPUT ONLY
			return false;
		}
	}

	d = romanNumeral(s, "I", "V", "X", "L", "C", "D", "M");

	return true;
}

bool convertDecimalToRoman(int d, string & s)
{
	//This line of code below convert the string into integer
	istringstream(s) >> d;

	//integers of roman numeral
	int M, D, C, L, X, V, I, n;

	cout << "The Roman Numeral: ";
	if (d >= 1000)
	{
		M = d / 1000;
		n = 0;
		{
			for (n; n < M; n++) {
				cout << "M";
			}				
		}

		d = d % 1000;
	}

	if (d >= 900)
	{
		cout << "CM";
		d = d % 900;
	}
	else if (d >= 500)
	{
		{
			D = d / 500;
			n = 0;
			for (n; n < D; n++) {
				cout << "D";
			}
		}
		d = d % 500;
	}

	if (d >= 400)
	{
		cout << "CD";
		d = d % 400;
	}
	else if (d >= 100)
	{
		{
			C = d / 100;
			n = 0;
			for (n; n < C; n++) {
				cout << "C";
			}				
		}
		d = d % 100;
	}

	if (d >= 90)
	{
		cout << "XC";
		d = d % 90;
	}

	else if (d >= 50)
	{
		{
			L = d / 50;
			n = 0;
			for (n; n < L; n++) {
				cout << "L";
			}				
		}
		d = d % 50;
	}
	if (d >= 40)
	{
		cout << "XL";
		d = d % 40;
	}

	else if (d >= 10)
	{
		{
			X = d / 10;
			n = 0;
			for (n; n < X; n++) {
				cout << "X";
			}				
		}
		d = d % 10;
	}

	if (d >= 9)
	{
		cout << "IX";
		d = d % 9;
	}

	else if (d >= 5)
	{
		{
			V = d / 5;
			n = 0;
			for (n; n < V; n++) {
				cout << "V";
			}
		}
		d = d % 5;
	}
	if (d >= 4)
	{
		cout << "IV";
		d = d % 4;
	}
	else if (d >= 1)
	{
		I = d;
		n = 0;
		for (n; n < I; n++) {
			cout << "I";
		}
	}
	
	cout << endl << endl; 

	return true;
}

// This function yields the constant values of each roman numeral constant
int romanNumeral (string s, string one, string five, string ten, string fifty, string oneHundred, string fiveHundred, string oneThousand)
{
	int d = 0;

	int count_I = 0;
	int count_V = 0;
	int count_X = 0;
	int count_L = 0;
	int count_C = 0;
	int count_D = 0;
	int count_M = 0;

	for (int i = 0; i < s.length(); i++) {
		//FOR ROMAN NUMERAL: M
		if (s[i] == oneThousand[0]) {
			d += 1000;
			count_M++;
		}
		//FOR ROMAN NUMERAL: D
		else if (s[i] == fiveHundred[0]) {
			if ( s[i + 1] == fiveHundred[0] || s[i + 1] == oneThousand[0] ) {	// INVALID INPUT
				return 0;
			}
			else {
				d += 500;
				count_D++;
			}
		}
		//FOR ROMAN NUMERAL: C
		else if (s[i] == oneHundred[0]) {
			if (s[i + 1] == oneThousand[0]) {
				d += 900;
				i++;
				count_M++;
				count_C++;
			}
			else if (s[i + 1] == fiveHundred[0]) {
				d += 400;
				i++;
				count_D++;
				count_C++;
			}
			else {
				d += 100;
				count_C++;
			}
		}
		//FOR ROMAN NUMERAL: L
		else if (s[i] == fifty[0]) {
			if (s[i + 1] == fifty[0] || s[i + 1] == oneHundred[0] || s[i + 1] == fiveHundred[0] || s[i + 1] == oneThousand[0]) {	// INVALID INPUT
				return 0;
			}
			else {
				d += 50;
				count_L++;
			}
		}
		//FOR ROMAN NUMERAL: X
		else if (s[i] == ten[0]) {
			if (s[i + 1] == oneHundred[0]) {
				d += 90;
				i++;
				count_X++;
			}
			else if (s[i + 1] == fifty[0]) {
				d += 40;
				i++;
				count_X++;
			}
			else if (s[i + 1] == fiveHundred[0] || s[i + 1] == oneThousand[0]) {	// INVALID INPUT
				return 0;
			}
			else {
				d += 10;
				count_X++;
			}
		}
		//FOR ROMAN NUMERAL: V
		else if (s[i] == five[0]) {
			if (s[i + 1] == five[0] || s[i + 1] == ten[0] || s[i + 1] == fifty[0] || s[i + 1] == oneHundred[0] || s[i + 1] == fiveHundred[0] || s[i + 1] == oneThousand[0]) {	// INVALID INPUT
				return 0;
			}
			else {
				d += 5;
				count_V++;
			}
		}
		//FOR ROMAN NUMERAL: I			
		else if (s[i] == one[0]) {	
			if (s[i + 1] == five[0]) {
				d += 4;
				i++;
				count_I++;
			}
			else if (s[i + 1] == ten[0]) {
				d += 9;
				i++;
				count_I++;
			}
			else if (s[i + 1] == fifty[0] || s[i + 1] == oneHundred[0] || s[i + 1] == fiveHundred[0] || s[i + 1] == oneThousand[0]) {	// INVALID INPUT
				return 0;
			}
			else {
				d += 1;
				count_I++;
			}
		}
		else {	// OTHER INVALID INPUT
			return 0;
		}

		// INVALID INPUT
		if ( count_I > 3 || count_V > 1 || count_X > 3 || count_L > 1 || count_C > 3 || count_D > 1 || count_M > 10 ) {
			return 0;
		}
	}
	return d;
}