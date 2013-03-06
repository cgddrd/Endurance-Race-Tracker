/* 
 * File:   Process.h
 * Author: connor
 *
 * Created on March 4, 2013, 3:25 PM
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
    Process(const Process& orig);
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
   Entrant *emp;
   FileIO io;
   Datastore *data; 
};

#endif	/* PROCESS_H */

