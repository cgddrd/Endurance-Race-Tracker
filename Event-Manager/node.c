/* 
 * File: node.c
 * Description: Creates new course node structures and populates them with
 * data supplied from file read-in by system.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "fileIO.h"

/* 
 * Creates new instance of course node structure and populates with
 * data read-in from a file.
 */
int loadNodes() {

    /* Obtain node FILE pointer returned by openFile (fileIO.c). */
    FILE * file_two = openFile("Enter node file name:");

    /* Allocate memory for course  node linked-list data structure (fileIO.c). */
    initialise(&node_list);

    int status = 0;

    /* Read file until EOF is reached. */
    if (file_two != NULL) {

        while (!feof(file_two)) {

            /* Create new linked-list item. */
            linked_node = malloc(sizeof (linked_item));
            linked_node->next = NULL;
            
            /* Create new course node structure and allocate required memory. */
            course_node * new_node = malloc(sizeof (course_node));

            status = fscanf(file_two, " %d %[a-zA-Z]s", 
                    &new_node->number, 
                    new_node->type);
            
            /* Set new linked list item data to new course node structure. */
            linked_node->data = new_node;

            
            /* Check course node information was read in successfully from file 
             * (data not incomplete/corrupt)
             */
            if (status > 0) {

                /* Add new item to course linked list. */
                addToList(&linked_node, &node_list);

            } else {
                
                /* 
                 * If read data is incomplete/incorrupt, structures are invalid 
                 * and so free allocated memory. 
                 */
                free(linked_node);
                free(new_node);
            }
        }

        /* Once all lines have been read in, close the file. */
        fclose(file_two);
        return 1;

    } else {
        
        /* If an error has occurred, return flag indicating this. */
        return 0;
    }
}

/* 
 * Traverses through newly created course node linked-list
 * and prints out data for each node item.
 */
void printNodes() {
    
    linked_item * temp = node_list->head;

    while (temp != NULL) {

        course_node * temp_node = (course_node *) temp->data;

        printf("\nNode: %d -> %s", temp_node->number, temp_node->type);

        temp = temp->next;

    }
}