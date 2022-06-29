//OCCCDate.h
//http://stackoverflow.com/questions/10387630/string-in-header-file

#ifndef OCCCDATE_H
#define OCCCDATE_H

#include <string>
using namespace std;

class OCCCDate {

private:

	int dayOfMonth;
	int monthOfYear;
	int year;
	bool dateFormat = true; // defaults to true; if true use US date format
							//					 if false use European date format

public:

	OCCCDate(); // default constractors 
	OCCCDate(int day, int month, int year);

	int getDayOfMonth();
	int getMonth();
	string getNameOfMonth();
	int getYear();
	int getDifference(OCCCDate d1); //elapsed time in years
	int getDifference(); // elapsed time in years from current time
	
	void setDateFormat(bool dateFormat); // sets date format
	bool equals(OCCCDate d); // compare only month, day, year
	string toString(); // output formatted date string as mm/dd/yyyy or dd/mm/yyyy
					  // depending on value of dateFormat
};

#endif