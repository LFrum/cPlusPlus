// Person.cpp
/*
http://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
http://stackoverflow.com/questions/23418390/how-to-convert-a-c-string-to-uppercase
*/

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <algorithm> 
#include <functional>
#include <cctype>
#include "OCCCDate.h"
#include "Person.h"

using namespace std;

// default constractors 
Person::Person(string firstName, string lastName) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->dob = OCCCDate();
}

Person::Person(string firstName, string lastName, OCCCDate dob) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->dob = dob;
}

string Person::getFirstName() {
	return firstName;
}
string Person::getLastName() {
	return lastName;
}

OCCCDate Person::getDate() {
	return dob;
}

void Person::setFirstName(string firstName) {
	this->firstName = firstName;
}
void Person::setLastName(string lastName) {
	this->lastName = lastName;
}

int Person::getAgeInYears() {
	time_t now = time(0);

	tm *ltm = localtime(&now);

	return (1900 + ltm->tm_year) - dob.getYear();
}

bool Person::equals(Person p) {
	if (equalsIgnoreCase(firstName, p.firstName) && equalsIgnoreCase(lastName, p.lastName)
		&& dob.equals(p.getDate())) {
		return true;
	}
	else {
		return false;
	}
}

// helper function for equals
bool Person::equalsIgnoreCase(string s1, string s2) {
	if (toUpperCase(s1) == toUpperCase(s2)) {
		return true;
	}
	else {
		return false;
	}
}
string Person::toUpperCase(string s) {
	//string sUpper;
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

// output "Lastname, Firstname (dob)"
string Person::toString() {
	return lastName + ", " + firstName + " (" + dob.toString() + ")";
}