/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22510.clg11.model;

/**
 *
 * @author connor
 */
public class Node {
    
    private String type;
    private int number;
    
    public Node() {
        
    }
    
    public Node(int cpNumber, String cpType) {
        
        this.number = cpNumber;
        this.type = cpType;
        
    }

    /**
     * @return the type
     */
    public String getType() {
        return type;
    }

    /**
     * @param type the type to set
     */
    public void setType(String type) {
        this.type = type;
    }

    /**
     * @return the number
     */
    public int getNumber() {
        return number;
    }

    /**
     * @param number the number to set
     */
    public void setNumber(int number) {
        this.number = number;
    }
    
}
