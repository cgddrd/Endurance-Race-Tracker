/* 
 * File:   Menu.h
 * Author: connor
 *
 * Created on March 5, 2013, 4:41 PM
 */

#ifndef MENU_H
#define	MENU_H

#include "Process.h"
#include "Course.h"
#include "FileIO.h"

class Menu {
public:
    Menu(Datastore *newData, Process *newProc);
    Menu(const Menu& orig);
    virtual ~Menu();
    void showEventEditor();
    void showCourseEditor();
    void showEntrantEditor();
    void showMainMenu();
private:
    Process *proc;
    Datastore *data;
    FileIO io;
};

#endif	/* MENU_H */

