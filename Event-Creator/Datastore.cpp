/* 
 * File:   Datastore.cpp
 * Author: connor
 * 
 * Created on March 5, 2013, 4:40 PM
 */

#include "Datastore.h"

Datastore::Datastore() {
    
    event = NULL;
}

Datastore::~Datastore() {
    delete event;
}

std::vector<Course*> Datastore::getCourseList(void){
    return courseList;
}

std::vector<Node*> Datastore::getNodeList(void) {
    return nodeList;
}

std::vector<Entrant*> Datastore::getEntrantList(void){
    return entrantList;
}

Event* Datastore::getEvent(void) const {
    return event;
}

void Datastore::addNewCourse (Course* newCourse) {
    
    courseList.push_back(newCourse);
    
}

void Datastore::addNewNode (Node* newNode) {
    
    nodeList.push_back(newNode);
    
}

void Datastore::addNewEntrant (Entrant* newEntrant) {
    
    entrantList.push_back(newEntrant);
    
}

void Datastore::setNewEvent(Event* newEvent) {
    
    this->event = newEvent;
    
}

Course* Datastore::getInCourse (char selectedID) {
    
    for (std::vector<Course*>::iterator it = courseList.begin(); it != courseList.end(); ++it) {

        if ((*it)->getCourseID() == selectedID) {

            return (*it);
        } 
        
      //  cout << (*it)->getCourseID();
    }

    return NULL;
}

Node* Datastore::obtainNode (int nodeNo) {
    
    for (std::vector<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {

        if ((*it)->getNodeNo() == nodeNo) {

            return (*it);
        }

    }
    
    return NULL;
}
