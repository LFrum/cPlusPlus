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

#include<iostream>
#include<cstring>
#include<cctype>

using namespace std;

void pal_string_copy(char * source, char * destination);
bool test_CopySentence(char * destination, int &index);

int main() {
	cout << "Welcome to Palindromes Verification Application!" << endl << endl;

	const int SIZE = 100;
	int testIndex=0;
	bool testSentence;

	char sentence[SIZE];
	char checkingSentence[SIZE];

	cout << "Enter a word or sentence(s) to check if it is a palindrome: " << endl;
	cin.getline(sentence, SIZE);
	cout << endl;

	pal_string_copy(sentence, checkingSentence);

	testSentence = test_CopySentence(checkingSentence, testIndex);

	if (testSentence == true) {
		cout << "The sentence is a palindrome!" << endl;
	}
	else {
		cout << "The sentence is NOT a palindrome!" << endl;
	}

	return 0;
}

void pal_string_copy(char * source, char * destination) {
	int sourceIndex = 0;
	int destinationIndex = 0;

	while (source[sourceIndex] != NULL) {
		while (!isalnum(source[sourceIndex]) && source[sourceIndex] != NULL) {
			sourceIndex++; // skip all non-alphanumeric characters
		}
		if (source[sourceIndex] == NULL) {
			break;
		}
		if ( isalpha( source[sourceIndex] ) ) {
			destination[destinationIndex] = toupper(source[sourceIndex]);			
		}
		if ( isdigit( source[sourceIndex]) ) {
			destination[destinationIndex] = source[sourceIndex];			
		}
		sourceIndex++;
		destinationIndex++;
	}

	//source is NUL so destination is NUL
	destination[destinationIndex] = NULL;
}

bool test_CopySentence(char * destination, int &index) {

	if (destination[index] == destination[strlen(destination) - 1]) {
		destination[strlen(destination) - 1] = NULL;
		
		if (destination[index+1] == NULL || destination[index] == NULL) {
			return true;
		}
		else {
			index++;
			test_CopySentence(destination, index);
		}		
	}
	else {
		return false;
	}
	
}
