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
    
    private ArrayList<Node> courseNodes = new ArrayList<>();
    private int courseLength;
    private char courseID;
    
    public Course() {
           
    }
    
    public void addNewNode(Node newNode) {
        
        getCourseNodes().add(newNode);
        
    }

    /**
     * @return the courseNodes
     */
    public ArrayList<Node> getCourseNodes() {
        return courseNodes;
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

    /**
     * @param courseNodes the courseNodes to set
     */
    public void setCourseNodes(ArrayList<Node> courseNodes) {
        this.courseNodes = courseNodes;
    }

    /**
     * @return the courseID
     */
    public char getCourseID() {
        return courseID;
    }

    /**
     * @param courseID the courseID to set
     */
    public void setCourseID(char courseID) {
        this.courseID = courseID;
    }
    
}