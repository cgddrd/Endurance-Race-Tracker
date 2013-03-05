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

using namespace std;

FileIO::FileIO() {
}

FileIO::FileIO(const FileIO& orig) {
}

FileIO::~FileIO() {
}

void FileIO::writeEntrants(std::vector<Entrant*> entrantList) {

    ofstream myfile;
    myfile.open("../files/exampleentrants.txt", ios::out | ios::app);


    for (std::vector<Entrant*>::iterator it = entrantList.begin(); it != entrantList.end(); ++it) {
        (*it)->print();
        myfile << (*it)->getEntrantNo() << " " << (*it)->getCourseID() << " " << (*it)->getEntrantName() << "\n";
    }

    myfile.close();

}

void FileIO::writeCourses(std::vector<Course*> courseList) {

    ofstream myfile;
    myfile.open("../files/examplecourses.txt", ios::out | ios::app);


    for (std::vector<Course*>::iterator it = courseList.begin(); it != courseList.end(); ++it) {
        myfile << (*it)->getCourseID() << " " << (*it)->getCourseSize() << " ";
        
        std::vector<Node*> testy = (*it)->getCourseNodes();
        
         for (std::vector<Node*>::iterator jt = testy.begin(); jt != testy.end(); ++jt) {
             //cout << "THIS NODE: " << (*jt)->getNodeNo() << endl;
              myfile << (*jt)->getNodeNo() << " ";
         }
        
        myfile << "\n";
    }

    myfile.close();

}

std::vector<std::vector<std::string > > FileIO::getFile() {

    string line;
    ifstream myfile("../files/nodes.txt");
    if (myfile.is_open()) {
        
        while (std::getline(myfile, line)) {

            std::istringstream ss(line);
            std::istream_iterator<std::string> begin(ss), end;

            //putting all the tokens in the vector
            std::vector<std::string> poo(begin, end);
            //line.at(0)
            test.push_back(poo);

        }
        
        myfile.close();
    }
    
    return test;
  
}

