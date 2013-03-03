/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22510.clg11.model;

import java.util.ArrayList;

/**
 *
 * @author Connor Luke Goddard (clg11)
 */
public class Datastore {
    
    private ArrayList<Course> courses = new ArrayList<>();
    private ArrayList<Node> nodes = new ArrayList<>();
    private ArrayList<Entrant> entrants = new ArrayList<>();
    
    public Datastore() {
        
        
    }

    /**
     * @return the courses
     */
    public ArrayList<Course> getCourses() {
        return courses;
    }

    /**
     * @param courses the courses to set
     */
    public void setCourses(ArrayList<Course> courses) {
        this.courses = courses;
    }

    /**
     * @return the nodes
     */
    public ArrayList<Node> getNodes() {
        return nodes;
    }

    /**
     * @param nodes the nodes to set
     */
    public void setNodes(ArrayList<Node> nodes) {
        this.nodes = nodes;
    }

    /**
     * @return the entrants
     */
    public ArrayList<Entrant> getEntrants() {
        return entrants;
    }

    /**
     * @param entrants the entrants to set
     */
    public void setEntrants(ArrayList<Entrant> entrants) {
        this.entrants = entrants;
    }
    
}
