/* 
 * File:   Process.cpp
 * Author: connor
 * 
 * Created on March 4, 2013, 3:25 PM
 */

#include "Process.h"
#include "FileIO.h"
#include <vector>
#include <iostream>
#include <limits> 

using namespace std;

FileIO io;

Process::Process() {


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

    int enno = (entrantList.size() + 1);

    Entrant *emp = new Entrant(test, enno, cid);

    entrantList.push_back(emp);

}

void Process::getAllNodes() {

    std::vector<std::vector<std::string > > temp = io.getFile();

    for (std::vector<std::vector<std::string > >::iterator it = temp.begin(); it != temp.end(); ++it) {

        cout << (*it).at(0) << "\n";
        cout << (*it).at(1) << "\n";

        int value = atoi((*it).at(0).c_str());

        Node *tempNode = new Node(value, (*it).at(1));

        this->nodeList.push_back(tempNode);

        //it is now a pointer to a vector<int>
        //  for (std::vector<std::string>::iterator jt = it->begin(); jt != it->end(); ++jt) {
        // jt is now a pointer to an integer.
        //       cout << (*jt).at(0) << "\n";
        //   }
    }

    for (std::vector<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
        (*it)->print();
    }


}

void Process::showCourseEditor() {


    int x;

    while (x != 9) {

        cout << "\n*************************************\n"
                << "Course Editor | Please make a choice:\n"
                << "-------------------------------------\n"
                << "1. Create a new course.\n"
                << "2. Add a new node to existing course.\n"
                << "3. Export courses to file.\n"
                << "4. Return to main menu.\n"
                << "*************************************\n";

        cin >> x;

        switch (x) {

            case 1:

                createNewCourse();

                break;

            case 2:
            {
                Course *newCourse = NULL;

                while (newCourse == NULL) {

                    newCourse = getSelectedCourse();

                }

                addCourseNode(newCourse);

                std::vector<Node*> tester = newCourse->getCourseNodes();

                cout << "COURSE NODES:\n";

                for (std::vector<Node*>::iterator it = tester.begin(); it != tester.end(); ++it) {
                    cout << (*it)->getNodeNo() << " (" << (*it)->getNodeType() << ")\n";
                }

                break;
            }
            case 3:
                cout << "Exporting all courses to file.\n";
                io.writeCourses(this->courseList);
                break;
            case 9:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}


void Process::createNewCourse() {

    char cid;

    cout << "Please enter a new course ID: ";
    cin >> cid;

    Course *newCourse = new Course(cid);

    courseList.push_back(newCourse);


}

void Process::addCourseNode(Course *currentCourse) {

    int nodeNo;

    cout << "Please select a node to add: \n";

    for (std::vector<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
        cout << (*it)->getNodeNo() << " (" << (*it)->getNodeType() << "), ";
    }

    cout << endl;

    cin >> nodeNo;

    for (std::vector<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {

        if ((*it)->getNodeNo() == nodeNo) {

            currentCourse->addCourseNode((*it));
            cout << "NODE ADDED\n";
            return;
        }

    }

    cout << "NODE NOT FOUND\n";

}

const vector<Entrant*> Process::getEntrantList() const {
    return entrantList;
}

const vector<Node*> Process::getNodeList() const {
    return nodeList;
}

Course* Process::getSelectedCourse() {

    char selectedID;

    cout << "Please enter ID of the course: \n";

    cin >> selectedID;

    for (std::vector<Course*>::iterator it = courseList.begin(); it != courseList.end(); ++it) {

        if ((*it)->getCourseID() == selectedID) {

            return (*it);
        }
    }

    return NULL;

}

