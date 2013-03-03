/* 
 * File: event.c
 * Description: Creates new event structures and populates them with
 * data supplied from a file read-in by system.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "fileIO.h"

/* 
 * Creates new instance of race event structure and populates with
 * data read-in from a file.
 */
int loadEventDes() {

    /* Allocate memory for event structure. */
    event = calloc(1, sizeof (event_description));

    /* Obtain course FILE pointer returned by openFile (fileIO.c). */
    FILE * event_file = openFile("Enter event description file name:");

    if (event_file != NULL) {
        
         /* Read file until EOF is reached. */
        while (!feof(event_file)) {

            fscanf(event_file, " %[A-Za-z -]s", event -> event_title);
            fscanf(event_file, " %[a-zA-Z0-9 ]s", event -> event_date);
            fscanf(event_file, " %[0-9:]s", event -> event_time);

        }

        /* Once all lines have been read in, close the file. */
        fclose(event_file);

    } else {
        
        /* If an error has occurred, free the memory
         * allocated for the event structure and
         * return flag indicating this. */
        free(event_file);
        return 0;
    }

    return 1;
}

/* 
 *  Prints the event information recently read in  to standard output.
 */
void printEventDes() {

    printf("\n%s\n%s\n%s\n ", event->event_title, event->event_date, event->event_time);

}