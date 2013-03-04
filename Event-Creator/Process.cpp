/* 
 * File:   Process.cpp
 * Author: connor
 * 
 * Created on March 4, 2013, 3:25 PM
 */

#include "Process.h"
#include "Entrant.h"
#include <vector>
#include <iostream>

using namespace std;

Process::Process() {
    
    
}

Process::Process(const Process& orig) {
}

Process::~Process() {
}

void Process::addEntrant() {
    
   string test;
   int enno;
   char cid;
   
   cout << "Please enter a name: ";
   cin >> test; 
   
   cout << "Please enter an entrant no: ";
   cin >> enno; 
   
   cout << "Please enter an course ID: ";
   cin >> cid; 
   
   emp = new Entrant(test, enno, cid);            
   entrantList.push_back(emp);        
    
}

vector<Entrant*> Process::getSalaryInfoRequestCount() {
    
    return entrantList;
}

