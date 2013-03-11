/* 
 * File: Entrant.cpp
 * Description: Provides a data model for an entrant in an event.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#include "Entrant.h"
#include <iostream>

using namespace std;


/**
 * Constructor that allows the constant 'entrant_name' and 'entrant_no' variables
 * to be specified. Also specifies the ID of the course the entrant is registered for.
 * @param theName The inputted name of the entrant.
 * @param theEnNo The inputted unique entrant number.
 * @param theCourseID The new course ID value to be set.
 */
Entrant::Entrant(const string &theName, const int theEnNo, char theCourseID) : entrantName(theName), entrantNo(theEnNo){
    
    courseID = theCourseID;
}

/**
 * Destructor to be used once object is removed.
 */
Entrant::~Entrant() {
    
}

/**
 * Fetches the name of the entrant.
 * @return A string containing the name of the entrant.
 */
string Entrant::getEntrantName(void) {
    return entrantName;
}

/**
 * Fetches the ID number of the entrant.
 * @return An integer containing the entrant number.
 */
int Entrant::getEntrantNo(void) {
    return entrantNo;
}

/**
 * Fetches the ID of the course the entrant is registered for.
 * @return An char containing the course ID.
 */
char Entrant::getCourseID(void) {
    return courseID;
}