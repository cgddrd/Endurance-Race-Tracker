/* 
 * File: main.cpp
 * Description: Bootstrap loader for the application.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#include <cstdlib>
#include "Process.h"
#include "Menu.h"

using namespace std;

/**
 * Bootstrap method for the application.
 */
int main(int argc, char** argv) {

    /**
     * New Datastore object created on the heap
     * that is used throughout the program. 
     */ 
    Datastore *data = new Datastore(); 
    
    /**
     * New Process object created on the heap
     * that is used throughout the program. 
     */ 
    Process *proc = new Process(data);
    
    /**
     * New Menu object created on the heap 
     * that will display the main menu.
     */ 
    Menu *menu = new Menu(data, proc);
    
    //Load course nodes into system from "nodes.txt" file.
    proc->getAllNodes();
    
    //Display the main program menu.
    menu->showMainMenu();

   return 0;
}

