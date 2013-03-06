/* 
 * File:   FileIO.h
 * Author: connor
 *
 * Created on March 4, 2013, 10:49 PM
 */

#ifndef FILEIO_H
#define	FILEIO_H

#include "Entrant.h"
#include "Course.h"
#include "Event.h"
#include <iterator> //for std::istream_iterator

class FileIO {
public:
    FileIO();
    FileIO(const FileIO& orig);
    virtual ~FileIO();
    void writeEntrants(std::vector<Entrant*> entrantList);
    void writeCourses(std::vector<Course*> courseList);
    void writeEvent(Event *event);
    std::vector<std::vector<std::string > > getFile(std::string fileName);
private:
    std::vector<std::vector<std::string > > arrayTokens;
};

#endif	/* FILEIO_H */

