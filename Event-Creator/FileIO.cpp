/* 
 * File: FileIO.cpp
 * Description: Provides file input/output and parsing facilities.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
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

/**
 * Default constructor for FileIO.
 */
FileIO::FileIO() {
}

/**
 * Destructor to be used once object is removed.
 */
FileIO::~FileIO() {
}

/**
 * Writes all the created entrants for a particular event to file using a
 * specified format. Entrant information is obtained from the Entrant pointers vector 
 * stored within the Datastore class.
 * @param entrantList Vector of all the Entrant pointers contained 
 * within Datastore class.
 */
void FileIO::writeEntrants(vector<Entrant*> entrantList) {

    //Create a new file stream.
    ofstream myfile;

    /**
     * "Load" or create a new file with the given file name.
     * Flags: ios::out = Output to file, ios::app = Append to existing file
     * or create a new one.
     */
    myfile.open("../files/exampleentrants.txt", ios::out | ios::app);

    //Loop through all the created entrants.
    for (vector<Entrant*>::iterator it = entrantList.begin(); it != entrantList.end(); ++it) {

        //Write the entrant details to the file using specific format.
        myfile << (*it)->getEntrantNo() << " " << (*it)->getCourseID() << " " << (*it)->getEntrantName() << "\n";
    }

    //Close the file stream once completed.
    myfile.close();

}

/**
 * Writes all the created courses for a particular event to file using a
 * specified format. Course information is obtained from the Entrant pointers vector 
 * stored within the Datastore class.
 * @param entrantList Vector of all the Course pointers contained 
 * within Datastore class.
 */
void FileIO::writeCourses(vector<Course*> courseList) {

    ofstream myfile;
    myfile.open("../files/examplecourses.txt", ios::out | ios::app);

    //Loop through all the the courses in the vector.
    for (vector<Course*>::iterator it = courseList.begin(); it != courseList.end(); ++it) {
        
        //Write the current course ID and total course size to file.
        myfile << (*it)->getCourseID() << " " << (*it)->getCourseSize() << " ";

        //Create a temporary array of current course nodes.
        vector<Node*> currentCourseNodes = (*it)->getCourseNodes();

        //Loop through all nodes that make up the current course.
        for (vector<Node*>::iterator jt = currentCourseNodes.begin(); jt != currentCourseNodes.end(); ++jt) {
            
            //Write the node number to the file.
            myfile << (*jt)->getNodeNo() << " ";
        }

        myfile << "\n";
    }

    myfile.close();

}

/**
 * Writes the details of a particular event to file using a
 * specified format. Event information is obtained from the 'event' pointer
 * stored within the Datastore class.
 * @param event Pointer to the stored Event class.
 */
void FileIO::writeEvent(Event *event) {

    ofstream myfile;
    myfile.open("../files/exampleevent.txt", ios::out | ios::trunc);

    myfile << (*event).getEventName() << "\n" << (*event).getEventDate() << "\n" << (*event).getEventTime() << "\n";

    myfile.close();

}

/**
 * Accesses a specified file and returns the contents as a vector.
 * @param fileName The file path of the specified file. 
 * @return A vector of vectors that each contain the contents of each line
 * of the file that was read in. 
 */
vector<vector<string > > FileIO::getFile(string fileName) {

    string line;
    
    //Create a new file stream.
    ifstream myfile(fileName.c_str());
    
    //Check the file has been successfully opened.
    if (myfile.is_open()) {

        //Read the entire contents of the file.
        while (std::getline(myfile, line)) {

            //Split the current line by white space into separate tokens.
            istringstream ss(line);
            istream_iterator<string> begin(ss), end;

            //Place all the tokens into a new vector (For the line).
            vector<string> allStrings(begin, end);
            
            //Add this vector to the parent vector for the whole file.
            arrayTokens.push_back(allStrings);

        }
        
        myfile.close();
    }

    //Return the vector. If the loading was un-successful, it will be empty.
    return arrayTokens;
}