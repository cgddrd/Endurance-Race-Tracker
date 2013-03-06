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
#include <ctime>
#include <sstream>
#include <algorithm>


using namespace std;

Process::Process(Datastore *newData) {

    data = newData;

}

Process::Process(const Process& orig) {
}

Process::~Process() {
    
    delete emp;
    delete data;
}

void Process::createEvent(void) {

    string inputName, inputDate, inputTime, convertedDate;

    cout << "Please enter an event name/description: ";
    getline(cin, inputName);

    cout << "Please enter the date of the event: (DD/MM/YYYY) ";
    getline(cin, inputDate);

    cout << "Please enter the time of the event: ";
    getline(cin, inputTime);

    convertedDate = convertDate(inputDate);

    Event *newEvent = new Event(inputName, convertedDate, inputTime);
    data->setNewEvent(newEvent);
}

void Process::addEntrant(void) {

    string entrantName;
    char courseID, input;
    int entrantNo;

    cout << "Please enter a name: ";
    getline(cin, entrantName);


    while (!((input == 'y') || (input == 'n') || (input == 'Y') || (input == 'N'))) {

        cout << "Do you wish to set a manual entrant no? (Y/N)";
        cin >> input;

        switch (input) {

            case 'Y':
            case 'y':
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter an entrant no: ";
                cin >> entrantNo;
                break;
            case 'N':
            case 'n':
                cout << "Setting automatic entrant number\n";
                entrantNo = (data->getEntrantList().size() + 1);
                break;
            default:
                cout << "Not a valid option. Please try again.\n";
                break;
        }
    }

    while (!isalpha(courseID)) {

        cout << "Please enter a course ID: ";
        cin >> courseID;

        if (!isalpha(courseID)) {

            cout << "ERROR: Course ID's can contain letters only. Please try again\n";

        }

    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Entrant *emp = new Entrant(entrantName, entrantNo, courseID);

    data->addNewEntrant(emp);

}

void Process::getAllNodes(void) {

    string fileName;

    cout << "Welcome. Please enter the file path for course nodes:\n";

    getline(cin, fileName);

    std::vector<std::vector<std::string > > temp = io.getFile(fileName);
    if (temp.size() <= 0) {

        cout << "ERROR: Nodes file (" << fileName << ") could not be located.\n\n"
                << "Please check the file path and try again. Exiting...\n";

        exit(EXIT_FAILURE);

    } else {

        for (std::vector<std::vector<std::string > >::iterator it = temp.begin(); it != temp.end(); ++it) {

            int value = atoi((*it).at(0).c_str());

            Node *tempNode = new Node(value, (*it).at(1));
            data->addNewNode(tempNode);
        }
        cout << "Course nodes loaded successfully.\n" << "Loading program...\n\n";
    }
}

void Process::createNewCourse(void) {

    char cid;

    while (!isalpha(cid)) {

        cout << "Please enter a new course ID: ";
        cin >> cid;

        if (!isalpha(cid)) {

            cout << "ERROR: Course ID's can contain letters only. Please try again\n";

        }

    }

    Course *newCourse = new Course(cid);
    data->addNewCourse(newCourse);
    cout << "Course (" << cid << ") created successfully.\n";
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
        cout << "\nNode (" << tempNode->getNodeNo() << ") added successfully.\n";

    } else {

        cout << "\nERROR: Node " << nodeNo << " not found.\n";

    }

}

Course* Process::getSelectedCourse(void) {

    char selectedID;

    cout << "Please enter ID of the course: \n";

    cin >> selectedID;

    data->getInCourse(selectedID);

}

string Process::convertDate(string &input) {

    string convertDate, result;

    convertDate.resize(input.size());
    std::remove_copy(input.begin(), input.end(), convertDate.begin(), '/');

    std::ostringstream date1;
    date1 << convertDate;

    struct tm tm;
    strptime(date1.str().c_str(), "%d%m%Y", &tm);

    char date2[30];
    strftime(date2, sizeof (date2), "%d %b %Y", &tm);

    result = string(date2);

    return result;

}