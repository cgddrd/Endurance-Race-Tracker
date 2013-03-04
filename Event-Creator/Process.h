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

class Process {
public:
    Process();
    Process(const Process& orig);
    virtual ~Process();
    void addEntrant();
    std::vector<Entrant*> getEntrantList(void);
private:
   std::vector<Entrant*> entrantList;
   Entrant *emp;
};

#endif	/* PROCESS_H */

