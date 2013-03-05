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

class Process {
public:
    Process();
    Process(const Process& orig);
    virtual ~Process();
    void addEntrant();
    void getAllNodes();
    void showCourseEditor();
    void createNewCourse();
    Course* getSelectedCourse();
    void addCourseNode(Course *currentCourse);
    const std::vector<Entrant*> getEntrantList(void) const;
    const std::vector<Node*> getNodeList() const;
private:
   std::vector<Entrant*> entrantList;
   std::vector<Node*> nodeList;
   std::vector<Course*> courseList;
   Entrant *emp;
};

#endif	/* PROCESS_H */

