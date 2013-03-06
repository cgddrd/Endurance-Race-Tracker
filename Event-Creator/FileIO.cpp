/* 
 * File:   FileIO.cpp
 * Author: connor
 * 
 * Created on March 4, 2013, 10:49 PM
 */

#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include "FileIO.h"
#include "Event.h"

using namespace std;

FileIO::FileIO() {
}

FileIO::FileIO(const FileIO& orig) {
}

FileIO::~FileIO() {
}

void FileIO::writeEntrants(vector<Entrant*> entrantList) {

    ofstream myfile;
    myfile.open("../files/exampleentrants.txt", ios::out | ios::app);

    for (std::vector<Entrant*>::iterator it = entrantList.begin(); it != entrantList.end(); ++it) {
        (*it)->print();
        myfile << (*it)->getEntrantNo() << " " << (*it)->getCourseID() << " " << (*it)->getEntrantName() << "\n";
    }

    myfile.close();

}

void FileIO::writeCourses(vector<Course*> courseList) {

    ofstream myfile;
    myfile.open("../files/examplecourses.txt", ios::out | ios::app);

    for (vector<Course*>::iterator it = courseList.begin(); it != courseList.end(); ++it) {
        myfile << (*it)->getCourseID() << " " << (*it)->getCourseSize() << " ";
        
        vector<Node*> testy = (*it)->getCourseNodes();
        
         for (vector<Node*>::iterator jt = testy.begin(); jt != testy.end(); ++jt) {
              myfile << (*jt)->getNodeNo() << " ";
         }
        
        myfile << "\n";
    }

    myfile.close();

}

void FileIO::writeEvent(Event *event) {

    ofstream myfile;
    myfile.open("../files/exampleevent.txt", ios::out | ios::trunc);
    
    myfile << (*event).getEventName() << "\n" << (*event).getEventDate() << "\n" << (*event).getEventTime() << "\n";

    myfile.close();

}

vector<vector<string > > FileIO::getFile(string fileName) {

    string line;
    ifstream myfile(fileName.c_str());
    if (myfile.is_open()) {
        
        while (std::getline(myfile, line)) {

            istringstream ss(line);
            istream_iterator<string> begin(ss), end;

            //putting all the tokens in the vector
            vector<string> allStrings(begin, end);
            arrayTokens.push_back(allStrings);

        }
        
        myfile.close();  
    }
    
    return arrayTokens;
}

