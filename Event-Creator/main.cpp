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

  //  test.addEntrant();
  //  test.addEntrant();

  //  io.writeEntrants(test.getEntrantList());
    
    test.getAllNodes();

    return 0;
}

