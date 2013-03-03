/* 
 * File: main.h
 * Description: Defines functions used by user to interact with program.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "event.h"
#include "node.h"
#include "fileIO.h"
#include "track.h"
#include "course.h"
#include "entrant.h"
#include "display.h"
#include "process.h"
    

    void loadFiles();
    void displayMenu();
    
    /* Define function pointers (one returns an int, other void)*/
    int (*functionPtr)();
    void (*printfunctionPtr)();
    
    /* Define function that takes the two function pointers as parameters */
    void checkFileLoad(int (*loadFunctionPtr)(), void (*printFunctionPtr)());

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

