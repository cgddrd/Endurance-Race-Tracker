/* 
 * File:   Node.h
 * Author: connor
 *
 * Created on March 4, 2013, 10:20 AM
 */

#ifndef NODE_H
#define	NODE_H

#include <string>


class Node {
public:
    Node();
    Node(const Node& orig);
    Node(const int newNodeNo, std::string newNodeType);
    virtual ~Node();
    void setNodeType(std::string nodeType);
    std::string getNodeType(void) const;
    const int getNodeNo(void) const;
    void print(void) const;
private:
    const int nodeNo;
    std::string nodeType;
};

#endif	/* NODE_H */

