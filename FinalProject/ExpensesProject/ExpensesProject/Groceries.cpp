#include "Groceries.h"
#include <iostream>


Groceries::Groceries(string filename)
{
	this->filename = filename;
}
Groceries::Groceries(string filename, string itemDescription, int itemQuantity, double itemPrice, double taxPrice) {
	this->filename = filename;
	this->itemDescription = itemDescription;
	this->itemQuantity = itemQuantity;
	this->itemPrice = itemPrice;
	this->taxPrice = taxPrice;
}

string Groceries::getFilename() {
	return filename;
}
string Groceries::getItemDescription() {
	return itemDescription;
}
int Groceries::getItemQuantity() {
	return itemQuantity;
}
double Groceries::getItemPrice() {
	return itemPrice;
}
double Groceries::getTaxPrice() {
	return taxPrice;
}


void Groceries::setFilename(string filename) {
	this->filename = filename;
}
void Groceries::setItemDescription(string itemDescription) {
	this->itemDescription = itemDescription;
}
void Groceries::setItemQuantity(int itemQuantity) {
	this->itemQuantity = itemQuantity;
}
void Groceries::setItemPrice(double itemPrice) {
	this->itemPrice = itemPrice;
}
void Groceries::setTaxPrice(double taxPrice) {
	this->taxPrice = taxPrice;
}

double Groceries::calcTotalItemPrice() {
	return itemQuantity*itemPrice*(1 + taxPrice);
}

string Groceries::toString() {
	return itemDescription + " " + to_string(itemPrice) + " " + to_string(itemQuantity) + " " + to_string(calcTotalItemPrice());
}