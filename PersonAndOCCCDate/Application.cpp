// Application.cpp
// Chapter 5 Hw
// http://www.tutorialspoint.com/cplusplus/cpp_date_time.htm

#include <iostream>
#include <ctime>
#include <cmath>
#include "OCCCDate.h"
#include "Person.h"
using namespace std;

bool dateFormatSelection(OCCCDate d);

int main()
{
	bool dateFormat;
	//OCCCDate

	OCCCDate d1 = OCCCDate();
	OCCCDate d2 = OCCCDate(4, 9, 1990);
	
	//Date 1 output
	cout << "The day entered for default date is " << d1.getDayOfMonth() << "." << endl;
	cout << "The month entered for default date is " << d1.getMonth() << "." << endl;
	cout << "The year entered for default date is " << d1.getYear() << "." << endl << endl;

	dateFormat=dateFormatSelection(d1);
	d1.setDateFormat(dateFormat);
	
	cout << "Default date: " << d1.toString() << "." << endl;
	cout << "The month for the format above is " << d1.getNameOfMonth() << "." << endl << endl;

	//Date 2 output
	cout << "The day entered for date 2 is " << d2.getDayOfMonth() << "." << endl;
	cout << "The month entered for date 2 is " << d2.getMonth() << "." << endl;
	cout << "The year entered for date 2 is " << d2.getYear() << "." << endl << endl;

	dateFormat = dateFormatSelection(d2);
	d2.setDateFormat(dateFormat);

	cout << "The date: " << d2.toString() << "." << endl;
	cout << "The month for the format above is " << d2.getNameOfMonth() << "." << endl << endl;


	if (d1.equals(d2)) {
		cout << "The date is the same." << endl;
	}
	else {
		cout << "The date is not the same." << endl;
	}

	cout << "The difference in years between the two dates: "
		<< abs(d1.getDifference(d2)) << " year(s)." << endl;
	cout << "The difference in years between default date and now: "
		<< d1.getDifference() << " year(s)." << endl << endl;

	//Person 
	string firstName;
	string lastName;

	Person p1 = Person(firstName, lastName);
	Person p2 = Person("Jackie", "Chan", d2);

	p1.setFirstName("Jackie");
	p1.setLastName("Chan");

	cout << "Name of person 1 is "<< p1.getFirstName() << " " << p1.getLastName() << "." << endl;
	cout << "Name of person 2 is " << p2.getFirstName() << " " << p2.getLastName() << "." << endl;

	cout << "Age of person 2 is " << p2.getAgeInYears() << " years old." << endl;

	if (p2.equals(p1)) {
		cout << "They are the same person." << endl;
	}
	else {
		cout << "They are not the same person." << endl;
	}
	
	cout << "Person 2 info : " << p2.toString() << "." << endl;

	return 0;
}

bool dateFormatSelection(OCCCDate d) {
	int selectTimeFormat;
	do {
		cout << "Do you want display the date in:" << endl;
		cout << "1. US Format, or" << endl;
		cout << "2. EU Format." << endl;
		cin >> selectTimeFormat;

		if (selectTimeFormat == 1) {
			return true;
		}
		else if (selectTimeFormat == 2) {
			return false;
		}
		else {
			cout << "Invalid selection!" << endl << endl;
		}
	} while (selectTimeFormat != 1 || selectTimeFormat != 2);
}