/*
Advanced C++
Dr. Goulden
Ciphers HW
Lince Rumainum

Textbook chapter 9 pg 390
http://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
http://www.cplusplus.com/forum/beginner/148159/ Vigenere cipher
http://www.cplusplus.com/forum/articles/13355/ parsing command line
http://stackoverflow.com/questions/8188401/c-warning-c4018-signed-unsigned-mismatch
https://www.programmingalgorithms.com/algorithm/playfair-cipher?lang=C%2B%2B Playfair cipher
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
// stdlib.h
using namespace std;

int displaySelectionMenu();
bool encryptTextOption();

void usage(string program_name);
void openFileError(string filename);

string vigenereCipherText(string str, string keyphrase);
string vigenereOriginalText(string cipher_text, string keyphrase);

string playfairCipherText(string str, string keyphrase);
string playfairOriginalText(string input, string key);

string playfairCipher(string input, string key, bool encipher);
int Mod(int a, int b);
char** Create2DArray(int rowCount, int colCount);
string ToUpper(string str);
//Remove "J"
string RemoveChar(string str, char ch);
vector <int> FindAllOccurrences(string str, char value);
string RemoveAllDuplicates(string str, vector<int> indexes);
//Generate the 5x5 square from the keyphrase
char** GenerateKeySquare(string key);
void GetPosition(char** keySquare, char ch, int* row, int* col);
//Getting the char for different cases:
char* SameRow(char** keySquare, int row, int col1, int col2, int encipher);
char* SameColumn(char** keySquare, int col, int row1, int row2, int encipher);
char* SameRowColumn(char** keySquare, int row, int col, int encipher);
char* DifferentRowColumn(char** keySquare, int row1, int col1, int row2, int col2);
//Removing the chars that are NOT alpha
string RemoveOtherChars(string input);
string AdjustOutput(string input, string output);

int main(int argc, char * argv[]) {
	string keyphrase;
	bool decrypt = false;
	bool vigenereCipher = false; //true for playfair cipher
	int nfile = 0;
	ifstream inputFile;
	ofstream outputFile;
	string inputFileName;
	string outputFileName;
	string vigenereKey, vigenereEncryptedText, vigenereDecryptedText;
	string playfairEncryptedText, playfairDecryptedText;

	cout << "Welcome to Vigenere and Playfair Ciphers" << endl;
	//filePath, /v or /p, /e or /d, inputFile, outFile, keyphrase
	if (6 == argc) {
		for (int i = 1; i < argc; i++) {
			string arg = string(argv[i]);
			if (i == 1 && arg.length() >= 2 && arg[0] == '/') {
				//It is a command line option
				char chiperOption = arg[1];
				if (chiperOption == 'v') {
					vigenereCipher = true;
				}
				else if (chiperOption == 'p') {
					vigenereCipher = false; //playfair chiper
				}
				else if (chiperOption == '?') {
					usage(string(argv[0]));
					break;
				}
			}
			else if (i == 2 && arg.length() >= 2 && arg[0] == '/') {
				char option = arg[1];
				if (option == 'e') {
					decrypt = false; //encrypt phrase
				}
				else if (option == 'd') {
					decrypt = true;
				}
			}
			else {
				nfile++;
				if (nfile == 1) {
					inputFileName = arg.c_str();
					inputFile.open(inputFileName);
					if (inputFile.fail()) {
						openFileError(arg);
					}
				}
				else if (nfile == 2) {
					outputFileName = arg.c_str();
					outputFile.open(outputFileName);
					if (outputFile.fail()) {
						openFileError(arg);
					}
				}
				else {
					keyphrase = arg.c_str();
				}
			}
		}

		if (nfile != 2) {
			usage(string(argv[0]));
		}

		// Read the input file and then store the message from it into the string
		string inputMessage((std::istreambuf_iterator<char>(inputFile)),
			(std::istreambuf_iterator<char>()));

		if (vigenereCipher == true) {
			if (decrypt == false) {
				vigenereEncryptedText = vigenereCipherText(inputMessage, keyphrase);
				outputFile << vigenereEncryptedText;
			}
			else {
				vigenereDecryptedText = vigenereOriginalText(inputMessage, keyphrase);
				outputFile << vigenereDecryptedText;
			}
		}
		else {
			if (decrypt == false) {
				playfairEncryptedText = playfairCipherText(inputMessage, keyphrase);
			}
			else {
				playfairDecryptedText =playfairOriginalText(inputMessage, keyphrase);
			}
		}

		inputFile.close();
		outputFile.close();
	}
	else {
		int menuSelection;

		do {
			menuSelection = displaySelectionMenu();

			if (menuSelection == 0) {
				return 0;
			}			

			bool encryptText = encryptTextOption();			
			
			//cout << "press Enter key" << endl;
			cin.ignore();

			cout << "Enter keyphrase: ";
			getline(cin, keyphrase);

			cout << "Enter input file name: ";
			getline(cin, inputFileName);

			cout << "Enter output file name: ";
			getline(cin, outputFileName);

			// Try to open input file
			inputFile.open(inputFileName);
			if (inputFile.fail()) {
				openFileError(inputFileName);
			}

			outputFile.open(outputFileName);
			if (outputFile.fail()) {
				openFileError(outputFileName);
			}

			// Read the input file and then store the message from it into the string
			string inputMessage((std::istreambuf_iterator<char>(inputFile)),
				(std::istreambuf_iterator<char>()));

			if (menuSelection == 1) {
				if (encryptText) {
					vigenereEncryptedText = vigenereCipherText(inputMessage, keyphrase);
					outputFile << vigenereEncryptedText;
				}
				else {
					vigenereDecryptedText = vigenereOriginalText(inputMessage, keyphrase);
					outputFile << vigenereDecryptedText;
				}
			}
			else if (menuSelection == 2) {
				if (encryptText) {
					playfairEncryptedText = playfairCipherText(inputMessage, keyphrase);
					outputFile << playfairEncryptedText;
				}
				else {
					playfairDecryptedText = playfairOriginalText(inputMessage, keyphrase);					
					outputFile << playfairDecryptedText;
				}
			}
			// close files
			inputFile.close();
			outputFile.close();
		} while (menuSelection != 0);
	}
	
	return 0;
}

int displaySelectionMenu() {
	int selection;
	do {
		cout << "Do you want to use: " << endl;
		cout << "1. Vigenere cypher" << endl;
		cout << "2. Playfair cypher" << endl;
		cout << "Enter 0 to exit program" << endl;
		cin >> selection;
		//cin.get();

		if (selection < 0 || selection > 2) {
			cout << "Invalid Input! Enter either 0 or 1 or 2!" << endl;
		}

	} while (selection < 0 || selection > 2);

	if (selection == 1) {
		return 1;
	}
	else if (selection == 2) {
		return 2;
	}
	else {
		return 0;
	}
}

bool encryptTextOption() {
	int cypherOption;
	
	do {
		cout << "Do you want to do a(n): " << endl;
		cout << "1. Encryption " << endl;
		cout << "2. Decryption" << endl;
		cin >> cypherOption;
		//cin.get();

		if (cypherOption < 1 || cypherOption > 2) {
			cout << "Invalid Input! Enter either 1 or 2!" << endl;
		}
	} while (cypherOption < 1 || cypherOption > 2);
	
	if (cypherOption == 1) {
		return true;
	}
	else {
		return false;
	}
}

/**
	Prints usage instrunctions.
	@param program)name the nae of this program
*/
void usage(string program_name) {
	cout << "Usage: " << program_name << "[/v or /p] [/e or /d] infile outfile keyphrase \n";
		exit(1);
}

