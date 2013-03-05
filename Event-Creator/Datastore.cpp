/* 
 * File:   Datastore.cpp
 * Author: connor
 * 
 * Created on March 5, 2013, 4:40 PM
 */

#include "Datastore.h"

Datastore::Datastore() {
}

Datastore::~Datastore() {
}

std::vector<Course*> Datastore::getCourseList(){
    return courseList;
}

std::vector<Node*> Datastore::getNodeList(){
    return nodeList;
}

std::vector<Entrant*> Datastore::getEntrantList(){
    return entrantList;
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

