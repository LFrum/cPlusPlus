// OCCCPerson.h

#ifndef OCCCPERSON_H
#define OCCCPERSON_H

#include "OCCCDate.h"
#include "Person.h"

#include <string>
using namespace std;

class OCCCPerson : public OCCCDate, public Person {
	
private:
	
	string firstName;
	string lastName;
	OCCCDate dob;
	string studentID;

public:
	
	OCCCPerson(string firstName, string lastName, OCCCDate dob, string studentID);
	OCCCPerson(Person p, string studentID);

	string getStudentID();
	string getFirstName();
	string getLastName();
	OCCCDate getDate();

	void setFirstName(string firstName);
	void setLastName(string lastName);
	void setOCCCDate(OCCCDate dob);

	bool equals(OCCCPerson p); // ignore case in name
	string toString(); // format Lastname, Firstname (dob) [studentID]

};
#endif