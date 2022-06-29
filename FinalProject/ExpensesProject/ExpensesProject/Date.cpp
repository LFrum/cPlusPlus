//Date.cpp

#include "Date.h"
#include <iostream>
#include <ctime>

using namespace std;

time_t now = time(0);
tm*local = localtime(&now);
int currentYear = local->tm_year + 1900;
int currentMonth = local->tm_mon + 1;
int currentDay = local->tm_mday;

string month[] = { "January", "Feburary", "March", "April", "May", "June",
"July","Auguest", "September", "October", "November", "December" };

Date::Date() {
	this->dayOfMonth = currentDay;
	this->monthOfYear = currentMonth;
	this->year = currentYear;
}

Date::Date(int day, int month, int year) {
	this->dayOfMonth = day;
	this->monthOfYear = month;
	this->year = year;
}
void Date::setDay(int day) {
	this->dayOfMonth = day;
}
void Date::setMonth(int month) {
	this->monthOfYear = month;
}
void Date::setYear(int year) {
	this->year = year;
}
string Date::toString() {
	return to_string(monthOfYear) + "/" + to_string(dayOfMonth) + "/" + to_string(year);
}