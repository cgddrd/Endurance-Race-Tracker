/**
 * File: Node.cpp
 * Description: Provides the data model for a particular course node.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#include <iostream>
#include "Node.h"

using namespace std;

/**
 * Constructor that allows the characteristics of a course node to be specified.
 * Constant variable 'nodeNo' is set it's value here.
 * @param newNodeNo The unique identifier of a particular node. (constant)
 * @param newNodeType The course node type to be set.
 */
Node::Node(const int newNodeNo, string newNodeType) : nodeNo(newNodeNo){
   
    setNodeType(newNodeType);
    
}

/**
 * Destructor to be used once object is removed.
 */
Node::~Node() {
}


/**
 * NOTE: setNodeNo() cannot be used due to 'nodeNo'
 * being a CONSTANT value. It therefore cannot be changed
 * once created. Making the variable MUTABLE however would allow ]
 * it to be changed.
 */

/**
 * Updates the type value of the node.
 * @param nodeType The new node type value.
 */
void Node::setNodeType(string nodeType) {
    this->nodeType = nodeType;
}

/**
 * Fetches the node type of the current node.
 * @return The type of the current node.
 */
string Node::getNodeType(void) const {
    return nodeType;
}

/**
 * Fetches the unique number of the node.
 * @return The number representing the node.
 */
const int Node::getNodeNo(void) const {
    return nodeNo;
}