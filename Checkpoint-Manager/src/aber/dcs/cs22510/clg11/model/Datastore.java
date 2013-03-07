package aber.dcs.cs22510.clg11.model;

import java.util.ArrayList;

/**
 * Stores all internal data used by the system to process existing and new
 * race time logs (Nodes, Courses and Entrants). 
 * 
 * @author Connor Luke Goddard (clg11)
 * Copyright: Aberystwyth University, Aberystwyth.
 */
public class Datastore {
    
    /** Arraylist of all courses in an event. */
    private ArrayList<Course> courses = new ArrayList<>();
    
    /** Arraylist of all nodes in an event. */
    private ArrayList<Node> nodes = new ArrayList<>();
    
    /** Arraylist of all entrants registered to an event. */
    private ArrayList<Entrant> entrants = new ArrayList<>();
    
    /**
     * Default constructor for a Course.
     */
    public Datastore() {
        
        
    }

    /**
     * Fetches all courses that are stored for a particular event.
     * @return The collection of courses.
     */
    public ArrayList<Course> getCourses() {
        return courses;
    }


    /**
     * Fetches all the nodes that are stored for a particular event.
     * @return The collection of nodes.
     */
    public ArrayList<Node> getNodes() {
        return nodes;
    }


    /**
     * Fetches all the entrants that are stored for a particular event.
     * @return The collection of entrants.
     */
    public ArrayList<Entrant> getEntrants() {
        return entrants;
    }
    
}
