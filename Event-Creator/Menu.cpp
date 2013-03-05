/* 
 * File:   Menu.cpp
 * Author: connor
 * 
 * Created on March 5, 2013, 4:41 PM
 */

#include <vector>
#include <iostream>
#include <limits> 
#include "Menu.h"

using namespace std;

Menu::Menu(Datastore *newData, Process *newProc) {

    data = newData;
    proc = newProc;

}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

void Menu::showMainMenu() {

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
                io.writeEntrants(data->getEntrantList());
                io.writeCourses(data->getCourseList());
                break;
                
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}

void Menu::showCourseEditor() {

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

                while (newCourse == NULL) {

                    newCourse = proc->getSelectedCourse();

                }

                proc->addCourseNode(newCourse);

                std::vector<Node*> tester = newCourse->getCourseNodes();

                cout << "COURSE NODES:\n";

                for (std::vector<Node*>::iterator it = tester.begin(); it != tester.end(); ++it) {
                    cout << (*it)->getNodeNo() << " (" << (*it)->getNodeType() << ")\n";
                }

                break;
            }
            case 3:
                cout << "Exporting all courses to file.\n";
                io.writeCourses(data->getCourseList());
                break;
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}

void Menu::showEntrantEditor() {

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

                io.writeEntrants(data->getEntrantList());
                break;

            case 3:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}

void Menu::showEventEditor() {

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
                proc->createEvent();
                break;

            case 2:

                io.writeEntrants(data->getEntrantList());
                break;

            case 3:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Incorrect option. Please try again.\n";
        }
    }
}