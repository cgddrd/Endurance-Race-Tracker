/* 
 * File: Process.cpp
 * Description: Provides all core functionality and data processing for the
 * application.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#include <vector>
#include <iostream>
#include <limits> 
#include <ctime>
#include <sstream>
#include <algorithm>
#include <string.h>
#include "Process.h"

using namespace std;

/**
 * Constructor for Process that allows access to the shared Datastore class
 * created in "main.cpp".
 * @param newData Pointer to the shared Datastore class created in the main method.
 */
Process::Process(Datastore *newData) {

    data = newData;

}

/**
 * Destructor to be used once object is removed.
 * Removes the objects stored on the heap.
 */
Process::~Process() {

    delete data;
}

/**
 * Prompts user for input to define an event before creating a new
 * 'Event' object and storing it's pointer in the shared Datastore class.
 */
void Process::createEvent(void) {

    string inputName, inputDate, inputTime, convertedDate;

    cout << "Please enter an event name/description: ";

    //Obtain all inputted characters including white space.
    getline(cin, inputName);

    cout << "Please enter the date of the event: (DD/MM/YYYY) ";
    getline(cin, inputDate);

    cout << "Please enter the time of the event: ";
    getline(cin, inputTime);

    //Convert inputted date string into format for writing to file.
    convertedDate = convertDate(inputDate);

    //Create a new Event object on the heap using the inputted information.
    Event *newEvent = new Event(inputName, convertedDate, inputTime);

    //Check if an Event object already exists on the heap.
    if (data->getEvent() != NULL) {

        //If it does remove it to prevent a memory leak.
        delete data->getEvent();

    }

    //Set a pointer to the new object in the shared Datastore class.
    data->setNewEvent(newEvent);

    cout << "\nEvent (" << inputName << ") created successfully.\n";
}

/**
 * Prompts user for input to define an entrant before creating a new
 * 'Entrant' object and adding it's pointer to the 
 * vector of Entrant pointers contained in the shared Datastore class.
 */
void Process::addEntrant(void) {

    string entrantName;
    char courseID, input;
    int entrantNo;

    cout << "Please enter a name: ";
    getline(cin, entrantName);

    //Prompt user to ask if they wish to specify their own entrant number.
    while (!((input == 'y') || (input == 'n') || (input == 'Y') || (input == 'N'))) {

        cout << "Do you wish to set a manual entrant no? (Y/N)";
        cin >> input;

        switch (input) {

            case 'Y':
            case 'y':
            {
                bool notExists = false;

                //Flush the input buffer to prevent input skipping.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (data->getEntrantList().size() > 0) {

                    while (!notExists) {

                        cout << "Please enter an entrant no: ";
                        cin >> entrantNo;

                        //Obtain a vector of ALL the entrants stored in Datastore node vector.
                        vector<Entrant*> allEntrants = data->getEntrantList();

                        //Loop through all the entrants. 
                        for (vector<Entrant*>::iterator it = allEntrants.begin(); it != allEntrants.end(); ++it) {

                            //Check to see if another entrant already has the entered value
                            if ((*it)->getEntrantNo() == entrantNo) {

                                //If so break out of the loop as there should not be ANY matches.
                                notExists = false;
                                cout << "\nERROR: This entrant already exists. Please enter another value.\n";
                                break;

                            } else {

                                //Otherwise if there is no match, then we can continue.
                                notExists = true;

                            }
                        }

                    }

                } else {

                    cout << "Please enter an entrant no: ";
                    cin >> entrantNo;

                }

                break;

            }
            case 'N':
            case 'n':

                cout << "Setting automatic entrant number\n";

                //Set entrant number to total numbeer of entrants + 1 (increment).
                entrantNo = (data->getEntrantList().size() + 1);
                break;
            default:
                cout << "Not a valid option. Please try again.\n";
                break;
        }
    }

    //Perform error checking to confirm entered course ID is a letter.
    while (!isalpha(courseID)) {

        cout << "Please enter a course ID: ";
        cin >> courseID;

        //If the user has not entered a letter, they must enter another value.
        if (!isalpha(courseID)) {

            cout << "ERROR: Course ID's can contain letters only. Please try again\n";

        }

    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //Create a new Entrant object on the heap using the inputted information.
    Entrant *emp = new Entrant(entrantName, entrantNo, courseID);

    //Add a pointer to the new object in the entrant vector stored in Datastore.
    data->addNewEntrant(emp);

    cout << "\nEntrant(" << entrantNo << ") created successfully.\n";

}

/**
 * Prompts user for the file path to the file that contains all the course
 * node information, before processing and storing these nodes in a vector
 * contained in the shared Datastore class.
 */
void Process::getAllNodes(void) {

    string fileName;

    //Obtain the file path from the user.
    cout << "Welcome. Please enter the file path for course nodes:\n";
    getline(cin, fileName);

    //Read-in all the node data from the file and store it all in a vector.
    vector<vector<string > > fileContents = io.getFile(fileName);

    //Check if the data has been successfully parsed and read-in.
    if (fileContents.size() <= 0) {

        cout << "ERROR: Nodes file (" << fileName << ") could not be located.\n\n"
                << "Please check the file path and try again. Exiting...\n";

        //If the node data could not be loaded, terminate the program.
        exit(EXIT_FAILURE);

    } else {

        //Loop through every line read-in from the file.
        for (vector<vector<string > >::iterator it = fileContents.begin(); it != fileContents.end(); ++it) {

            //Convert the first value on the line (node number) to an int.
            int value = atoi((*it).at(0).c_str());

            //Create a new Node object on the heap using the inputted information.
            Node *tempNode = new Node(value, (*it).at(1));

            //Add a pointer to the new object in the node vector stored in Datastore
            data->addNewNode(tempNode);
        }
        cout << "Course nodes loaded successfully.\n" << "Loading program...\n\n";
    }

}

