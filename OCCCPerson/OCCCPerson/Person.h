//Person.h
//http://stackoverflow.com/questions/10387630/string-in-header-file

#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {

private:

	string firstName;
	string lastName;
	OCCCDate dob;

public:

	Person(string firstName, string lastName); // default constractors 
	Person(string firstName, string lastName, OCCCDate dob);

	string getFirstName();
	string getLastName();
	OCCCDate getDate();

	void setFirstName(string firstName);
	void setLastName(string lastName);

	int getAgeInYears();
	bool equals(Person p);

	bool equalsIgnoreCase(string s1, string s2); // helper function for equals
	string toUpperCase(string s);

	string toString(); // output "Lastname, Firstname (dob)"

};

#endif