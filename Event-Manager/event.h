/* 
 * File: event.h
 * Description: Defines the structure of an event, and defines functions used.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef EVENT_H
#define	EVENT_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct event {
        char event_title[79];
        char event_date[79];
        char event_time[5];
    } event_description;

    /* Defines instance of event used by program */
    event_description * event;

    int loadEventDes();
    void printEventDes();


#ifdef	__cplusplus
}
#endif

#endif	/* EVENT_H */

