/* 
 * File: Datastore.cpp
 * Description: Contains and stores all the persistent data used
 * by the application to allow data to be accessed by multiple classes.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#include "Datastore.h"

/**
 * Default constructor for Datastore.
 * Sets the initial value of the 'event' pointer to NULL for
 * error checking purposes.
 */
Datastore::Datastore() {
    
    event = NULL;
}

/**
 * Destructor to be used once object is removed.
 */
Datastore::~Datastore() {
    delete event;
}

/**
 * Fetches the vector of all the courses created for an event.
 * @return A vector that contains pointers to all the Course objects created.
 */
std::vector<Course*> Datastore::getCourseList(void){
    return courseList;
}

/**
 * Fetches the vector of all the nodes read in from "nodes.txt".
 * @return A vector that contains pointers to all the Node objects.
 */
std::vector<Node*> Datastore::getNodeList(void) {
    return nodeList;
}

/**
 * Fetches the vector of all the entrants created for an event.
 * @return A vector that contains pointers to all the Entrant objects created.
 */
std::vector<Entrant*> Datastore::getEntrantList(void){
    return entrantList;
}

/**
 * Fetches the Event object created to define the race event.
 * @return A a pointer to the created Event object.
 */
Event* Datastore::getEvent(void) const {
    return event;
}

/**
 * Adds a new Course object to the end of the 'courseList' vector.
 * @param newCourse Pointer to the new Course object to be added to the vector.
 */
void Datastore::addNewCourse (Course *newCourse) {
    
    courseList.push_back(newCourse);
    
}

/**
 * Adds a new Node object to the end of the 'nodeList' vector.
 * @param newNode Pointer to the new Node object to be added to the vector.
 */
void Datastore::addNewNode (Node  *newNode) {
    
    nodeList.push_back(newNode);
    
}

/**
 * Adds a new Entrant object to the end of the 'courseEntrant' vector.
 * @param newEntrant Pointer to the new Entrant object to be added to the vector.
 */
void Datastore::addNewEntrant (Entrant *newEntrant) {
    
    entrantList.push_back(newEntrant);
    
}

/**
 * Sets the 'event' pointer to a newly created Event object.
 * @param newEvent A pointer to the new Event object created.
 */
void Datastore::setNewEvent(Event *newEvent) {
    
    this->event = newEvent;
    
}

/**
 * Determines if a course with the inputted ID exists in the vector of
 * courses ('courseList') and if so returns the pointer to that Course object.
 * @param selectedID The course ID inputted by the user.
 * @return Either the located course or NULL.
 */
Course* Datastore::getInCourse (char selectedID) {
    
    //Loop through the entire vector of courses.
    for (std::vector<Course*>::iterator it = courseList.begin(); it != courseList.end(); ++it) {

        //If the ID of the current course matches the inputted ID...
        if ((*it)->getCourseID() == selectedID) {
            
            //... return the pointer to that Course object.
            return (*it);
        } 
    }

    //Otherwise if no matches are found, return NULL.
    return NULL;
}

/**
 * Determines if a node with the inputted number exists in the vector of
 * nodes ('nodeList') and if so returns the pointer to that Node object.
 * @param nodeNo The node number inputted by the user.
 * @return Either a pointer to the located Node object or NULL.
 */
Node* Datastore::obtainNode (int nodeNo) {
    
    //Loop through the entire vector of courses.
    for (std::vector<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {

        //If the number of the current node matches the inputted number...
        if ((*it)->getNodeNo() == nodeNo) {

            //... return the pointer to that Node object.
            return (*it);
        }

    }
    
    //Otherwise if no matches are found, return NULL.
    return NULL;
}