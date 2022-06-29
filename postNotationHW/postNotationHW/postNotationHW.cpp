/*
Lince Rumainum 
C++
HW #2
Postfix notation
-------------------------------------------
Reference:
http://www.cplusplus.com/forum/general/13135/ Converting string to integer
*/

#include<iostream>
#include<string>
#include <vector>
#include <sstream>

using namespace std;

//Function to convert input string ASCII code into an actual integer
int numInput(char s_input);

int main() {
	string s_input;
	int sLength;
	vector <int> myVector;
	int myVector_last;

	do {	
		// Get input
		cout << "Enter 0 to exit " << endl;
		cout << "Otherwise, enter postfix string input : ";
		getline(cin, s_input);

		sLength = s_input.length(); //string input length

		//Exit program
		if (s_input[0] == '0') {
			return 0;
		}
		//Input for the postfix needs to be either a number or unary: + or - 
		else if (isdigit(s_input[0]) || s_input[0] == '+' || s_input[0] == '-') {
			for (int i = 0; i < sLength; i++) {
				if (isdigit(s_input[i])) {
					int digit;
					string s;
					int j = i + 1;
					s = to_string(numInput(s_input[i]));

					do {
						digit = numInput(s_input[i]);

						int digitX;
						if (isdigit(s_input[j])) {
							digitX = numInput(s_input[j]);
							s += to_string(digitX);
							j++;
							i++;
						}

					} while (isdigit(s_input[j]));

					// Convert the string into integer
					if (s.length() > 1) {
						istringstream(s) >> digit;
					}

					// Add the digit to myVector
					myVector.push_back(digit);
				}
				else if (s_input[i] == '+') {
					int k = i + 1;

					// Adding together the vectors
					if (isspace(s_input[k]) || i == sLength - 1) {
						myVector_last = myVector[myVector.size() - 2] + myVector[myVector.size() - 1];
						myVector[myVector.size() - 2] = myVector_last;
						myVector.pop_back();
					}
					// Adding the digits from the unary + input
					else if (isdigit(s_input[k])) {
						i++;
						int digitPlus;
						string sPlus;
						int l = k + 1;
						sPlus = to_string(numInput(s_input[k]));

						do {
							int digitX;
							digitPlus = numInput(s_input[k]);

							if (isdigit(s_input[l])) {
								digitX = numInput(s_input[l]);
								sPlus += to_string(digitX);
								l++;
								i++;
							}
						} while (isdigit(s_input[l]));

						// Convert the string into integer
						if (sPlus.length() > 1) {
							istringstream(sPlus) >> digitPlus;
						}

						// Add the digit to myVector
						myVector.push_back(digitPlus);
					}
				}
				// Adding the digits from the unary - input
				else if (s_input[i] == '-') {
					int k = i + 1;
					// subtract the last two vectors
					if (isspace(s_input[k]) || i == sLength - 1) {
						myVector_last = myVector[myVector.size() - 2] - myVector[myVector.size() - 1];
						myVector[myVector.size() - 2] = myVector_last;
						myVector.pop_back();
					}
					else if (isdigit(s_input[k])) {
						int digitMinus;
						string sMinus;
						int l = k + 1;
						sMinus = to_string(numInput(s_input[k]));
						i++;

						do {
							int digitX;

							digitMinus = numInput(s_input[k]);

							if (isdigit(s_input[l])) {

								digitX = numInput(s_input[l]);
								sMinus += to_string(digitX);
								l++;
								i++;
							}
						} while (isdigit(s_input[l]));

						// Convert the string into integer
						if (sMinus.length() > 1) {
							istringstream(sMinus) >> digitMinus;
						}

						digitMinus *= -1;

						// Add the digit to myVector
						myVector.push_back(digitMinus);
					}
				}
				else if (s_input[i] == '*') {
					myVector_last = myVector[myVector.size() - 2] * myVector[myVector.size() - 1];
					myVector[myVector.size() - 2] = myVector_last;
					myVector.pop_back();
				}
				else if (s_input[i] == '/') {
					myVector_last = myVector[myVector.size() - 2] / myVector[myVector.size() - 1];
					myVector[myVector.size() - 2] = myVector_last;
					myVector.pop_back();
				}
				else if (s_input[i] == '%') {
					myVector_last = myVector[myVector.size() - 2] % myVector[myVector.size() - 1];
					myVector[myVector.size() - 2] = myVector_last;
					myVector.pop_back();
				}
				else if (s_input[i] == '^') {
					myVector_last = myVector[myVector.size() - 2] ^ myVector[myVector.size() - 1];
					myVector[myVector.size() - 2] = myVector_last;
					myVector.pop_back();
				}
				else if (isspace(s_input[i])) {
					// go to next i, non error input
				}
				else {
					cout << "Invalid Input! Numbers and + - / * % input only!" << endl;
				}
			}
			cout << "Answer: " << myVector_last << endl << endl;
		}
		else {
			cout << "Invalid Input! Numbers and + - / * % input only!" << endl;
		}		
	} while (s_input != "0");
	
	return 0;
}

int numInput(char s_input)
{
	int num;

	if (s_input == 48) {
		num = 0;
	}
	else if (s_input == 49) {
		num = 1;
	}
	else if (s_input == 50) {
		num = 2;
	}
	else if (s_input == 51) {
		num = 3;
	}
	else if (s_input == 52) {
		num = 4;
	}
	else if (s_input == 53) {
		num = 5;
	}
	else if (s_input == 54) {
		num = 6;
	}
	else if (s_input == 55) {
		num = 7;
	}
	else if (s_input == 56) {
		num = 8;
	}
	else if (s_input == 57) {
		num = 9;
	}

	return num;
}