/**
 * Prompts user for input to define a course before creating a new
 * 'Course' object and adding it's pointer to the 
 * vector of Course pointers contained in the shared Datastore class.
 */
void Process::createNewCourse(void) {

    char cid;
    bool notExists = false;

    if (data->getCourseList().size() > 0) {

        while (!notExists) {

            cid = 0;
            
            //Check that the ID inputted by the user is a letter.
            while (!isalpha(cid)) {

                //Prompt user for a course ID.
                cout << "Please enter a new course ID: ";
                cin >> cid;

                if (!isalpha(cid)) {

                    cout << "ERROR: Course ID's can contain letters only. Please try again\n";

                }

            }

            //Obtain a vector of ALL the courses stored in Datastore node vector.
            vector<Course*> allCourses = data->getCourseList();

            //Loop through all the stored courses. 
            for (vector<Course*>::iterator it = allCourses.begin(); it != allCourses.end(); ++it) {

                //Check to see if another course already has the entered value.
                if ((*it)->getCourseID() == cid) {

                    notExists = false;

                    //If so break out of the loop as there should not be ANY matches.
                    cout << "\nERROR: This course already exists. Please enter another value.\n";
                    break;

                } else {

                    //Otherwise if there is no match, then we can continue.
                    notExists = true;

                }
            }
        }

    } else {

        //Check that the ID inputted by the user is a letter.
        while (!isalpha(cid)) {

            //Prompt user for a course ID.
            cout << "Please enter a new course ID: ";
            cin >> cid;

            if (!isalpha(cid)) {

                cout << "ERROR: Course ID's can contain letters only. Please try again\n";

            }

        }
    }

    //Create a new Course object on the heap using the inputted information.
    Course *newCourse = new Course(cid);

    //Add a pointer to the new object in the course vector stored in Datastore.
    data->addNewCourse(newCourse);

    cout << "\nCourse (" << cid << ") created successfully.\n";
}

/**
 * Allows a user to specify a new node (loaded in from "nodes.txt") that
 * that will form part of a particular course.
 * @param currentCourse The course that a user wishes to add a new node to.
 */
void Process::addCourseNode(Course *currentCourse) {

    int nodeNo;

    cout << "Please select a node to add: \n";

    //Obtain a vector of ALL the course nodes stored in Datastore node vector.
    vector<Node*> allNodes = data->getNodeList();

    //Print all the nodes to screen to provide user with a list to select from.
    for (vector<Node*>::iterator it = allNodes.begin(); it != allNodes.end(); ++it) {
        cout << (*it)->getNodeNo() << " (" << (*it)->getNodeType() << "), ";
    }

    cout << endl;

    //Prompt user for the number of the node they wish to add.
    cin >> nodeNo;

    //Attempt to fetch the specified node from the vector of nodes in Datastore.
    Node *tempNode = data->obtainNode(nodeNo);

    //Check to see if a matching node was located.
    if (tempNode != NULL) {

        /**
         * Add a pointer to the located node object in the course's vector
         * of nodes.
         */
        currentCourse->addCourseNode(tempNode);
        cout << "\nNode (" << tempNode->getNodeNo() << ") added successfully.\n";


        //Obtain the vector of all nodes contained within the course.
        vector<Node*> currentCourseNodes = currentCourse->getCourseNodes();

        //Display a list of all the nodes that make up the course on screen.
        cout << "\nCurrent nodes contained in Course (" << currentCourse->getCourseID() << "):\n";

        for (vector<Node*>::iterator it = currentCourseNodes.begin(); it != currentCourseNodes.end(); ++it) {
            cout << (*it)->getNodeNo() << " (" << (*it)->getNodeType() << ")\n";
        }

    } else {

        //Otherwise if no matching node can be found, inform the user.
        cout << "\nERROR: Node " << nodeNo << " not found.\n";

    }

}

/**
 * Attempts to locate a course from Datastore that matches 
 * the ID entered by the user.
 * @returns The pointer to a matching course or NULL.
 */
Course* Process::getSelectedCourse(void) {

    char selectedID;

    //Check that the ID inputted by the user is a letter.
    while (!isalpha(selectedID)) {

        //Prompt user for a course ID.
        cout << "Please enter an existing course ID: ";
        cin >> selectedID;

        if (!isalpha(selectedID)) {

            cout << "ERROR: Course ID's can contain letters only. Please try again\n";

        }

    }

    //Return the matching course fetched from the course vector in Datastore.
    return data->getInCourse(selectedID);

}

/**
 * Converts an inputted date string from "DD/MM/YYYY" to correct format
 * "%d %b %Y" (e.g. 05 July 1993) required to write event details to file.
 * @param input The original inputted event date in format "DD/MM/YYYY".
 * @returns A string containing the same date in a modified format.
 */
string Process::convertDate(string &input) {

    string convertDate, result;

    //Resize the conversion string to the same sized as the original.
    convertDate.resize(input.size());

    //Remove any '/' characters from the original string and pass to new string.
    remove_copy(input.begin(), input.end(), convertDate.begin(), '/');

    //Create new string stream and input modified date string into it.
    ostringstream date1;
    date1 << convertDate;

    //Create new time structure used to process date conversion.
    struct tm tm;
    strptime(date1.str().c_str(), "%d%m%Y", &tm);

    char date2[30];

    //Re-format the date into the correct format.
    strftime(date2, sizeof (date2), "%d %b %Y", &tm);

    //Set a resulting string to the output of the re-arranged time struct.
    result = string(date2);

    //Return the re-formatted date string.
    return result;

}