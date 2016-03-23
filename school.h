//  File: school.h
// Purpose: Header for declaration of school class and associated functions.
#ifndef __school_h_
#define __school_h_

#include <iostream>
#include <list>
#include <fstream>
using namespace std;

class School{
	
private:
		string Name;
		int num_Slots;
	
	std::list<string> acceptedstudentlist;
		int acceptedstudents;
		int offers;
public:
School(string& school_name, int& num_slots);
std::list<string> studentlist;
void AddStudent(string _name);
void PrepareToMakeOffers();
string GetName() const;
int NumAcceptedStudents();
int MaxAcceptedStudents();
string MakeNextOffer();
void StudentTentativelyAcceptsOffer(string a);
void StudentDeclinesTentativeAcceptance(string a);
void PrintSchoolEnrollment(std::ofstream &ostr);
};




//should be treated differently
bool alpha_by_school_name(const School & a, const School & b);
bool secondary(const string & a, const string & b);
#endif