/* 
 * File:   Datastore.h
 * Author: connor
 *
 * Created on March 5, 2013, 4:40 PM
 */

#ifndef DATASTORE_H
#define	DATASTORE_H

#include <vector>
#include <cstdlib>
#include "Entrant.h"
#include "Node.h"
#include "Course.h"

class Datastore {
public:
    Datastore();
    Datastore(const Datastore& orig);
    virtual ~Datastore();
private:
   std::vector<Entrant*> entrantList;
   std::vector<Node*> nodeList;
   std::vector<Course*> courseList;
};

#endif	/* DATASTORE_H */

