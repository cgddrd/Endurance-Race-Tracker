/* 
 * File:   Node.cpp
 * Author: connor
 * 
 * Created on March 4, 2013, 10:20 AM
 */

#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(const int newNodeNo, std::string newNodeType) : nodeNo(newNodeNo){
   
    setNodeType(newNodeType);
    
}

Node::~Node() {
}

void Node::setNodeType(std::string nodeType) {
    this->nodeType = nodeType;
}

std::string Node::getNodeType(void) const {
    return nodeType;
}

const int Node::getNodeNo(void) const {
    return nodeNo;
}

void Node::print(void) const {
    cout << "Node no: " << nodeNo << ' ';
    cout << "Node type: " << nodeType << endl;
}