/**
	Prints file oplening error message.
	@param filename the name of the file that ould not be opnened
*/
void openFileError(string filename) {
	cout << "Error opening file " << filename << endl;
	exit(1);
}

// This function encrypts the message text using the keyphrase
// and returns the encrypted text
string vigenereCipherText(string str, string keyphrase) {
	
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	transform(keyphrase.begin(), keyphrase.end(), keyphrase.begin(), ::toupper);
	unsigned int j = 0;

	for (unsigned int i = 0; i < str.size(); i++){
		if (isalpha(str[i])) {
			str[i] += keyphrase[j] - 'A';
			if (str[i] > 'Z') str[i] += -'Z' + 'A' - 1;
		}
		j = j + 1 == keyphrase.length() ? 0 : j + 1;
	}

	string key = str;
	return key;
}

// This function decrypts the encrypted text
// and returns the original text
string vigenereOriginalText(string cipher_text, string keyphrase) {
	string orig_text;

	transform(cipher_text.begin(), cipher_text.end(), cipher_text.begin(), ::toupper);
	transform(keyphrase.begin(), keyphrase.end(), keyphrase.begin(), ::toupper);
	unsigned int j = 0;

	for (unsigned int i = 0; i < cipher_text.length(); i++)
	{
		if (isalpha(cipher_text[i])) {
			cipher_text[i] = cipher_text[i] >= keyphrase[j] ?
				cipher_text[i] - keyphrase[j] + 'A' :
				'A' + ('Z' - keyphrase[j] + cipher_text[i] - 'A') + 1;
		}
		j = j + 1 == keyphrase.length() ? 0 : j + 1;
	}

	orig_text = cipher_text;
	return orig_text;
}

// This function encrypts the message text using the keyphrase
// and returns the encrypted text
string playfairCipherText (string input, string key) {
	return playfairCipher(input, key, true);
}

// This function decrypts the encrypted text
// and returns the original text
string playfairOriginalText(string input, string key) {
	return playfairCipher(input, key, false);
}

