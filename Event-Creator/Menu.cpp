/* 
 * File: Menu.cpp
 * Description: Generates system menus to provide a means of interacting with
 * the application.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */


#include <vector>
#include <iostream>
#include <limits> 
#include <string.h>
#include "Menu.h"

using namespace std;

/**
 * Constructor for Menu that allows access to Process and Datastore classes
 * created in "main.cpp". This allows Menu to access the same data stored in 
 * Datastore as the Process class.
 * @param newData Pointer to the shared Datastore class created in the main method.
 * @param newProc Pointer to the shared Process class created in the main method.
 */
Menu::Menu(Datastore *newData, Process *newProc) {

    data = newData;
    proc = newProc;

}

/**
 * Destructor to be used once object is removed.
 * Removes the objects stored on the heap.
 */
Menu::~Menu() {

    delete data;
    delete proc;
}

/**
 * Provides top-level interactive menu to allow user to interact with the
 * application and utilise its functions.
 */
void Menu::showMainMenu(void) {

    int x;

    while (x != 5) {

        cout << "\n*************************************\n"
                << "Welcome to the Event Creator.\n"
                << "Please select an option:\n"
                << "-------------------------------------\n"
                << "1. Event Editor\n"
                << "2. Entrant Editor\n"
                << "3. Course Editor\n"
                << "4. Export ALL files.\n"
                << "5. Exit Program.\n"
                << "*************************************\n";

        cin >> x;

        switch (x) {

            case 1:

                showEventEditor();
                break;

            case 2:

                showEntrantEditor();
                break;

            case 3:

                showCourseEditor();
                break;

            case 4:

                /**
                 * Export all data to their files.
                 * As this method writes ALL the data, it has to check
                 * that at least one instance of each object (Entrant, Event
                 * and Course) exists before being able to write them all to file.
                 */

                cout << "Writing all data to files...\n";

                //Check if an event has been created.
                if (data->getEvent() == NULL) {

                    cout << "ERROR: No event created. Event has to be created first.\n";

                    //Check if any entrants have been created.
                } else if (data->getEntrantList().size() <= 0) {

                    cout << "ERROR: No entrants created. Nothing to export.\n";

                    //Check if any courses have been created.
                } else if (data->getCourseList().size() <= 0) {

                    cout << "ERROR: No courses created. Nothing to export.\n";

                } else {

                    //If there are no problems, write all the data to file.
                    io.writeEvent(data->getEvent());
                    io.writeEntrants(data->getEntrantList(), data->getEvent());
                    io.writeCourses(data->getCourseList(), data->getEvent());
                }

                break;

            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}

/**
 * Provides sub-level interactive menu to allow user to create new
 * courses and write them to file.
 */
void Menu::showCourseEditor(void) {

    int x;

    while (x != 4) {

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

                proc->createNewCourse();

                break;

            case 2:
            {
                Course *newCourse = NULL;

                //Prompt user for the ID of the course they wish to edit.
                newCourse = proc->getSelectedCourse();

                //If the specified course does not exist..
                if (newCourse == NULL) {

                    //.. inform the user.
                    cout << "ERROR: Course does not exist. Please try again";

                //Otherwise if the course does exist..
                } else {

                    //Prompt the user for the node they wish to add and add it. 
                    proc->addCourseNode(newCourse);

                }

                break;
            }
            case 3:

                cout << "Exporting all courses to file.\n";
                
                //Check if any courses have been created. 
                if (data->getCourseList().size() > 0 && data->getEvent() != NULL) {
                    io.writeCourses(data->getCourseList(), data->getEvent());
                } else {
                    cout << "\nERROR: No courses, or event not created.\n";
                }

                break;
                
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}

/**
 * Provides sub-level interactive menu to allow user to create new
 * entrants and write them to file.
 */
void Menu::showEntrantEditor(void) {

    int x;

    while (x != 3) {

        cout << "\n*************************************\n"
                << "Entrant Editor | Please make a choice:\n"
                << "-------------------------------------\n"
                << "1. Create a new entrant.\n"
                << "2. Export entrants to file.\n"
                << "3. Return to main menu.\n"
                << "*************************************\n";

        cin >> x;

        switch (x) {

            case 1:
                
                //Flush the input buffer to prevent skipping on "getline()".
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                //Run method to add a new entrant.
                proc->addEntrant();
                break;

            case 2:

                cout << "Exporting all entrants to file.\n";
                
                //Check is any entrants have been created.
                if (data->getEntrantList().size() > 0 && data->getEvent() != NULL) {
                    io.writeEntrants(data->getEntrantList(), data->getEvent());
                } else {
                    cout << "\nERROR: No entrants, or event not created.\n";
                }

                break;

            case 3:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}

/**
 * Provides sub-level interactive menu to allow user to create a new
 * event and write it's details to file.
 */
void Menu::showEventEditor(void) {

    int x;

    while (x != 3) {

        cout << "\n*************************************\n"
                << "Event Editor | Please make a choice:\n"
                << "-------------------------------------\n"
                << "1. Create new event.\n"
                << "2. Write event to file.\n"
                << "3. Return to main menu.\n"
                << "*************************************\n";

        cin >> x;

        switch (x) {

            case 1:

                //Flush the input buffer to prevent skipping on "getline()".
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                //Perform check to see if an event has already been created.
                checkExistingEvent();
                break;

            case 2:

                cout << "Exporting event to file.\n";
                
                //Check to see if an event had been created.
                if (data->getEvent() != NULL) {
                    io.writeEvent(data->getEvent());
                } else {
                    cout << "\nERROR: No event created. Nothing to export.\n";
                }

                break;

            case 3:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}

/**
 * Checks to see if an existing event has already been created in this session,
 * and provides suitable prompting and error checking as required.
 */
void Menu::checkExistingEvent(void) {

    char input;

    //Check to see if the 'event' pointer in Datastore has been set to an Event object.
    if (data->getEvent() != NULL) {

        //If an event has already been created, prompt user for confirmation.
        while (!((input == 'y') || (input == 'n') || (input == 'Y') || (input == 'N'))) {

            cout << "WARNING: An event has already been created.\n";
            cout << "Do you wish to create a new event? (Y/N)\n";
            cin >> input;

            switch (input) {

                case 'Y':
                case 'y':
                    
                    //Flush the input buffer to prevent skipping on "getline()".
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    //Prompt user for event information and create the new event.
                    proc->createEvent();
                    break;
                
                //If the answer is no, nothing needs to happen. 
                //Case is left in to prevent system thinking 'n/N' keys are incorrect.
                case 'N':
                case 'n':
                    break;
                default:
                    cout << "Not a valid option. Please try again.\n";
                    break;
            }
        }
    } else {
        
        //Otherwise if no event has been created as of yet, create a new one.
        proc->createEvent();
    }
}