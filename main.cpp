//TO DO

//ORDER NOTATION

#include <iostream>
#include <fstream>
#include <list>
#include <cassert>
#include <cstdlib>

#include "school.h"
#include "student.h"
using namespace std;
// ==========================================================================================
// IMPORTANT: Carefully read this file, but do not make any changes to
//            the code, except to fill in code where indicated, and 
//            (optionally) add appropriate error messages.
// ==========================================================================================

// read the data for a school & add to the schools list
void AddSchool(std::istream &istr, std::list<School> &schools) {
  std::string school_name, student_name;
  int num_slots, num_prefs;
  istr >> school_name >> num_slots >> num_prefs;
  // create the school
  School s(school_name, num_slots);
  for (int i = 0; i < num_prefs; i++) {
    istr >> student_name;
    // add the students in the order listed
    s.AddStudent(student_name);
  }
  //check to see if this school is already in the list
    for (std::list<School>::iterator school_itr = schools.begin(); school_itr != schools.end(); school_itr++){
	  if ((*school_itr).GetName() == school_name)
		  return;
  }
  // add to the schools list
  schools.push_back(s);
}

// read the data for a student & add to the students list
void AddStudent(std::istream &istr, std::list<Student> &students) {
  std::string student_name, school_name;
  int num_prefs;
  istr >> student_name >> num_prefs;
  
  // Create the student
  Student s(student_name);
  for (int i = 0; i < num_prefs; i++) {
    istr >> school_name;
    // add the schools in the order listed
    s.AddSchool(school_name);
  }
   //check to see if this student is already in the list
  for (std::list<Student>::iterator student_itr = students.begin(); student_itr != students.end(); student_itr++){
	  if ((*student_itr).GetName() == student_name)
		  return;
  }
  // add to the students list
  students.push_back(s);
}

// ==========================================================================================

// read data and add a student into a school's preference list
void InsertStudentIntoSchoolPreferenceList(std::istream &istr, std::list<School> &schoolsedit) {
	//takes in strings
  std::string new_student_name, school_name, insert_before_student_name;
  istr >> school_name >> new_student_name >> insert_before_student_name;


 //finds the right school
  for (std::list<School>::iterator school_itr = schoolsedit.begin(); school_itr != schoolsedit.end(); school_itr++){
  if ((*school_itr).GetName() == school_name){
	  std::list<string>::iterator student_itr2;
	  
	   bool check = false;
	   //finds the right student
	for (std::list<string>::iterator student_itr = (*school_itr).studentlist.begin(); student_itr != (*school_itr).studentlist.end(); student_itr++){
		
	 
	  //checks for repeat
	if (*student_itr == new_student_name){
		cerr << "WARNING: could not add " << new_student_name << " into school preference list, this student is already in the list" << endl;
		return;
	}
	//check to see if the same student
	if (*student_itr == insert_before_student_name){
	 student_itr2 = student_itr;
	 check = true;
	}
	}
	 if (check){
		 //actual insert
	  (*school_itr).studentlist.insert(student_itr2,new_student_name);
		 	return;
  }
	  //the student before is not in list
	cerr << "WARNING: could not insert new student into school preference list before " << insert_before_student_name << ", this student is not in the list" << endl;
	  return;
  }
	  
	  
  }
  //bad school
  cerr << "WARNING: could not insert student into school preference list, no school named " << school_name << endl;
  //PrintSchoolPreferencesList(istr,schools,test.txt);
}

// read data and remove a particular school from a student's preference list
void RemoveSchoolFromStudentPreferenceList(std::istream &istr, std::list<Student> &studentsedit) {
  std::string school_name, student_name;
  //taking names and schools from instring
  istr >> student_name >> school_name;

    for (std::list<Student>::iterator student_itr = studentsedit.begin(); student_itr != studentsedit.end(); student_itr++){
		//check to see if the same student
  if ((*student_itr).GetName() == student_name){
	for (std::list<string>::iterator school_itr = (*student_itr).schoollist.begin(); school_itr != (*student_itr).schoollist.end(); school_itr++){
	
	//check to see if the same school
	 if (*school_itr == school_name){
	  (*student_itr).schoollist.erase(school_itr);
		 	return;
  }
	  }
	//bad school name check
	cerr << "WARNING: could not remove school from student preference list, no school named " << school_name << endl;
	  return;
  }
  }
	//bad student name check
  cerr << "WARNING: could not remove school from student preference list, no student named " << student_name << endl;

 
}

