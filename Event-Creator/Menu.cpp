/* 
 * File:   Menu.cpp
 * Author: connor
 * 
 * Created on March 5, 2013, 4:41 PM
 */

#include <vector>
#include <iostream>
#include <limits> 
#include <string.h>
#include "Menu.h"

using namespace std;

Menu::Menu(Datastore *newData, Process *newProc) {

    data = newData;
    proc = newProc;

}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {

    delete data;
    delete proc;
}

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

                cout << "Writing all data to files...\n";

                if (data->getEvent() == NULL) {

                    cout << "ERROR: No event created. Nothing to export.\n";

                } else if (data->getEntrantList().size() <= 0) {

                        cout << "ERROR: No entrants created. Nothing to export.\n";
                        
                } else if (data->getCourseList().size() <= 0) {
                    
                    cout << "ERROR: No courses created. Nothing to export.\n";

                } else {
                    io.writeEvent(data->getEvent());
                    io.writeEntrants(data->getEntrantList());
                    io.writeCourses(data->getCourseList());
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

                newCourse = proc->getSelectedCourse();

                if (newCourse == NULL) {

                    cout << "ERROR: Course does not exist. Please try again";

                } else {

                    proc->addCourseNode(newCourse);

                    std::vector<Node*> tester = newCourse->getCourseNodes();

                    cout << "\nCurrent nodes contained in Course (" << newCourse->getCourseID() << "):\n";

                    for (std::vector<Node*>::iterator it = tester.begin(); it != tester.end(); ++it) {
                        cout << (*it)->getNodeNo() << " (" << (*it)->getNodeType() << ")\n";
                    }

                }

                break;
            }
            case 3:
                
                cout << "Exporting all courses to file.\n";
                if (data->getCourseList().size() > 0) {
                   io.writeCourses(data->getCourseList());
                } else {
                   cout << "\nERROR: No courses created. Nothing to export.\n"; 
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

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                proc->addEntrant();
                break;

            case 2:

                cout << "Exporting all entrants to file.\n";
                if (data->getEntrantList().size() > 0) {
                   io.writeEntrants(data->getEntrantList());
                } else {
                   cout << "\nERROR: No entrants created. Nothing to export.\n"; 
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

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                checkExistingEvent();
                break;

            case 2:
                
                cout << "Exporting event to file.\n";
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

void Menu::checkExistingEvent(void) {

    char input;

    if (data->getEvent() != NULL) {

        while (!((input == 'y') || (input == 'n') || (input == 'Y') || (input == 'N'))) {

            cout << "WARNING: An event has already been created.\n";
            cout << "Do you wish to create a new event? (Y/N)\n";
            cin >> input;

            switch (input) {

                case 'Y':
                case 'y':
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    proc->createEvent();
                    break;
                case 'N':
                case 'n':
                    break;
                default:
                    cout << "Not a valid option. Please try again.\n";
                    break;
            }
        }
    } else {
        proc->createEvent();
    }
}