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
#include "Event.h"

class Datastore {
public:
    Datastore();
    virtual ~Datastore();
    std::vector<Course*> getCourseList(void);
    std::vector<Node*> getNodeList(void);
    std::vector<Entrant*> getEntrantList(void);
    Event* getEvent(void) const;
    void addNewCourse (Course* newCourse);
    void addNewNode (Node* newNode);
    void addNewEntrant (Entrant* newEntrant);
    void setNewEvent(Event* newEvent);
    Course* getInCourse (char courseID);
    Node* obtainNode (int nodeNo);
    
private:
   std::vector<Entrant*> entrantList;
   std::vector<Node*> nodeList;
   std::vector<Course*> courseList;
   Event *event;
};

#endif	/* DATASTORE_H */

