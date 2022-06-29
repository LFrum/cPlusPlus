// TestPerson.cpp
// OCCCPerson
// http://www.tutorialspoint.com/cplusplus/cpp_date_time.htm

#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include "OCCCDate.h"
#include "Person.h"
#include "OCCCPerson.h"
using namespace std;

//bool dateFormatSelection(OCCCDate d);

int main()
{
	string firstName;
	string lastName;
	int birthYear, birthMonth, birthDay;
	int todaysMonth, todaysDay, todaysYear;
	string studentID;

	cout << "Welcome to OCCCPerson Application!" << endl << endl;

	cout << "Please enter your first name: ";
	cin >> firstName;

	cout << "Please enter your last name: ";
	cin >> lastName;

	cout << "Please enter your birth year (ex.:1990): ";
	cin >> birthYear;

	cout << "Please enter your birth month (ex.:1): ";
	cin >> birthMonth;

	cout << "Please enter your birth day (ex.:18): ";
	cin >> birthDay;

	// current date/time based on current system
	time_t now = time(0);
	tm *ltm = localtime(&now);

	//OCCCDate d1 = OCCCDate (ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
	OCCCDate d1 = OCCCDate();
	d1.setDateFormat(true);
	cout << "Current time: " << d1.toString() << endl;

	OCCCDate d2 = OCCCDate (birthDay, birthMonth, birthYear);
	d2.setDateFormat(true);
	cout << "Date of birth: " << d2.toString() << endl;

	cout << "Please enter today’s date (month, day, year): ";
	cin >> todaysMonth >> todaysDay >> todaysYear;

	OCCCDate d3 = OCCCDate(todaysDay, todaysMonth, todaysYear);
	d3.setDateFormat(true);

	if (d1.equals(d3)) {
		cout << "Today's date is a match" << endl;
	}
	else {
		cout << "Today's date is not the same" << endl;
	}
	
	Person p1 = Person (firstName, lastName);
	Person p2 = Person (firstName, lastName, d2);


	cout << firstName << " " << lastName << " is " << p2.getAgeInYears() <<
		" years old." << endl;

	if (p1.equals(p2)) {
		cout << "Person 1 and Person 2 have the same name" << endl;
	}
	else {
		cout << "Person 1 and Person 2 does not have the same name" << endl;
	}

	Person p3 = Person (p1.getFirstName(), p1.getLastName(), d3);

	if (p1.equals(p3)) {
		cout << "Person 1 and Person 3 have the same name" << endl;
	}
	else {
		cout << "Person 1 and Person 3 does not have the same name" << endl;
	}

	cout << "Please enter a new last name: ";
	cin >> lastName;

	p3.setLastName(lastName);

	cout << "Person 3 info: " << p3.toString() << endl;

	cout << "Enter your student ID: ";
	cin >> studentID;

	OCCCPerson p4 = OCCCPerson (p3, studentID);
	OCCCPerson p5 = OCCCPerson(p5.toUpperCase(firstName), p5.toUpperCase(lastName), d2, studentID);

	if (p4.equals(p5)) {
		cout << "Person 4 and Person 5 is the same person" << endl;
	}
	else {
		cout << "Person 4 and Person 5 is not the same person" << endl;
	}

	OCCCPerson p6 = p5;

	if (p5.equals(p6)) {
		cout << "Person 5 and Person 6 is the same person" << endl;
	}
	else {
		cout << "Person 5 and Person 6 is not the same person" << endl;
	}

	cout << "Please enter a new last name: ";
	cin >> lastName;

	p6.setLastName(lastName);

	cout << "Person 5 info: " << p5.toString() << endl;
	cout << "Person 6 info: " << p6.toString() << endl;

	OCCCPerson p7 = OCCCPerson (p6);

	if (p6.equals(p7)) {
		cout << "Person 6 and Person 7 is the same person" << endl;
	}
	else {
		cout << "Person 6 and Person 7 is not the same person" << endl;
	}

	p6.setLastName("Hazard");

	cout << "Person 6 info: " << p6.toString() << endl;
	cout << "Person 7 info: " << p7.toString() << endl;

	return 0;
}