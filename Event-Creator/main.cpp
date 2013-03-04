/* 
 * File:   main.cpp
 * Author: connor
 *
 * Created on March 3, 2013, 7:06 PM
 */

#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include "Process.h"
#include "FileIO.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Process test;
    FileIO io;

    // test.addEntrant("David", 45, 'B');
    // test.addEntrant("Connor", 1, 'E');

    test.addEntrant();
    test.addEntrant();

  /*  vector<Entrant*> bar = test.getEntrantList();

    for (std::vector<Entrant*>::iterator it = bar.begin(); it != bar.end(); ++it) {
        (*it)->print();
    }

    test.addEntrant();

    bar = test.getEntrantList(); */

    io.writeEntrants(test.getEntrantList());

    return 0;
}

