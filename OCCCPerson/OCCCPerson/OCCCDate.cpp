// OCCCDate.cpp
/*
http://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
http://www.cplusplus.com/forum/beginner/3405/ Concatenate a string with an int.
*/


#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include "OCCCDate.h"

using namespace std;

time_t now = time(0);
tm *ltm = localtime(&now);

OCCCDate::OCCCDate() { // default constractors 
	this->dayOfMonth = ltm->tm_mday;
	this->monthOfYear = 1 + ltm->tm_mon;
	this->year = 1900 + ltm->tm_year;
}

OCCCDate::OCCCDate(int day, int month, int year) {
	this->dayOfMonth = day;
	this->monthOfYear = month;
	this->year = year;
}

int OCCCDate::getDayOfMonth() {
	return dayOfMonth;
}

int OCCCDate::getMonth() {
	return monthOfYear;
}

string OCCCDate::getNameOfMonth() {
	if (getMonth() == 1) {
		return "Jan";
	}
	else if (getMonth() == 2) {
		return "Feb";
	}
	else if (getMonth() == 3) {
		return "Mar";
	}
	else if (getMonth() == 4) {
		return "Apr";
	}
	else if (getMonth() == 5) {
		return "May";
	}
	else if (getMonth() == 6) {
		return "Jun";
	}
	else if (getMonth() == 7) {
		return "Jul";
	}
	else if (getMonth() == 8) {
		return "Aug";
	}
	else if (getMonth() == 9) {
		return "Sep";
	}
	else if (getMonth() == 10) {
		return "Oct";
	}
	else if (getMonth() == 11) {
		return "Nov";
	}
	else if (getMonth() == 12) {
		return "Dec";
	}
	else {
		return "Invalid input! Month is 1 - 12 only.";
	}
}
int OCCCDate::getYear() {
	return year;
}

int OCCCDate::getDifference(OCCCDate d1) { //elapsed time in years
	return year - d1.year;
}

// elapsed time in years from current time
int OCCCDate::getDifference() {
	// current date/time based on current system
	time_t now = time(0);

	tm *ltm = localtime(&now);

	return (1900 + ltm->tm_year) - year;
}

void OCCCDate::setDateFormat(bool dateFormat) { // sets date format
	this->dateFormat = dateFormat;
}

// compare only month, day, year
bool OCCCDate::equals(OCCCDate d) {
	if (dayOfMonth == d.getDayOfMonth() && monthOfYear == d.getMonth() && year == d.getYear()) {
		return true;
	}
	else {
		return false;
	}
}

// output formatted date string as mm/dd/yyyy or dd/mm/yyyy
// depending on value of dateFormat
string OCCCDate::toString() {
	stringstream outputDate;

	// defaults to true; if true use US date format
	//					  if false use European date format
	if (dateFormat == true) {
		outputDate << monthOfYear << "/" << dayOfMonth << "/" << year << " - US format";
		
	}
	else if (dateFormat == false) {
		outputDate << dayOfMonth << "/" << monthOfYear << "/" << year << " - EU format";		
	}

	return outputDate.str();
}