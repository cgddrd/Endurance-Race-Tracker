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
#include <sys/types.h>
#include <sys/stat.h>
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
 * Creates a new file directory for the event, which will be used to 
 * store all the data files created for the event.
 * @param event Event object created by the user.
 * @return Integer describing if the folder was created successfully.
 */
int FileIO::createDirectory(Event *event) {

    int status;

    string folder = "../files/" + event->getEventName();
   
    //Set the directory of the event.
    event->setDirectory(folder);

    /*
     * Create the directory with write/read permissions for owner/group, and 
     * read only permissions for others.
     */
    return status = mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
}

/**
 * Writes all the created entrants for a particular event to file using a
 * specified format. Entrant information is obtained from the Entrant pointers vector 
 * stored within the Datastore class.
 * @param entrantList Vector of all the Entrant pointers contained 
 * within Datastore class.
 */
void FileIO::writeEntrants(vector<Entrant*> entrantList, Event *event) {

    string folder = event->getDirectory();
                
    folder += "/entrants.txt";
    
    //Create a new file stream.
    ofstream myfile;

    /**
     * "Load" or create a new file with the given file name.
     * Flags: ios::out = Output to file, ios::app = Append to existing file
     * or create a new one.
     */
    myfile.open(folder.c_str(), ios::out | ios::app);

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
void FileIO::writeCourses(vector<Course*> courseList, Event *event) {
    
    string folder = event->getDirectory();
                
    folder += "/courses.txt";

    ofstream myfile;
    myfile.open(folder.c_str(), ios::out | ios::app);

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

    //Get the status of the folder directory creation. 
    int status = createDirectory(event);
    
    //Check if the file was created successfully or not.
    if (status == 0) {

        ofstream myfile;

        //Get the current event directory.
        string folder = event->getDirectory();
                
        folder += "/event.txt";

        //Create a file stream with that will overwrite any existing file.
        myfile.open(folder.c_str(), ios::out | ios::trunc);

        //Write to the file the event data.
        myfile << (*event).getEventName() << "\n" << (*event).getEventDate() << "\n" << (*event).getEventTime() << "\n";

        //Close the file stream. 
        myfile.close();

    } else {

        cout << "ERROR: Event folder could not be created. ";
    }

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