/* 
 * File:   Course.cpp
 * Author: connor
 * 
 * Created on March 4, 2013, 10:20 AM
 */

#include "Course.h"

Course::Course(const char theCourseID) : courseID(theCourseID) {
    
    courseSize = 0;
}

Course::~Course() {
}

void Course::addCourseNode(Node *newNode) {
    
    this->courseNodes.push_back(newNode);
    this->setCourseSize(courseNodes.size());
    
}

void Course::setCourseSize(int courseSize) {
    this->courseSize = courseSize;
}

int Course::getCourseSize() const {
    return courseSize;
}

std::vector<Node*> Course::getCourseNodes() const {
    return courseNodes;
}

const char Course::getCourseID() const {
    return courseID;
}

