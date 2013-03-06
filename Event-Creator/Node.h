/* 
 * File: Course.h
 * Description: Defines all variables/methods for the Node class.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#ifndef NODE_H
#define	NODE_H

#include <string>

/**
 *  Course class used to define the data model for a paritcular course node.
 */
class Node {
    
public:
    Node();
    Node(const Node& orig);
    Node(const int newNodeNo, std::string newNodeType);
    virtual ~Node();
    void setNodeType(std::string nodeType);
    std::string getNodeType(void) const;
    const int getNodeNo(void) const;
    
private:
    const int nodeNo; /**< Unique number that represents a node.*/
    std::string nodeType; /**< Contains the type of node.*/
};

#endif	/* NODE_H */