// ==========================================================================================
// The Gale-Shapley algorithm to solve the Stable Marriage Problem

void PerformMatching(std::list<School> &schools, std::list<Student> &students, std::ofstream &ostr) {
  // Perform any initialization necessary for the school and student objects
  for (std::list<School>::iterator itr = schools.begin(); itr != schools.end(); itr++) {
	  //useless crap
    itr->PrepareToMakeOffers(); 
  }
  for (std::list<Student>::iterator itr = students.begin(); itr != students.end(); itr++) {
	  //more useless crap
    itr->PrepareToReceiveOffers();
  }
  // a bool value to be kept through the program.
bool check = true;
  // Iterate until the matching is stable (no changes)
  int which_iteration = 1;
  while(1) {
    ostr << "---- ROUND " << which_iteration << " ----" << std::endl;
    which_iteration++;
    // keep track of the offers made during this round
    int offers_made = 0;
    
    for (std::list<School>::iterator school_itr = schools.begin(); school_itr != schools.end(); school_itr++) {
	  if (school_itr->NumAcceptedStudents() == school_itr->MaxAcceptedStudents()) continue;

      // Each school that has open slots, makes an offer to the next student on their preference list
      std::string student = school_itr->MakeNextOffer();
      // an empty string indicates that this school has reached the end of its preference list
      if (student == "") continue;
      ostr << school_itr->GetName() << " makes an offer to " << student << std::endl;
      offers_made++;

      for (std::list<Student>::iterator student_itr = students.begin(); student_itr != students.end(); student_itr++) {
	// loop through the students to find the student object with that name
	if (student_itr->GetName() == student) {
	  check = false;
	  // check to see if that student has tentatively accepted an offer from another school
	  std::string current_choice = "";
	  if (student_itr->HasOffer()) { 
	    current_choice = student_itr->GetBestOffer(); 
	  }
	  // make the offer to the student, returns true if the school is on the student's 
	  // preference list and is better than the students current offer (if any)
	  bool tentative_acceptance = student_itr->IsOfferTentativelyAccepted(school_itr->GetName());
	  if (!tentative_acceptance) {
	    ostr << "  " << student << " declines offer from " << school_itr->GetName() << std::endl;
	  } else {
	    if (current_choice != "") {
	      // if the student had a prior acceptance, decline the earlier offer
	      for (std::list<School>::iterator school2_itr = schools.begin(); school2_itr != schools.end(); school2_itr++) {
		if (school2_itr->GetName() == current_choice) {
		  ostr << "  " << student << " withdraws tentative acceptance of offer from " << current_choice << std::endl;		
		  school2_itr->StudentDeclinesTentativeAcceptance(student);
		}
	      }	    
	    }
	    // student tentatively accepts the offer from the (new) school
	    school_itr->StudentTentativelyAcceptsOffer(student);
	    ostr << "  " << student << " tentatively accepts offer from " << school_itr->GetName() << std::endl;
	  }
	}
      }
	  //bad student check
	  if (check){
	cout <<"WARNING: could not make offer to student " << student << ", that student does not exist" << endl;
	  }
    }
	// the end
    if (offers_made == 0) {
      ostr << "no offers_made this round" << std::endl << std::endl;
      break;
    }
  }
}

// ==========================================================================================
// PRINTING

// Print the ranking of students by a particular school
void PrintSchoolPreferenceList(std::istream &istr, const std::list<School> &schools, std::ostream &ostr) {
  std::string school_name;
  //takes in string
  istr >> school_name;

//i = numbering and used for a check
int i = 0;
for (std::list<School>::const_iterator school_itr = schools.begin(); school_itr != schools.end(); school_itr++){
	//same school check
  if ((*school_itr).GetName() == school_name){
	  i = 1;
	  //print header
	 ostr << school_name << " preference list:" << endl;
	//rest of printing
	for (std::list<string>::const_iterator student_itr = (*school_itr).studentlist.begin(); student_itr != (*school_itr).studentlist.end(); student_itr++){
	if (i < 10)
	ostr << "  " << i << ". " << *student_itr << endl;
	else {
		ostr << " " << i << ". " << *student_itr << endl;
	}
		i++;
		
	
	}
	 
	  
ostr << endl;
	  break;
  } 
  }
if (i == 0)
	//no schools listed check
cerr << "WARNING: could not print student preference list for " << school_name << ", that school does not exist" << endl;


}

