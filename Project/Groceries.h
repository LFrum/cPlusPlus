//Groceries.h
//http://stackoverflow.com/questions/10387630/string-in-header-file

#ifndef GROCERIES_H
#define GROCERIES_H

#include <string>
using namespace std;

class Groceries {

private:

	string filename;
	string itemDescription;
	int itemQuantity;
	double itemPrice;
	double taxPrice;

public:

	Groceries(string filename); // default constractors 
	Groceries(string filename, string itemDescription, int itemQuantity, double itemPrice, double taxPrice);

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