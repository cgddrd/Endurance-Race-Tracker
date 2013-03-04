/* 
 * File:   Entrant.h
 * Author: connor
 *
 * Created on March 4, 2013, 10:21 AM
 */

#ifndef ENTRANT_H
#define	ENTRANT_H

#include <string>

class Entrant {
    
public:
    Entrant(const std::string &theName, const int theEnNo, char theCourseID);
    virtual ~Entrant();
    void print(void) const;
private:
    std::string entrant_name;
    const int entrant_no;
    char course_id;
};

#endif	/* ENTRANT_H */

