//Expenses.h

#ifndef EXPENSES_H
#define EXPENSES_H

#include <string>
using namespace std;

class Expenses {

private:

	string filename;
	string itemDescription;
	int itemQuantity;
	double itemPrice;
	Date shopDate;

public:

	Expenses(string filename); // default constractors 
	Expenses(string filename, string itemDescription, int itemQuantity, double itemPrice, Date shopDate);

	string getFilename();
	string getItemDescription();
	int getItemQuantity();
	double getItemPrice();
	Date getDate();

	void setFilename(string filename);
	void setItemDescription(string itemDescription);
	void setItemQuantity(int itemQuantity);
	void setItemPrice(double itemPrice);

	double calcTotalItemPrice(int itemQuantity, double itemPrice);

	string toString(); // output
};

#endif