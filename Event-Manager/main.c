/* 
 * File: main.c
 * Description: Bootstrap loader for the application and provides 
 * interactive menu to allow user to interact with the program.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/* Bootstrap method for the application.*/
int main(int argc, char** argv) {

    loadFiles();
    displayMenu();

    return (EXIT_SUCCESS);
}

/* 
 * Generic function used to provide error checking for all
 * functions that require a user to input a file name.
 * 
 * Takes two function pointers as parameters to allow these
 * functions to be called again if user inputs an incorrect
 * file name.
 */
void checkFileLoad(int (*functionPtr)(), void (*printfunctionPtr)()) {

    /* 
     * If the current load function returns an "unsuccessful" flag,
     * (i.e. it cannot locate the file name inputted by the user)
     */
    while (functionPtr() == 0) {

        printf("\nFile could not be opened.\nWould you like to try again? (1 = Yes, 2 = No):\n");
        int option;

        scanf(" %d", &option);

        switch (option) {

            case 1:
                /* Run the same load function again. */
                functionPtr();
                break;
            case 2:
                /* Exit program cleanly. */
                printf("\nExiting program.");
                exit(0);
                break;
            default:
                printf("\nOption not available - Exiting program.");
                exit(0);
                break;
        }

    }

    /* If load is successful, run applicable print method.*/
    printfunctionPtr();
}

/*
 * Calls data input load functions in sequence to allow
 * program to become populated with data specified in data
 * files. 
 * 
 * Calls generic error checking function using individual load
 * functions as parameters.
 */
void loadFiles() {

    checkFileLoad(&loadEventDes, &printEventDes);

    checkFileLoad(&loadNodes, &printNodes);

    checkFileLoad(&loadTracks, &printTracks);

    checkFileLoad(&loadCourses, &printCourses);

    checkFileLoad(&loadEntrants, &getAllEntrantStatuses);

}

/* 
 * Provides interactive menu to allow user to interact with the
 * application and utilise its functions.
 */
void displayMenu() {

    int option = 0, status = 0;

    while (option != 9) {

        printf("\n*****************************************");
        printf("\nWelcome, please select an option:\n");
        printf("\n*****************************************");
        printf("\n  1. Display competitors yet to start");
        printf("\n  2. Display competitors out of courses");
        printf("\n  3. Display finished competitors");
        printf("\n  4. Enter competitor checkpoint time");
        printf("\n  5. Load time log file into system");
        printf("\n  6. Display event results list");
        printf("\n  7. Display specific competitor status");
        printf("\n  8. Display excluded competitors");
        printf("\n  9. Exit Program");
        printf("\n*****************************************\n");

        status = scanf(" %d", &option);

        if (status == 0) {
            exit(0);
        }

        switch (option) {

            case 1:
                checkNotStarted();
                break;
            case 2:
                checkStarted();
                break;
            case 3:
                checkFinished();
                break;
            case 4:
                /* Brackets are required as variables are being defined here. */
            {
                int entrant;
                printf("Enter required competitor number:\n");
                scanf(" %d", &entrant);
                userUpdateEntrant(entrant_list->head, entrant);
                break;
            }
            case 5:
                loadTimes();
                break;
            case 6:
                displayResultsList();
                break;
            case 7:
                getSpecificEntrantStatus();
                break;
            case 8:
                checkExcluded();
                break;
            case 9:
                printf("\nExiting program..\n");
                break;
            case 10:
                logActivity("This is test activity");
                break;
            default:
                printf("\nInput not valid. Please try again.\n");
                break;

        }

    }

}