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
#include <iterator> //for std::istream_iterator

class FileIO {
public:
    FileIO();
    FileIO(const FileIO& orig);
    virtual ~FileIO();
    void writeEntrants(std::vector<Entrant*> entrantList);
    void writeCourses(std::vector<Course*> courseList);
    std::vector<std::vector<std::string > > getFile();
private:
    std::vector<std::string> arrayTokens;
    std::vector<std::vector<std::string > > test;
};

#endif	/* FILEIO_H */

