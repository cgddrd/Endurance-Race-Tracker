/* 
 * File: node.h
 * Description: Defines course node structures and functions.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef NODE_H
#define	NODE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "linked_list.h"

    typedef struct node {
        
        int number; /* Node ID number*/
        char type[2]; /* Node type (i.e. checkpoint, junction, medical CP) */

    } course_node;

    /* Define linked-list structure for nodes */
    linked_item * linked_node;
    list * node_list;

    int loadNodes();
    void printNodes();


#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

