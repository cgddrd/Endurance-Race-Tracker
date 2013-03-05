/* 
 * File:   Process.cpp
 * Author: connor
 * 
 * Created on March 4, 2013, 3:25 PM
 */

#include "Process.h"
#include <vector>
#include <iostream>
#include <limits> 

using namespace std;

Process::Process(Datastore *newData) {

    data = newData;

}

Process::Process(const Process& orig) {
}

Process::~Process() {
}

void Process::addEntrant() {

    string test;
    char cid;

    cout << "Please enter a name: ";

    getline(cin, test);

    // cout << "Please enter an entrant no: ";
    //   cin >> enno; 

    cout << "Please enter an course ID: ";
    cin >> cid;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int enno = (data->getEntrantList().size() + 1);

    Entrant *emp = new Entrant(test, enno, cid);

    data->addNewEntrant(emp);

}

void Process::getAllNodes() {

    std::vector<std::vector<std::string > > temp = io.getFile();

    for (std::vector<std::vector<std::string > >::iterator it = temp.begin(); it != temp.end(); ++it) {

        cout << (*it).at(0) << "\n";
        cout << (*it).at(1) << "\n";

        int value = atoi((*it).at(0).c_str());

        Node *tempNode = new Node(value, (*it).at(1));

    //    data->getNodeList().push_back(tempNode);
        
        data->addNewNode(tempNode);

        //it is now a pointer to a vector<int>
        //  for (std::vector<std::string>::iterator jt = it->begin(); jt != it->end(); ++jt) {
        // jt is now a pointer to an integer.
        //       cout << (*jt).at(0) << "\n";
        //   }
    }

    for (std::vector<Node*>::iterator it = data->getNodeList().begin(); it != data->getNodeList().end(); ++it) {
        (*it)->print();
    }


}




void Process::createNewCourse() {

    char cid;

    cout << "Please enter a new course ID: ";
    cin >> cid;

    Course *newCourse = new Course(cid);

    data->addNewCourse(newCourse);
    
    cout << "SIZE: " << data->getCourseList().size() << endl;


}

void Process::addCourseNode(Course *currentCourse) {

    int nodeNo;

    cout << "Please select a node to add: \n";
    
    std::vector<Node*> allNodes = data->getNodeList();

    for (std::vector<Node*>::iterator it = allNodes.begin(); it != allNodes.end(); ++it) {
        cout << (*it)->getNodeNo() << " (" << (*it)->getNodeType() << "), ";
    }

    cout << endl;

    cin >> nodeNo;

    Node *tempNode = data->obtainNode(nodeNo);
    
    if (tempNode != NULL) {
        
       currentCourse->addCourseNode(tempNode);  
       cout << "Node " << tempNode->getNodeNo() << " added successfully.\n";
       
    } else {
        
       cout << "ERROR: Node " << nodeNo << " not found.\n";
       
    }

}

Course* Process::getSelectedCourse() {

    char selectedID;

    cout << "Please enter ID of the course: \n";

    cin >> selectedID;

    data->getInCourse(selectedID);

}

