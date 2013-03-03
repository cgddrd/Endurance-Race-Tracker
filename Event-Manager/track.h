/* 
 * File: track.h
 * Description: Defines course track structures and functions.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef TRACK_H
#define	TRACK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "node.h"
#include "linked_list.h"

    typedef struct track {
        int number; /* Track ID number*/
        course_node * start_node; /* One of two course nodes connected to track */
        course_node * end_node; /* Second of two course nodes connected to track */
       
        /* 
         * Average number of minutes to complete track.
         * Used for predicting entrant location.
         */
        int minutes;

    } course_track;

    /* Define linked-list structure for course tracks */
    linked_item * linked_track;
    list * track_list;

    int loadTracks();
    void printTracks();
    
    /* Determines the nodes that connect to a particular track. */
    void locateNodes(course_track * new_track, int start_node, int end_node);

#ifdef	__cplusplus
}
#endif

#endif	/* TRACK_H */

