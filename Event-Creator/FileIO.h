/* 
 * File:   FileIO.h
 * Author: connor
 *
 * Created on March 4, 2013, 10:49 PM
 */

#ifndef FILEIO_H
#define	FILEIO_H

#include "Entrant.h"

class FileIO {
public:
    FileIO();
    FileIO(const FileIO& orig);
    virtual ~FileIO();
    void writeEntrants(std::vector<Entrant*> entrantList);
private:

};

#endif	/* FILEIO_H */

