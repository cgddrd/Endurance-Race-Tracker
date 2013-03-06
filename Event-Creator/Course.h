/* 
 * File: Course.h
 * Description: Defines all variables/methods for the Course class.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#include <vector>
#include "Node.h"

#ifndef COURSE_H
#define	COURSE_H

/**
 *  Course class used to define the data model for an event course.
 */
class Course {
    
public:
    Course(const char theCourseID);
    virtual ~Course();
    void addCourseNode(Node *newNode);
    void setCourseSize(int courseSize);
    int getCourseSize(void) const;
    std::vector<Node*> getCourseNodes(void) const;
    const char getCourseID(void) const;
private:

    const char courseID; /**< Unique ID for a Course.*/
    std::vector<Node*> courseNodes; /**< Vector of all nodes that make up a course. */
    int courseSize; /**< The total number of nodes in the course. */
};

#endif	/* COURSE_H */