string playfairCipher(string input, string key, bool encipher){
	string retVal = "";
	char** keySquare = GenerateKeySquare(key);
	string tempInput = RemoveOtherChars(input);

	int e = encipher ? 1 : -1;
	int tempInputLen = tempInput.size();

	if ((tempInputLen % 2) != 0) {
		tempInput += "X";
	}		

	for (int i = 0; i < tempInputLen; i += 2) {
		int row1 = 0;
		int col1 = 0;
		int row2 = 0;
		int col2 = 0;

		GetPosition(keySquare, toupper(tempInput[i]), &row1, &col1);
		GetPosition(keySquare, toupper(tempInput[i + 1]), &row2, &col2);

		if (row1 == row2 && col1 == col2) {
			retVal += string(SameRowColumn(keySquare, row1, col1, e), 2);
		}
		else if (row1 == row2) {
			retVal += string(SameRow(keySquare, row1, col1, col2, e), 2);
		}
		else if (col1 == col2) {
			retVal += string(SameColumn(keySquare, col1, row1, row2, e), 2);
		}
		else {
			retVal += string(DifferentRowColumn(keySquare, row1, col1, row2, col2), 2);
		}
	}

	retVal = AdjustOutput(input, retVal);

	return retVal;
}

int Mod(int a, int b){
	return (a % b + b) % b;
}

char** Create2DArray(int rowCount, int colCount) {
	char** arr = new char*[rowCount];

	for (int i = 0; i < rowCount; ++i)
		arr[i] = new char[colCount];

	return arr;
}

string ToUpper(string str) {
	string output = str;
	int strLen = str.size();

	for (int i = 0; i < strLen; ++i) {
		output[i] = toupper(output[i]);
	}		

	return output;
}

string RemoveChar(string str, char ch) {
	string output = str;
	int outputLen = output.size();

	for (int i = 0; i < outputLen; ++i) {
		if (output[i] == ch){
			output = output.erase(i, 1);
		}
	}
	return output;
}

vector <int> FindAllOccurrences(string str, char value){
	vector<int> indexes;

	int index = 0;
	while ((index = str.find(value, index)) != -1) {
		indexes.push_back(index++);
	}	

	return indexes;
}

string RemoveAllDuplicates(string str, vector<int> indexes) {
	string retVal = str;

	for (int i = indexes.size() - 1; i >= 1; i--){
		retVal = retVal.erase(indexes[i], 1);
	}

	return retVal;
}

char** GenerateKeySquare (string key) {
	char** keySquare = Create2DArray(5, 5);
	string defaultKeySquare = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	string tempKey = key.empty() ? "CIPHER" : ToUpper(key);

	tempKey = RemoveChar(tempKey, 'J');
	tempKey += defaultKeySquare;

	for (int i = 0; i < 25; ++i)	{
		vector<int> indexes = FindAllOccurrences(tempKey, defaultKeySquare[i]);
		tempKey = RemoveAllDuplicates(tempKey, indexes);
	}

	tempKey = tempKey.substr(0, 25);

	for (int i = 0; i < 25; ++i) {
		keySquare[(i / 5)][(i % 5)] = tempKey[i];
	}		

	return keySquare;
}

void GetPosition(char** keySquare, char ch, int* row, int* col){
	if (ch == 'J') {
		GetPosition(keySquare, 'I', row, col);
	}		

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (keySquare[i][j] == ch) {
				*row = i;
				*col = j;
				return;
			}
		}
	}

}

char* SameRow(char** keySquare, int row, int col1, int col2, int encipher) {
	return new char[2]{ keySquare[row][Mod((col1 + encipher), 5)], keySquare[row][Mod((col2 + encipher), 5)] };
}

char* SameColumn(char** keySquare, int col, int row1, int row2, int encipher) {
	return new char[2]{ keySquare[Mod((row1 + encipher), 5)][col], keySquare[Mod((row2 + encipher), 5)][col] };
}

char* SameRowColumn(char** keySquare, int row, int col, int encipher) {
	return new char[2]{ keySquare[Mod((row + encipher), 5)][Mod((col + encipher), 5)], keySquare[Mod((row + encipher), 5)][Mod((col + encipher), 5)] };
}

char* DifferentRowColumn(char** keySquare, int row1, int col1, int row2, int col2) {
	return new char[2]{ keySquare[row1][col2], keySquare[row2][col1] };
}

string RemoveOtherChars(string input) {
	string output = input;
	int strLen = input.size();

	for (int i = 0; i < strLen; i++){
		if (!isalpha(output[i])) {
			//Erase the char if it's not an alphabet char
			output = output.erase(i, 1);
			//decrease the i and strLen so array won't be out of range
			--i;
			strLen--;
		}			
	}
	
	return output;
}

string AdjustOutput(string input, string output) {
	string retVal = output;
	int strLen = input.size();

	for (int i = 0; i < strLen; ++i)	{
		if (!isalpha(input[i])) {
			retVal = retVal.insert(i, 1, input[i]);
		}			

		if (islower(input[i])) {
			retVal[i] = tolower(retVal[i]);
		}			
	}

	return retVal;
}