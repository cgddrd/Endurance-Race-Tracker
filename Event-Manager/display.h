/* 
 * File: display.h
 * Description: Defines functions used to display information to screen.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "entrant.h"

    void checkStarted();
    void checkNotStarted();
    void checkFinished();
    void displayResultsList();
    void checkExcluded();
    
#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

