#include "OtherExpenses.h"

OtherExpenses::OtherExpenses(string filename) {
	this->filename = filename;
}
OtherExpenses::OtherExpenses(string filename, string itemDescription, int itemQuantity, double itemPrice, double taxPrice) {
	this->filename = filename;
	this->itemDescription = itemDescription;
	this->itemQuantity = itemQuantity;
	this->itemPrice = itemPrice;
	this->taxPrice = taxPrice;
}

string OtherExpenses::getFilename() {
	return filename;
}
string OtherExpenses::getItemDescription() {
	return itemDescription;
}
int OtherExpenses::getItemQuantity() {
	return itemQuantity;
}
double OtherExpenses::getItemPrice() {
	return itemPrice;
}
double OtherExpenses::getTaxPrice() {
	return taxPrice;
}


void OtherExpenses::setFilename(string filename) {
	this->filename = filename;
}
void OtherExpenses::setItemDescription(string itemDescription) {
	this->itemDescription = itemDescription;
}
void OtherExpenses::setItemQuantity(int itemQuantity) {
	this->itemQuantity = itemQuantity;
}
void OtherExpenses::setItemPrice(double itemPrice) {
	this->itemPrice = itemPrice;
}
void OtherExpenses::setTaxPrice(double taxPrice) {
	this->taxPrice = taxPrice;
}

double OtherExpenses::calcTotalItemPrice() {
	return itemPrice*itemQuantity*(itemPrice + 1);
}

string OtherExpenses::toString() {
	return "Description: " + itemDescription + " Price: " + to_string(itemPrice) + " Quantity: " + to_string(itemQuantity) + " Total Price: " + to_string(calcTotalItemPrice());
}