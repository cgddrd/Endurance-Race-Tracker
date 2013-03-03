/* 
 * File: course.h
 * Description: Defines the structure of an event course and defines functions used.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef COURSE_H
#define	COURSE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "node.h"
#include "linked_list.h"

    typedef struct course {
        
        char id; /* Character ID of particular course */
        int course_length; /* Denotes the total number of nodes used to make up the course */
        course_node ** course_nodes; /* Pointer to array of track node pointers */

    } event_course;

    /* Define linked-list structure for courses */
    linked_item * linked_course;
    list * course_list;

    int loadCourses();
    void compareCourseNodes(event_course ** temp_course, FILE ** course_file);
    void printCourses();


#ifdef	__cplusplus
}
#endif

#endif	/* COURSE_H */

