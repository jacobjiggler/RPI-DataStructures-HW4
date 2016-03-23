//  File: student.h
// Purpose: Header for declaration of student class and associated functions.
#ifndef __student_h_
#define __student_h_
#include <iostream>
#include <list>
#include <fstream>

using namespace std;

class Student{
	
private:
string Name;
	
	string bestOffer;
		
public:
Student(string student_name);
std::list<string> schoollist;
void AddSchool(string _name);
string GetBestOffer();
bool HasOffer();
void PrepareToReceiveOffers();
string GetName() const;
bool IsOfferTentativelyAccepted(string school_name);
void PrintStudentDecision(std::ofstream &ostr) const;

};




//should be treated differently
bool alpha_by_student_name(const Student & a, const Student & b);
#endif