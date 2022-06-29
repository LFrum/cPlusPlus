//ExpenseApplication.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "Date.h"
#include "Expenses.h"
#include "Groceries.h"
#include "Entertainment.h"
#include "OtherExpenses.h"
using namespace std;

string displayMainMenuOption();
Date expensesDate();

int main(int argc, char argv[]) {

	cout << "Welcome to the Expenses Application!" << endl << endl;

	string fileName;

	//Continue writing from an existing file
	if (2 == argc) {
		fileName = argv[1];
	}
	else { //Ask for user's input
		fileName = displayMainMenuOption();
	}

	ofstream outputFile;
	outputFile.open(fileName);

	if (!outputFile) {
		cout << "The file is not found" << endl;
		exit(1);
	}

	int option; 

	do {
		string itemDescription;
		int itemQuantity;
		double itemPrice;
		double taxPrice;

		cout << "What expenses would you like to record?" << endl;
		cout << "1. Groceries" << endl;
		cout << "2. Entertainment" << endl;
		cout << "3. Other Expenses" << endl;
		cout << "Enter 0 to exit" << endl;
		cin >> option;
		cin.ignore();

		if (option != 1 && option != 2 && option != 3 && option !=0) {
			cout << "Invalid input! Pick 1, 2, or 3! Or enter 0 to exit!" << endl << endl;
		}
		else if (option == 0) {
			break;
		}
		else {
			Date dateOfExpense = expensesDate();
			outputFile << dateOfExpense.toString();
			outputFile << endl;
			cin.ignore();

			cout << "Enter the item description: ";
			getline(cin, itemDescription);
			cout << "Enter the item quantity: ";
			cin >> itemQuantity;
			cout << "Enter the price of the item: ";
			cin >> itemPrice;
			cout << "Enter the tax of this expense: ";
			cin >> taxPrice;

			if (option == 1) {				
				Groceries g = Groceries (fileName, itemDescription, itemQuantity, itemPrice, taxPrice);
				outputFile << g.toString();
			}
			else if (option == 2) {				
				Entertainment e = Entertainment(fileName, itemDescription, itemQuantity, itemPrice, taxPrice);
				outputFile << e.toString();
			}
			else {				
				OtherExpenses o = OtherExpenses(fileName, itemDescription, itemQuantity, itemPrice, taxPrice);
				outputFile << o.toString();
			}
		}	

	} while (option != 0);

	outputFile.close();

	cout << "Your expenses are recorded in the file you had provided!" << endl;

	return 0;
}

string displayMainMenuOption() {
	char menuChoice;
	//string inputFileName, outputFileName;
	string fileName;

	do {
		cout << "Do you want to continue writing from existing expense file? [Y/N] ";
		cin >> menuChoice;
		cin.ignore();

		if (menuChoice == 'Y' || menuChoice == 'y') {
			cout << "Please enter the input file name: ";
			getline(cin, fileName);
			
		}
		else if (menuChoice == 'N' || menuChoice == 'n') {
			cout << "Please enter the file name to save the expense: ";
			getline(cin, fileName);
			
		}
		else {
			cout << "Invalid input! Enter either Y or N!" << endl;
		}
	} while (menuChoice != 'Y' && menuChoice != 'y' && menuChoice != 'N' && menuChoice != 'n');
	return fileName;
}

Date expensesDate() {
	int dateOption;
	Date d = Date();

	int year = d.getDay();
	int month = d.getMonth();
	int day = d.getDay();

	do {
		cout << "What is the date for this expenses?" << endl;
		cout << "1. Current date" << endl;
		cout << "2. Enter new date" << endl;
		cout << "3. Use previous date (for first entry, date will be set to current date)" << endl;
		cin >> dateOption;
		cout << endl;

		if (dateOption == 1) {
			d = Date();
		}
		else if (dateOption == 2) {
			cout << "Please enter the year (ex.:2017): ";
			cin >> year;

			cout << "Please enter the month (ex.:1): ";
			cin >> month;

			cout << "Please enter the day (ex.:1): ";
			cin >> day;

			d = Date(day, month, year);
		}
		else if (dateOption == 3) {
			d = Date(day, month, year);
		}
		else {
			cout << "Invalid input!" << endl;
		}
	} while (dateOption != 1 && dateOption != 2 && dateOption != 3 );

	return d;
}