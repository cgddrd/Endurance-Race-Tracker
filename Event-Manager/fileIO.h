/* 
 * File: fileIO.h
 * Description: Defines functions used to open/parse files.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef FILEIO_H
#define	FILEIO_H


#ifdef	__cplusplus
extern "C" {
#endif
    
#include "linked_list.h"
    
    FILE * openFile();
    void initialise(list ** data_list);
    void addToList(linked_item ** temp, list ** data_list);
    void writeFile(char *file_name, char *message);
    void logActivity(char *activity);
    
#ifdef	__cplusplus
}
#endif

#endif	/* FILEIO_H */

