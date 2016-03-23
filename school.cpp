//  File: school.cpp
// Purpose: Implementation of the class school.h
#include <iostream>
#include <list>
#include <fstream>
#include "school.h"

using namespace std;

//main school class initialization
School::School(string& school_name, int& num_slots) { 
Name = school_name;
num_Slots = num_slots;
acceptedstudents = 0;
offers = 0;
}
//add a student
void School::AddStudent(string _name){
for (std::list<string>::iterator student_itr = studentlist.begin(); student_itr != studentlist.end(); student_itr++){
if (*student_itr == _name){
	//checks if the student is already added
	cerr << "WARNING: could not add " << _name << " into school preference list, this student is already in the list" << endl;
	 return;
}
}
	studentlist.push_back(_name);
}
void School::PrepareToMakeOffers(){
	//there is no point in this
}
//return names
string School::GetName() const{
	return Name;
}
//return accepted students
int School::NumAcceptedStudents(){
	return acceptedstudents;
}
//return max amount of students allowed
int School::MaxAcceptedStudents(){
	return num_Slots;
}
//offers to the next student
string School::MakeNextOffer(){
offers++;	
//amount of offers so far
int i = 0;
string g;
//return the name of the one offered to
for (std::list<string>::iterator student_itr = studentlist.begin(); student_itr != studentlist.end() && i < offers; student_itr++){
g = *student_itr;
i++;
}
if (i == offers)
return g;
else
	//if none left return blank
	return "";

}
//student accept offer and list is  pushed back with that student
void School::StudentTentativelyAcceptsOffer(string a){
	acceptedstudentlist.push_back(a);
	acceptedstudents++;
}
//a student who has already accepted declines it
void School::StudentDeclinesTentativeAcceptance(string a){
	for (std::list<string>::iterator student_itr = acceptedstudentlist.begin(); student_itr != acceptedstudentlist.end(); student_itr++){
	if (*student_itr == a){
		student_itr = acceptedstudentlist.erase(student_itr);
		acceptedstudents--;
		return;
	}
	}
	//test
	cerr << a << endl;
}
//print all the students enrolling at the school
void School::PrintSchoolEnrollment(std::ofstream &ostr){
   ostr << "student(s) who will be attending " << Name << ":" << endl;
   acceptedstudentlist.sort(secondary);
	for (std::list<string>::iterator student_itr = acceptedstudentlist.begin(); student_itr != acceptedstudentlist.end(); student_itr++){
	ostr << "  " << *student_itr << endl;
	}
	if (num_Slots - acceptedstudents > 0){
		ostr << "  [" << (num_Slots - acceptedstudents) << " remaining slot(s) in enrollment]" << endl;
	}
}
//sort functions
bool alpha_by_school_name(const School & a, const School & b){
return (a.GetName() < b.GetName());	
}
bool secondary(const string & a, const string & b){
return (a < b);	
}