/* 
 * File:   Datastore.h
 * Author: connor
 *
 * Created on March 5, 2013, 4:40 PM
 */

#ifndef DATASTORE_H
#define	DATASTORE_H

#include <vector>
#include <cstdlib>
#include "Entrant.h"
#include "Node.h"
#include "Course.h"

class Datastore {
public:
    Datastore();
    virtual ~Datastore();
    std::vector<Course*> getCourseList();
    std::vector<Node*> getNodeList();
    std::vector<Entrant*> getEntrantList();
    void addNewCourse (Course* newCourse);
    void addNewNode (Node* newNode);
    void addNewEntrant (Entrant* newEntrant);
    Course* getInCourse (char courseID);
    Node* obtainNode (int nodeNo);
private:
   std::vector<Entrant*> entrantList;
   std::vector<Node*> nodeList;
   std::vector<Course*> courseList;
};

#endif	/* DATASTORE_H */

