/* 
 * File: track.c
 * Description: Creates new course track structures and populates them with
 * data supplied from file read-in by system.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "track.h"

/* 
 * Creates new instance of course track structure and populates with
 * data read-in from a file.
 */
int loadTracks() {

    /* Obtain track FILE pointer returned by openFile (fileIO.c). */
    FILE * track_file = openFile("Enter track file name:");

    /* Allocate memory for track linked-list data structure (fileIO.c). */
    initialise(&track_list);

    if (track_file != NULL) {

        int status = 0;

        /* Read file until EOF is reached. */
        while (!feof(track_file)) {

            /* Create new linked-list item. */
            linked_track = malloc(sizeof(linked_item));
            linked_track->next = NULL;
            
            /* Create new course track structure and allocate required memory. */ 
            course_track * new_track = malloc(sizeof(course_track));

            int start_node = 0, end_node = 0;

            status = fscanf(track_file, " %d%d%d%d", 
                    &new_track->number, 
                    &start_node, 
                    &end_node, 
                    &new_track->minutes);

            /* Locate course nodes that link to current track. */
            locateNodes(new_track, start_node, end_node);

            /* Set new linked list item data to new course track structure. */
            linked_track->data = new_track;

            /* Check entrant information was read in successfully from file 
             * (data not incomplete/corrupt)
             */
            if (status > 0) {

                /* Add new item to course linked list. */
                addToList(&linked_track, &track_list);

            } else {

                /* 
                 * If read data is incomplete/incorrupt, structures are invalid 
                 * and so free allocated memory. 
                 */
                free(linked_track);
                free(new_track);
            }
        }

         /* Once all lines have been read in, close the file. */
        fclose(track_file);
        return 1;

    } else {
        
        /* If an error has occurred, return flag indicating this. */
        return 0;
    }
}

/*
 * Search through course node linked list for nodes that
 * match the start/end nodes that are defined for the current track.
 * 
 * If a node is found, create pointer to that node. 
 */
void locateNodes(course_track * new_track, int start_node, int end_node) {

    linked_item * temp = node_list->head;

    while (temp != NULL) {

        course_node * temp_node = (course_node *) temp->data;

        /* Check if the current node matches the first node number. */
        if (start_node == temp_node->number) {

            new_track->start_node = temp->data;
        }

        /* Check if the current node matches the second node number. */
        if (end_node == temp_node->number) {

            new_track->end_node = temp->data;

        }
        
        temp = temp->next;
    }
}

/* 
 * Traverses through newly created course track linked-list
 * and prints out data for each track item.
 */
void printTracks() {

    linked_item * temp_item = track_list->head;

    while (temp_item != NULL) {

        course_track * temp_track = (course_track *) temp_item->data;

        printf("\nTrack No: %d, SN: %d, EN: %d, Min: %d", 
                temp_track->number, 
                temp_track->start_node->number,
                temp_track->end_node->number, 
                temp_track->minutes);

        temp_item = temp_item->next;

    }

}