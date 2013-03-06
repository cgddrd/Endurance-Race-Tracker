/* 
 * File:   Entrant.cpp
 * Author: connor
 * 
 * Created on March 4, 2013, 10:21 AM
 */

#include "Entrant.h"
#include <iostream>


Entrant::Entrant(const std::string &theName, const int theEnNo, char theCourseID) : entrant_name(theName), entrant_no(theEnNo){
    
    course_id = theCourseID;
}

Entrant::~Entrant() {
    
}

std::string Entrant::getEntrantName(void) {
    return entrant_name;
}

int Entrant::getEntrantNo(void) {
    return entrant_no;
}

char Entrant::getCourseID(void) {
    return course_id;
}

void Entrant::print(void) const {
    using namespace std;
    cout << "Entrant name: " << entrant_name << ' ';
    cout << "Employee no: " << entrant_no << ' ';
    cout << "Course ID: " << course_id << endl;
}

