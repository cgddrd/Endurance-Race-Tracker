/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22510.clg11.model;

/**
 *
 * @author connor
 */
public class Entrant {
    
    private String firstName;
    private String lastName;
    private int number;
    private int currentProgress;
    private char courseID;
    private boolean isExcluded = false;
    private boolean isFinished = false;
    
    public Entrant() {
        
        this.currentProgress = 0;
        
    }
    
    public Entrant(String firstName, String lastName, char courseID, int enNumber) {
     
        this.firstName = firstName;
        this.lastName = lastName;
        this.courseID = courseID;
        this.number = enNumber;
        this.currentProgress = 0;
        
    }

    /**
     * @return the name
     */
    public String getFullName() {
        return getFirstName() + " " + getLastName();
    }

    /**
     * @param name the name to set
     */
    public void setFullName(String name) {
        String[] tempName = name.split(" ");
        this.setFirstName(tempName[0]);
        this.setLastName(tempName[1]);
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

    /**
     * @return the firstName
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * @param firstName the firstName to set
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * @return the lastName
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * @param lastName the lastName to set
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
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

    /**
     * @return the isExcluded
     */
    public boolean getIsExcluded() {
        return isExcluded;
    }

    /**
     * @param isExcluded the isExcluded to set
     */
    public void setIsExcluded(boolean isExcluded) {
        this.isExcluded = isExcluded;
    }

    /**
     * @return the isFinished
     */
    public boolean getIsFinished() {
        return isFinished;
    }

    /**
     * @param isFinished the isFinished to set
     */
    public void setIsFinished(boolean isFinished) {
        this.isFinished = isFinished;
    }
   
}
