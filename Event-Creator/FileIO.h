/* 
 * File: FileIO.h
 * Description: Defines all variables/methods for the FileIO class.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#ifndef FILEIO_H
#define	FILEIO_H

#include "Entrant.h"
#include "Course.h"
#include "Event.h"

class FileIO {
public:
    FileIO();
    virtual ~FileIO();
    int createDirectory(Event *event);
    void writeEntrants(std::vector<Entrant*> entrantList, Event *event);
    void writeCourses(std::vector<Course*> courseList, Event *event);
    void writeEvent(Event *event);
    std::vector<std::vector<std::string > > getFile(std::string fileName);
private:
    
    /** 
     * Vector of vectors used to store the contents of individual line
     * that collect to form the entire file.
     */
    std::vector<std::vector<std::string > > arrayTokens; 
};

#endif	/* FILEIO_H */

