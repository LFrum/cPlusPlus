// Expenses.cpp
/*
http://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
http://stackoverflow.com/questions/23418390/how-to-convert-a-c-string-to-uppercase
*/

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <cctype>
#include "Date.h"
#include "Expenses.h"

using namespace std;

// default constractors 
Expenses::Expenses(string filename) {
	this->filename = filename;
}

Expenses::Expenses(string filename, string itemDescription, int itemQuantity, double itemPrice, Date shopDate) {
	this->filename = filename;
	this->itemDescription = itemDescription;
	this->itemQuantity = itemQuantity;
	this->itemPrice = itemPrice;
	this->shopDate = Date();
}

string Expenses::getFilename() {
	return filename;
}

string Expenses::getItemDescription() {
	return itemDescription;
}

int Expenses::getItemQuantity() {
	return itemQuantity;
}
double Expenses::getItemPrice() {
	return itemPrice;
}
Date Expenses::getDate() {
	return shopDate;
}

void Expenses::setFilename(string filename) {
	this->filename = filename;
}
void Expenses::setItemDescription(string itemDescription) {
	this->itemDescription = itemDescription;
}
void Expenses::setItemQuantity(int itemQuantity) {
	this->itemQuantity = itemQuantity;
}
void Expenses::setItemPrice(double itemPrice) {
	this->itemPrice = itemPrice;
}

double Expenses::calcTotalItemPrice(int itemQuantity, double itemPrice) {
	return itemQuantity*itemPrice;
}

// output
string Expenses::toString() {
	return itemDescription + " " + to_string(itemQuantity) + " $" + to_string(calcTotalItemPrice(itemQuantity, itemPrice));
}