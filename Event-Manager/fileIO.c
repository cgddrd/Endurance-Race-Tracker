/* 
 * File: fileIO.c
 * Description: Contains modular functions used to read in files
 * specified by the user and to allocate memory for linked-list
 * structures. 
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

/* Instruct compiler to use POSIX extensions for file locking.*/
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/file.h> 
#include "fileIO.h"

/* 
 * Allocates memory blocks for linked-list data structures
 * passed as parameters and sets default values.
 */
void initialise(list ** data_list) {

    (*data_list) = malloc(sizeof (list));

    (*data_list)->head = NULL;
    (*data_list)->tail = NULL;

}

/* 
 * Appends a new linked-list item to the end 
 * of a linked-list specified as parameters.
 */
void addToList(linked_item ** new_item, list ** data_list) {

    /* Check if linked list is currently empty */
    if ((*data_list)->head == NULL) {

        /* 
         * If so add the new item and point the
         * linked-list head and tail to it.
         * (As there is only one item in the list)
         */
        (*data_list)->head = (*new_item);
        (*data_list)->tail = (*new_item);

    } else {

        /* Otherwise locate the last item in the linked-list*/
        linked_item * temp = (*data_list)->tail;

        /* 
         * Set the 'next' pointer of that original last
         * item to the new item being added, and set the 
         * 'tail' pointer to the new item.
         */
        temp->next = (*new_item);
        (*data_list)->tail = (*new_item);
    }
}

/* 
 * Returns a FILE pointer that points to a file specified
 * by a user via an input prompt.
 */
FILE * openFile(char *prompt) {

    char file_name[101];

    printf("\n%s ", prompt);
    scanf(" %100[a-zA-Z0-9._/]", file_name);

    FILE * file = fopen(file_name, "r");

    return file;

}

/* 
 * Appends a specified message to a specified file incorporating
 * file locking to prevent corruption of file data.
 */
void writeFile(char *file_name, char *message) {

    /* Create new file stream (append). */
    FILE * file = fopen(file_name, "a+");

    /* Attempt to lock the file. */
    flock(fileno(file), LOCK_EX); 

    /* Write the message to the file. */
    fprintf(file, "%s", message); 
    
    /* Close the output stream to the file. */
    fclose(file); /*done!*/

    /* Release lock from the file. */
    flock(fileno(file), LOCK_UN);
    
}

/* 
 * Appends a new system activity log message to the 
 * end of the "log.txt" file.
 */
void logActivity(char *activity) {

    char message[2000];
    time_t rawtime;
    struct tm * timeinfo;

    /* Obtain the current system time. */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    message[0] = '\0';

    /* Create the log message. */
    strcat(message, "LOG - EM: ");
    strcat(message, activity);
    strcat(message, " - ");
    strcat(message, asctime(timeinfo));

    /* Write the log message to the log file (log.txt). */
    writeFile("../files/log.txt", message);

}
