package aber.dcs.cs22510.clg11.model;

/**
 * Defines the data model for an entrant registered for an event. 
 * Allows the setting and retrieval of data about a particular entrant.
 * 
 * @author Connor Luke Goddard (clg11)
 * Copyright: Aberystwyth University, Aberystwyth.
 */
public class Entrant {
    
    private String firstName;
    private String lastName;
    
    /** Entrant number used for tracking of entrant. */
    private int number;
    
    /** The current progress of the entrant along their registered course. */
    private int currentProgress;
    
    /** The ID character of the course the entrant is registered for. */
    private char courseID;
    
    /** Defines if the entrant is excluded or not. */
    private boolean isExcluded = false;
    
    /** Defines if the entrant has finished or not. */
    private boolean isFinished = false;
    
    /** Defines if the entrant is currently at a medical checkpoint. */
    private boolean atMC = false;
    
    /**
     * Default constructor for an Entrant.
     * Sets the current progress to 0 as a new entrant will
     * not have started the race.
     */
    public Entrant() {
        
        this.currentProgress = 0;
        
    }
    
    /**
     * Constructor for an Entrant that allows their characteristics to be set upon 
     * instantiation.
     * @param firstName The first name of the new entrant.
     * @param lastName The last name of the new entrant.
     * @param courseID The ID of the course the new entrant is registered for.
     * @param enNumber The race number of the new entrant.
     */
    public Entrant(String firstName, String lastName, char courseID, int enNumber) {
     
        this.firstName = firstName;
        this.lastName = lastName;
        this.courseID = courseID;
        this.number = enNumber;
        this.currentProgress = 0;
        
    }

    /**
     * Fetches the full name (both first and last) name of the entrant.
     * @return The full name of the entrant.
     */
    public String getFullName() {
        return getFirstName() + " " + getLastName();
    }

    /**
     * Sets the full name of the entrant by splitting the full
     * name on a space and setting the separate first, and last names.
     * @param name The inputted full name to be set.
     */
    public void setFullName(String name) {
        
        //Split the inputted name by a space.
        String[] tempName = name.split(" ");
        this.setFirstName(tempName[0]);
        this.setLastName(tempName[1]);
    }

    /**
     * Returns the race number of the entrant.
     * @return The race number of the entrant.
     */
    public int getNumber() {
        return number;
    }

    /**
     * Sets the race number of the entrant.
     * @param number The race number to be set. 
     */
    public void setNumber(int number) {
        this.number = number;
    }

    /**
     * Fetches the current progress of the entrant along their course.
     * @return The current progress of the entrant on their course.
     */
    public int getCurrentProgress() {
        return currentProgress;
    }

    /**
     * Updates the current progress of the entrant along their course.
     * @param currentProgress The incremented progress of the entrant.
     */
    public void setCurrentProgress(int currentProgress) {
        this.currentProgress = currentProgress;
    }

    /**
     * Returns the first name of the entrant.
     * @return The first name of the entrant.
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Sets the first name only of the entrant.
     * @param firstName The first name of the entrant to be set.
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * Returns the last name of the entrant.
     * @return The last name of the entrant.
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Sets the last name only of the entrant.
     * @param lastName The last name of the entrant to be set.
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /**
     * Fetches the course ID that the entrant is registered for.
     * @return The ID of the registered course.
     */
    public char getCourseID() {
        return courseID;
    }

    /**
     * Sets the course ID of the entrant.
     * @param courseID The ID of the course that the entrant is registered for.
     */
    public void setCourseID(char courseID) {
        this.courseID = courseID;
    }

    /**
     * Returns whether the entrant is excluded or not.
     * @return Boolean determining if the entrant is excluded.
     */
    public boolean getIsExcluded() {
        return isExcluded;
    }

    /**
     * Sets whether or not the entrant is excluded.
     * @param isExcluded Whether the entrant is excluded or not.
     */
    public void setIsExcluded(boolean isExcluded) {
        this.isExcluded = isExcluded;
    }

    /**
     * Returns whether the entrant has finished their race or not.
     * @return Boolean determining if the entrant has finished.
     */
    public boolean getIsFinished() {
        return isFinished;
    }

    /**
     * Sets whether or not the entrant has finished their race or not.
     * @param isFinished 
     */
    public void setIsFinished(boolean isFinished) {
        this.isFinished = isFinished;
    }

    /**
     * Returns if the entrant is currently at a medical checkpoint.
     * @return Boolean determining if the entrant is at an MC.
     */
    public boolean getAtMC() {
        return atMC;
    }

    /**
     * Sets if an entrant is at a medical checkpoint.
     * @param atMC Whether the entrant is currently at an MC or not.
     */
    public void setAtMC(boolean atMC) {
        this.atMC = atMC;
    }
   
}
