// OCCCPerson.cpp
/*
http://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
http://stackoverflow.com/questions/23418390/how-to-convert-a-c-string-to-uppercase
http://www.cplusplus.com/forum/beginner/3405/ Concatenate a string with an int.
*/

#include <iostream>
#include <string>
#include "OCCCDate.h"
#include "Person.h"
#include "OCCCPerson.h"

using namespace std;

OCCCPerson::OCCCPerson(string firstName, string lastName, OCCCDate dob, string studentID) : Person(firstName, lastName, dob){
	this->firstName = firstName;
	this->lastName = lastName;
	this->dob = dob;
	this->studentID = studentID;
}

OCCCPerson::OCCCPerson(Person p, string studentID) : Person (p){
	this->firstName = p.getFirstName();
	this->lastName = p.getLastName();
	this->dob = p.getDate();
	this->studentID = studentID;
}

string OCCCPerson::getStudentID() {
	return studentID;
}

string OCCCPerson::getFirstName() {
	return firstName;
}

string OCCCPerson::getLastName() {
	return lastName;
}

OCCCDate OCCCPerson::getDate() {
	return dob;
}

void OCCCPerson::setFirstName(string firstName) {
	this->firstName = firstName;
}
void OCCCPerson::setLastName(string lastName) {
	this->lastName = lastName;
}


void OCCCPerson::setOCCCDate(OCCCDate dob) {
	this->dob = dob;
}

// ignore case in name
bool OCCCPerson::equals(OCCCPerson p) {
	if (studentID == p.getStudentID() && equalsIgnoreCase(firstName, p.firstName) 
		&& equalsIgnoreCase(lastName, p.lastName) && dob.equals(p.getDate())) {
		return true;
	}
	else {
		return false;
	}
}

// format Lastname, Firstname (dob) [studentID]
string OCCCPerson::toString() {
	return lastName + ", " + firstName + "(" + dob.toString() + ")" + "[" + studentID + "]";
}