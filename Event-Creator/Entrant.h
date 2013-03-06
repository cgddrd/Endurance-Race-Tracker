/* 
 * File: Entrant.h
 * Description: Defines all variables/methods for the Entrant class.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#ifndef ENTRANT_H
#define	ENTRANT_H

#include <string>

/**
 * Entrant class used to define the data model for a particular entrant.
 */
class Entrant {
    
public:
    Entrant(const std::string &theName, const int theEnNo, char theCourseID);
    virtual ~Entrant();
    void print(void) const;
    std::string getEntrantName(void);
    int getEntrantNo(void);
    char getCourseID(void);
private:
    std::string entrant_name; /**< The name of the entrant.*/
    const int entrant_no; /**< The unique number for the entrant.*/
    char course_id; /**< The ID that the entrant is registered for.*/
};

#endif	/* ENTRANT_H */