// Print a ranking of schools by a particular student
void PrintStudentPreferenceList(std::istream &istr, const std::list<Student> &students, std::ostream &ostr) {
  std::string student_name;
  //taking student name from instring
  istr >> student_name;

//numbering and used for a check
int i = 0;
for (std::list<Student>::const_iterator student_itr = students.begin(); student_itr != students.end(); student_itr++){
	//check if student names are the same
  if ((*student_itr).GetName() == student_name){
	  i = 1;
	  //print header
	 ostr << student_name << " preference list:" << endl; 
	//print schools
	for (std::list<string>::const_iterator school_itr = (*student_itr).schoollist.begin(); school_itr != (*student_itr).schoollist.end(); school_itr++){
		if (i < 10)
	ostr << "  " << i << ". " << *school_itr << endl;
	else {
		ostr << " " << i << ". " << *school_itr << endl;
	}
		i++;
	}
	ostr << endl;
	  break;
  } 
  }
if (i == 0)
	//no students check
cerr << "WARNING: could not print school preference list for " << student_name << ", that student does not exist" << endl;



}

// Print the list of all schools (sorted alphabetically) and the students enrolled (also alphabetically)
void PrintSchoolEnrollments(std::list<School> &schools, std::ofstream &ostr) {
  schools.sort(alpha_by_school_name);
  for (std::list<School>::iterator itr = schools.begin(); itr != schools.end(); itr++) {
    itr->PrintSchoolEnrollment(ostr);
  }
  ostr << std::endl;
}

// Print a list of the students (sorted alphabetically) and the school they will attend (if any)
void PrintStudentDecisions(std::list<Student> &students, std::ofstream &ostr) {
	//sort by name
  students.sort(alpha_by_student_name);
  for (std::list<Student>::const_iterator itr = students.begin(); itr != students.end(); itr++) {
	  //print student decisions one at a time
    itr->PrintStudentDecision(ostr);
  }
  ostr << std::endl;
}

// ==========================================================================================

int main(int argc, char* argv[]) {

  // process command line arguments
  if (argc != 3) {
    std::cerr << "ERROR: incorrect number of command line arguments" << std::endl;
    std::cerr << "USAGE:   " << argv[0] << " <input_file> <output_file>" << std::endl;
    exit(1);
  }
  // open the input file for parsing
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "ERROR: could not open input file " << argv[1] << std::endl;
    exit(1);
  }
  // open the output file
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "ERROR: could not open output file " << argv[2] << std::endl;
    exit(1);
  }

  // lists to store school and student objects
  std::list<School> schools;
  std::list<Student> students;

  // parse the file
  std::string keyword;
  while(istr >> keyword) {
    if (keyword == std::string("add_school")) {
      AddSchool(istr,schools);
    } else if (keyword == std::string("insert_student_into_school_preference_list")) {
      InsertStudentIntoSchoolPreferenceList(istr,schools);
    } else if (keyword == std::string("print_school_preferences")) {
      PrintSchoolPreferenceList(istr,schools,ostr);
    }

    else if (keyword == std::string("add_student")) { 
      AddStudent(istr,students);
    } else if (keyword == std::string("remove_school_from_student_preference_list")) { 
      RemoveSchoolFromStudentPreferenceList(istr,students);
    } else if (keyword == std::string("print_student_preferences")) {
      PrintStudentPreferenceList(istr,students,ostr);
    } 

    else if (keyword == std::string("perform_matching")) {
      PerformMatching(schools,students,ostr);
    } else if (keyword == std::string("print_school_enrollments")) {
      PrintSchoolEnrollments(schools,ostr);
    } else if (keyword == std::string("print_student_decisions")) {
      PrintStudentDecisions(students,ostr);
    } else {
      std::cerr << "unknown keyword in input file: " << keyword << std::endl;
      exit(1);
    }
  }
}

// ==========================================================================================
