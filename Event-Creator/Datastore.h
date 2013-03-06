/* 
 * File: Course.h
 * Description: Defines all variables/methods for the Datastore class.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#ifndef DATASTORE_H
#define	DATASTORE_H

#include <vector>
#include <cstdlib>
#include "Entrant.h"
#include "Node.h"
#include "Course.h"
#include "Event.h"

/**
 * Datastore class used for storing and providing access to all the of 
 * shared data used throughout the application..
 */
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
    
    /** Vector of pointers to all Entrant objects created. */
   std::vector<Entrant*> entrantList; 
   
   /** Vector of pointers to all Nodes objects read into the system. */
   std::vector<Node*> nodeList;
   
   /** Vector of pointers to all Course objects created. */
   std::vector<Course*> courseList;
   
   /** Pointer to Event object used to define the race event. */
   Event *event;
};

#endif	/* DATASTORE_H */

