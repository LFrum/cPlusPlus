#include "Entertainment.h"

Entertainment::Entertainment(string filename) {
	this->filename = filename;
}
Entertainment::Entertainment(string filename, string itemDescription, int itemQuantity, double itemPrice, double taxPrice) {
	this->filename = filename;
	this->itemDescription = itemDescription;
	this->itemQuantity = itemQuantity;
	this->itemPrice = itemPrice;
	this->taxPrice = taxPrice;
}

string Entertainment::getFilename() {
	return filename;
}
string Entertainment::getItemDescription() {
	return itemDescription;
}
int Entertainment::getItemQuantity() {
	return itemQuantity;
}
double Entertainment::getItemPrice() {
	return itemPrice;
}
double Entertainment::getTaxPrice() {
	return taxPrice;
}


void Entertainment::setFilename(string filename) {
	this->filename = filename;
}
void Entertainment::setItemDescription(string itemDescription) {
	this->itemDescription = itemDescription;
}
void Entertainment::setItemQuantity(int itemQuantity) {
	this->itemQuantity = itemQuantity;
}
void Entertainment::setItemPrice(double itemPrice) {
	this->itemPrice = itemPrice;
}
void Entertainment::setTaxPrice(double taxPrice) {
	this->taxPrice = taxPrice;
}

double Entertainment::calcTotalItemPrice() {
	return itemPrice*itemQuantity*(itemPrice + 1);
}

string Entertainment::toString() {
	return itemDescription + " " + to_string(itemPrice) + " " + to_string(itemQuantity) + " " + to_string(calcTotalItemPrice());
}