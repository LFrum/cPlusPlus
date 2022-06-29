//Entertainment.h
//http://stackoverflow.com/questions/10387630/string-in-header-file

#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include <string>
using namespace std;

class Entertainment {

private:

	string filename;
	string itemDescription;
	int itemQuantity;
	double itemPrice;
	double taxPrice;

public:

	Entertainment (string filename); // default constractors 
	Entertainment (string filename, string itemDescription, int itemQuantity, double itemPrice, double taxPrice);

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