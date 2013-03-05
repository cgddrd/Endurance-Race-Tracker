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
#include "Menu.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Datastore *data = new Datastore();
    Process *proc = new Process(data);
    
    Menu *menu = new Menu(data, proc);
    
    proc->getAllNodes();
    menu->showMainMenu();
    
 //   Process test();
  //  FileIO io;

  //  test.addEntrant();
  //  test.addEntrant();

  //  io.writeEntrants(test.getEntrantList());
    
  //  test.getAllNodes();
    
  //  test.showCourseEditor();

    return 0;
}

