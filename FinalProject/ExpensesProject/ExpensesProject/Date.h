//Expenses.h
//http://stackoverflow.com/questions/10387630/string-in-header-file

#ifndef DATE_H
#define DATE_H

#include<string>
using namespace std;

class Date {
private:

	int dayOfMonth;
	int monthOfYear;
	int year;

public:

	Date();
	Date(int day, int month, int year);
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	string toString();
};
#endif 