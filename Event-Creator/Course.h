/* 
 * File:   Course.h
 * Author: connor
 *
 * Created on March 4, 2013, 10:20 AM
 */
#include <vector>
#include "Node.h"

#ifndef COURSE_H
#define	COURSE_H

class Course {
public:
    Course(const char theCourseID);
    virtual ~Course();
    void addCourseNode(Node *newNode);
    void setCourseSize(int courseSize);
    int getCourseSize() const;
    std::vector<Node*> getCourseNodes() const;
    const char getCourseID() const;
private:
    const char courseID;
    std::vector<Node*> courseNodes;
    int courseSize;
};

#endif	/* COURSE_H */

