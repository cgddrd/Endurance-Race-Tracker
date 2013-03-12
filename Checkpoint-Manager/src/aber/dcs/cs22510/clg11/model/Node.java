package aber.dcs.cs22510.clg11.model;

/**
 * Defines the data model for a course node within an event. 
 * Allows the setting and retrieval of data about a particular course node.
 * 
 * @author Connor Luke Goddard (clg11)
 * Copyright: Aberystwyth University, Aberystwyth.
 */
public class Node {
    
    /** Type of the node. (CP, MC, JN) */
    private String type;
    
    /** The unique node number. */
    private int number;
    
    /**
     * Default constructor for a Node.
     */
    public Node() {
        
    }
    
    /**
     * Constructor for a Node that allows their characteristics to be set upon 
     * instantiation.
     * 
     * @param cpNumber The new node number to be set.
     * @param cpType The node type of the new node 
     */
    public Node(int cpNumber, String cpType) {
        
        this.number = cpNumber;
        this.type = cpType;
        
    }

    /**
     * Returns the node type of the current node.
     * @return The type of the current node.
     */
    public String getType() {
        return type;
    }

    /**
     * Set the current node type.
     * @param type The new node type to be set.
     */
    public void setType(String type) {
        this.type = type;
    }

    /**
     * Returns the ID number of the node.
     * @return The number of the current node.
     */
    public int getNumber() {
        return number;
    }

    /**
     * Sets the ID number of the current node.
     * @param number the number to set
     */
    public void setNumber(int number) {
        this.number = number;
    }
    
}
