package aber.dcs.cs22510.clg11.model;

import java.util.ArrayList;

/**
 * Defines the data model for an event course. 
 * Allows the setting and retrieval of data about a particular course.
 * 
 * @author Connor Luke Goddard (clg11)
 * Copyright: Aberystwyth University, Aberystwyth.
 */
public class Course {
    
    /** Arraylist of Nodes that make up the Course. */
    private ArrayList<Node> courseNodes = new ArrayList<>();
    
    /** The total length of the course (i.e. the size of the course array).*/
    private int courseLength;
    
    /** The unique ID of a particular course. */
    private char courseID;
    
    /**
     * Default constructor for a Course.
     */
    public Course() {
           
    }
    
    /**
     * Adds a new {@link aber.dcs.cs22510.clg11.model.Node} to the collection
     * of nodes that make up the course.
     * @param newNode The new node to be added to the course.
     */
    public void addNewNode(Node newNode) {
        
        getCourseNodes().add(newNode);
        
    }

    /**
     * Fetches the collection of {@link aber.dcs.cs22510.clg11.model.Node}s that
     * make up the course.
     * @return The collection of nodes in the course.
     */
    public ArrayList<Node> getCourseNodes() {
        return courseNodes;
    }

    /**
     * Fetches the total size of the course.
     * @return The total size of the Arraylist of Nodes.
     */
    public int getCourseLength() {
        return courseLength;
    }

    /**
     * Sets the 'courseLength' value of the course.
     * @param courseLength The new courselength value.
     */
    public void setCourseLength(int courseLength) {
        this.courseLength = courseLength;
    }

    /**
     * Sets the Arraylist of course nodes.
     * @param courseNodes The collection of course nodes to be set.
     */
    public void setCourseNodes(ArrayList<Node> courseNodes) {
        this.courseNodes = courseNodes;
    }

    /**
     * Fetches the ID character of the course.
     * @return The ID of the current course.
     */
    public char getCourseID() {
        return courseID;
    }

    /**
     * Sets the ID of the current course.
     * @param courseID The course ID to be set.
     */
    public void setCourseID(char courseID) {
        this.courseID = courseID;
    }
    
}