/* 
 * File: Course.cpp
 * Description: Provides a data model for an event course.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#include "Course.h"

using namespace std;

/**
 * Constructor that allows the constant 'courseID' variable
 * to be specified. Also defaults the size of a course to 0.
 * @param theCourseID The new course ID value to be set.
 */
Course::Course(const char theCourseID) : courseID(theCourseID) {
    courseSize = 0;
}

/**
 * Destructor to be used once object is removed.
 */
Course::~Course() {
    
}

/**
 * Adds a new node to the end of the 'courseNode' vector.
 * @param newNode Pointer to the new node to be added to the vector.
 */
void Course::addCourseNode(Node *newNode) {

    this->courseNodes.push_back(newNode);
    this->setCourseSize(courseNodes.size());

}

/**
 * Updates the total size of the course. (i.e. vector size).
 * @param courseSize The new size value.
 */
void Course::setCourseSize(int courseSize) {
    this->courseSize = courseSize;
}

/**
 * Fetches the value of 'courseSize'.
 * @return The total number of nodes in the course.
 */
int Course::getCourseSize(void) const {
    return courseSize;
}

/**
 * Fetches a vector of all the nodes in the course.
 * @return A vector of nodes that make up the course.
 */
std::vector<Node*> Course::getCourseNodes(void) const {
    return courseNodes;
}

/**
 * Fetches the ID of the course.
 * @return The ID of the course.
 */
const char Course::getCourseID(void) const {
    return courseID;
}

