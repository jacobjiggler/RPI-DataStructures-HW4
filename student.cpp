//  File: student.cpp
// Purpose: Implementation of the class student.h
#include <iostream>
#include <list>
#include <fstream>
#include "student.h"

using namespace std;

//main student class declaration
Student::Student(string student_name) {
Name = student_name;
bestOffer = " has not received an acceptable offer";

}
//add a school
void Student::AddSchool(string _name){
	for (std::list<string>::iterator school_itr = schoollist.begin(); school_itr != schoollist.end(); school_itr++){
if (*school_itr == _name){
	cerr << "WARNING: could not add " << _name << " into student preference list, this school is already in the list" << endl;
	 return;
}
}
	
	schoollist.push_back(_name);

}
//does this student already have an offer
bool Student::HasOffer(){
	return (bestOffer != " has not received an acceptable offer");
}
//Return the best offer
string Student::GetBestOffer(){
	return bestOffer;
	
}

void Student::PrepareToReceiveOffers(){
	//why is this here
}
//return student name
string Student::GetName() const{
return Name;
}
//checks to see if the student wants to take the new offer over a previous one or none at all
bool Student::IsOfferTentativelyAccepted(string school_name){

for (std::list<string>::iterator school_itr = schoollist.begin(); school_itr != schoollist.end(); school_itr++){
if (*school_itr == bestOffer){
	//if old offer is more favorable take this one
	return false;
}
//if new offer is more favorable take the new one
if (*school_itr == school_name){
bestOffer = school_name;
	return true;
}
}

	//just dont change anything. None on list
	return false;
}
//Prints the final Decision of the student
void Student::PrintStudentDecision(std::ofstream &ostr) const{
if (bestOffer == " has not received an acceptable offer"){
	ostr << Name << bestOffer << endl;
}
else {
	ostr << Name << " will be attending " << bestOffer << endl;
}
}
//sort by ame
bool alpha_by_student_name(const Student & a, const Student & b){

return (a.GetName() < b.GetName());	
}
