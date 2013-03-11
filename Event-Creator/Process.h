/* 
 * File: Process.h
 * Description: Defines all variables/methods for the Process class.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#ifndef PROCESS_H
#define	PROCESS_H

#include <vector>
#include <cstdlib>
#include "Entrant.h"
#include "Node.h"
#include "Course.h"
#include "FileIO.h"
#include "Datastore.h"
#include "Event.h"

class Process {
    
public:
    
    Process(Datastore *newData);
    virtual ~Process();
    void addEntrant(void);
    void createEvent(void);
    void getAllNodes(void);
    void showCourseEditor(void);
    void createNewCourse(void);
    Course* getSelectedCourse(void);
    void addCourseNode(Course *currentCourse);
    std::string convertDate(std::string &input);
    
private:
    
   /** Allows access to file I/O methods.*/
   FileIO io;
   
   /** Pointer to shared Datastore class created in "main.cpp".*/
   Datastore *data; 
};

#endif	/* PROCESS_H */

