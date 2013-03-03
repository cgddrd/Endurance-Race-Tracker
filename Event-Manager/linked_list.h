/* 
 * File: linked_list.h
 * Description: Defines a generic linked-list structure used the program.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H

#ifdef	__cplusplus
extern "C" {
#endif

    /* Defines a generic linked-list item */
    typedef struct list_item {
        
        void * data; /* 'void' used to create generic pointer */
        struct list_item * next; /* Pointer to next linked-list item */

    } linked_item;

    /* Defines structure of generic linked-list */
    typedef struct linked_list {
        
        linked_item * head;
        linked_item * tail;
        int no_of_items;

    } list;

    void initialise();


#ifdef	__cplusplus
}
#endif

#endif	/* LINKED_LIST_H */

