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
    myfile.open("../files/example.txt", ios::out | ios::app);
   

    for (std::vector<Entrant*>::iterator it = entrantList.begin(); it != entrantList.end(); ++it) {
        (*it)->print();
        myfile << (*it)->getEntrantNo() << " " << (*it)->getCourseID() << " " << (*it)->getEntrantName() << "\n";
    }
    
     myfile.close();
     
}

