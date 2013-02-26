/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.model;

/**
 *
 * @author connor
 */
public class Entrant {
    
    private String name;
    private int number;
    private int currentProgress;
    
    public Entrant() {
        
        this.currentProgress = 0;
        
    }
    
    public Entrant(String enName, int enNumber) {
     
        this.name = enName;
        this.number = enNumber;
        this.currentProgress = 0;
        
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
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

    /**
     * @return the currentProgress
     */
    public int getCurrentProgress() {
        return currentProgress;
    }

    /**
     * @param currentProgress the currentProgress to set
     */
    public void setCurrentProgress(int currentProgress) {
        this.currentProgress = currentProgress;
    }
   
}
