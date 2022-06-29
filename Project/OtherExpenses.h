//OtherExpenses.h
//http://stackoverflow.com/questions/10387630/string-in-header-file

#ifndef OTHEREXPENSES_H
#define OTHEREXPENSES_H

#include <string>
using namespace std;

class OtherExpenses {

private:

	string filename;
	string itemDescription;
	int itemQuantity;
	double itemPrice;
	double taxPrice;

public:

	OtherExpenses(string filename); // default constractors 
	OtherExpenses(string filename, string itemDescription, int itemQuantity, double itemPrice, double taxPrice);

	string getFilename();
	string getItemDescription();
	int getItemQuantity();
	double getItemPrice();
	double getTaxPrice();


	void setFilename(string filename);
	void setItemDescription(string itemDescription);
	void setItemQuantity(int itemQuantity);
	void setItemPrice(double itemPrice);
	void setTaxPrice(double taxPrice);

	double calcTotalItemPrice();

	string toString(); // output
};

#endif