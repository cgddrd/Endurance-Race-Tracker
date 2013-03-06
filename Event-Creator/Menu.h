/* 
 * File: Course.h
 * Description: Defines all variables/methods for the Course class.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#ifndef MENU_H
#define	MENU_H

#include "Process.h"
#include "Course.h"
#include "FileIO.h"

/**
 * Used to provide interactive interface with the application through
 * the use of menus.
 */
class Menu {
    
public:
    
    Menu(Datastore *newData, Process *newProc);
    Menu(const Menu& orig);
    virtual ~Menu();
    void showEventEditor(void);
    void showCourseEditor(void);
    void showEntrantEditor(void);
    void showMainMenu(void);
    void checkExistingEvent(void); 
    
private:
    
    /** Pointer to shared Process class created in "main.cpp".*/
    Process *proc; 
    
    /** Pointer to shared Datastore class created in "main.cpp".*/
    Datastore *data;
    
    /** Allows access to file I/O methods.*/
    FileIO io;
};

#endif	/* MENU_H */

