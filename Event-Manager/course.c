/* 
 * File: course.c
 * Description: Creates new course structures and populates them with
 * data supplied from file read-in by system.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "course.h"

/* Creates new instance of course structure and populates with
 * data read-in from a file.
 */
int loadCourses() {

    /* Obtain course FILE pointer returned by openFile (fileIO.c). */
    FILE * course_file = openFile("Enter courses file name:");

    /* Allocate memory for course linked-list data structure (fileIO.c). */
    initialise(&course_list);

    if (course_file != NULL) {

        int status = 0;

        /* Read file until EOF is reached. */
        while (!feof(course_file)) {

            /* Create new linked-list item. */
            linked_course = malloc(sizeof (linked_item));
            linked_course->next = NULL;

            /* Create new course structure and allocated required memory. */
            event_course * new_course = malloc(sizeof (event_course));

            status = fscanf(course_file, " %c%d", 
                    &new_course->id, 
                    &new_course->course_length);

            /* 
             * Allocate memory for course node array to size of total nodes
             * value obtained from file.
             */
            new_course->course_nodes = calloc(1, 
                    new_course->course_length * sizeof (course_node));
            
            /* Determine node pointers to be added to array. */
            compareCourseNodes(&new_course, &course_file);

            linked_course->data = new_course;

            /* Check course information was read in successfully from file 
             * (data not incomplete/corrupt)
             */
            if (status > 0) {

                /* Add new item to course linked list. */
                addToList(&linked_course, &course_list);
                
            } else {
                
                /* 
                 * If read data is incomplete/incorrupt, structures are invalid 
                 * and so free allocated memory. 
                 */
                free(linked_course);
                free(new_course);
            }
        }

        /* Once all lines have been read in, close the file. */
        fclose(course_file);
        return 1;

    } else {
        
        /* If an error has occurred, return flag indicating this. */
        return 0;
    }
}

/* Reads in specified node sequence for course from file and 
 * adds pointers to matching node structures in course array. */
void compareCourseNodes(event_course ** temp_course, FILE ** course_file) {

    int i, current_node;

    for (i = 0; i < (*temp_course)->course_length; i++) {

        /* Get next node in node sequence list located in input file*/
        fscanf((*course_file), " %d", &current_node);

        /* Search for specified node ID in course node linked list.
         * If node is located, set current 
         * element in new course node array to point to this node.
         */
        linked_item * temp_item = node_list->head;

        while (temp_item != NULL) {

            course_node * temp_node = (course_node *) temp_item->data;

            if (current_node == temp_node->number) {

                (*temp_course)->course_nodes[i] = temp_node;

            }

            temp_item = temp_item->next;
        }
    }
}

/* Prints to standard output full list of event courses.
 * (Used to verify all courses in file have been successfully processed)
 */
void printCourses() {

    linked_item * temp = course_list->head;

    while (temp != NULL) {

        event_course * temp_event = (event_course *) temp->data;

        printf("\nCourse ID: %c, Length: %d", 
                temp_event->id, 
                temp_event->course_length);
        
        printf("\nNodes in course:");

        int i;
        for (i = 0; i < temp_event->course_length; i++) {

            printf("\nNode %d: No: %d, ID: %s", i, 
                    temp_event->course_nodes[i]->number, 
                    temp_event->course_nodes[i]->type);
        }

        printf("\n\n");

        temp = temp->next;

    }

}