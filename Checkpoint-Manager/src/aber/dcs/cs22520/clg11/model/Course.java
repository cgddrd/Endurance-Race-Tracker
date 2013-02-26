/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.model;

import java.util.ArrayList;

/**
 *
 * @author connor
 */
public class Course {
    
    private ArrayList<Node> courseNodes;
    private int courseLength;
    
    public Course() {
           
    }
    
    public void addNewNode(Node newNode) {
        
        courseNodes.add(newNode);
        
    }

    /**
     * @return the courseNodes
     */
    public ArrayList<Node> getCourseNodes() {
        return courseNodes;
    }

    /**
     * @param courseNodes the courseNodes to set
     */
    public void setCourseNodes(ArrayList<Node> courseNodes) {
        this.courseNodes = courseNodes;
    }

    /**
     * @return the courseLength
     */
    public int getCourseLength() {
        return courseLength;
    }

    /**
     * @param courseLength the courseLength to set
     */
    public void setCourseLength(int courseLength) {
        this.courseLength = courseLength;
    }
    
}