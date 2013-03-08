package aber.dcs.cs22510.clg11.util;

import aber.dcs.cs22510.clg11.model.Course;
import aber.dcs.cs22510.clg11.model.Datastore;
import aber.dcs.cs22510.clg11.model.Entrant;
import aber.dcs.cs22510.clg11.model.Node;
import java.io.File;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Responsible for updating the internal record of entrant progress (based on
 * data read in from "times.txt") and for processing new time logs submitted by
 * a user. Has access to the shared
 * {@link aber.dcs.cs22510.clg11.model.Datastore} class to allow processing and
 * manipulation of the data collections.
 *
 * @author Connor Luke Goddard (clg11) Copyright: Aberystwyth University,
 * Aberystwyth.
 */
public class ProcessData {

    private Datastore data;
    private FileIO fileIO;
    private String lastLoggedTime = null;

    /**
     * Allows access to the file read/write facilities.
     */
    // private FileIO fileIO = new FileIO();
    public ProcessData() {
    }

    /**
     * Constructor to instantiate a new ProcessData. Takes the shared data store
     * object created in {@link aber.dcs.cs22510.clg11.driver.CMDriver} as a
     * parameter to allow accessed to the lists of nodes/entrants/courses loaded
     * in.
     *
     * @param newData Datastore object created in CMDriver.
     */
    public ProcessData(Datastore newData, FileIO newFileIO) {

        this.data = newData;
        this.fileIO = newFileIO;

    }

    /**
     * Returns the time value of the last read-in time log.
     *
     * @return The last time value of the "times.txt" file.
     */
    public String getLastLoggedTime() {
        return lastLoggedTime;
    }

    /**
     * Attempts to fetch a specified entrant from the internal collection of
     * entrants.
     *
     * @param requiredEntrant The number of the required entrant.
     * @return The specified Entrant object, or NULL.
     */
    public Entrant obtainEntrant(int requiredEntrant) {

        for (Entrant e : data.getEntrants()) {

            if (e.getNumber() == requiredEntrant) {

                return e;
            }

        }

        return null;
    }

    /**
     * Attempts to fetch the collection of course nodes that make up the course
     * that a specified entrant is registered for.
     *
     * @param selectedEntrant The number of the required entrant.
     * @return The collection of course nodes, or NULL.
     */
    public ArrayList<Node> obtainEntrantCourseNodes(Entrant selectedEntrant) {

        //Loop through all the stored courses.
        for (Course c : data.getCourses()) {

            //If the current course matches the entrant's course.
            if (c.getCourseID() == selectedEntrant.getCourseID()) {

                //Return the collection of nodes for that course.
                return c.getCourseNodes();
            }

        }

        //Otherwise if nothing is found, return NULL.
        return null;
    }

    /**
     * Processes each line read in from the "times.txt" file to update the
     * internal record of entrant's progress. This method is crucial to ensure
     * that any time log updates created by any other running versions of the
     * checkpoint manager are recorded in the internal entrant record within
     * this application.
     *
     * @param timeDelimiter The character symbol used to represent the status of
     * the particular time log.
     * @param nodeNo The number of the node the time log was recorded at.
     * @param entrantNo The number of the entrant that was recorded.
     */
    public void processNewTime(String timeDelimiter, int nodeNo, int entrantNo) {

        //Boolean used to determine whether this particular time log has been processed.
        boolean isUpdated = false;

        //Obtain the required entrant from the internal collection of entrants.
        Entrant currentEntrant = obtainEntrant(entrantNo);

        //Check if the time log dictates that the entrant should be excluded.
        if (timeDelimiter.equals("I")) {

            //If so exclude the entrant.
            excludeEntrant(entrantNo);

            //Log this activity in the log file ("log.txt");
            fileIO.addActivityLog("Entrant no: " + entrantNo + " successfully excluded.");

            /*
             * Otherwise if they shouldn't be excluded,
             * check to see if the entrant has already been excluded.
             */
        } else if (!currentEntrant.getIsExcluded()) {

            ArrayList<Node> courseNodes = obtainEntrantCourseNodes(currentEntrant);

            //Loop through all the nodes that make up the course the entrant is on.
            for (int i = 0; i < courseNodes.size(); i++) {

                /*
                 * Check that the current progress of the entrant < the index of 
                 * the current node in the array (to prevent nodes the entrant has 
                 * already passed being used again), and the current node equals
                 * the node number of the current time log.
                 */
                if (i > (currentEntrant.getCurrentProgress() - 1) && courseNodes.get(i).getNumber() == nodeNo && !isUpdated) {

                    /*
                     * If the entrant has ARRIVED at a medical checkpoint, 
                     * their progress should not be incrememted as they are 
                     * now waiting at the MC
                     */
                    if (timeDelimiter.equals("A")) {

                        //Just prevent this particular time log being processed any further.
                        currentEntrant.setAtMC(true);
                        isUpdated = true;
                        
                        /*
                         * Otherwise, if they are DEPARTING from a MC or they
                         * have just arrived at a normal checkpoint, then their
                         * progress needs to be recorded and incremented.
                         */
                    } else {

                        /*
                         * If the read in node from time file is further along 
                         * the course than the current progress,
                         * update the current progress. 
                         */
                        currentEntrant.setCurrentProgress((i + 1));
                        currentEntrant.setAtMC(false);


                        /*
                         * Check to see if the entrant has now completed
                         * their course.
                         */
                        if (currentEntrant.getCurrentProgress() >= courseNodes.size()) {

                            //Log that they have finished.
                            currentEntrant.setIsFinished(true);

                            //Log this activity in the log file ("log.txt");
                            fileIO.addActivityLog("Entrant no: " + currentEntrant.getNumber() + " has sucessfully finished the course.");
                        }

                        isUpdated = true;

                    }
                }
            }
        }
    }

    /**
     * Updates a particular Entrant object to log the fact that they have been
     * excluded from their race.
     *
     * @param entrantNo The number of the required entrant.
     */
    public void excludeEntrant(int entrantNo) {

        for (Entrant e : data.getEntrants()) {

            if (e.getNumber() == entrantNo) {

                e.setIsExcluded(true);
            }

        }

    }

    /**
     * Processes a new time log submitted by the user by determining whether the
     * entrant is on the correct path or not and updates the "times.txt" file
     * with the resulting time log.
     *
     * @param courseNodes The collection of nodes that make up the course the
     * current entrant is registered for.
     * @param selectedEntrant The current entrant being processed.
     * @param newNode The newly submitted node that the entrant has arrived at.
     * @param time The inputted time of the entrant's arrival at the CP.
     */
    public String processTimeLog(ArrayList<Node> courseNodes, Entrant selectedEntrant, int newNode, String time) {

        //Obtain the current progress of the entrant (i.e. the index of the array).
        int nextNodeIndex = selectedEntrant.getCurrentProgress();
        String result = null;

        //Check that the entrant has not already finished, or been excluded.
        if (selectedEntrant.getCurrentProgress() >= courseNodes.size()) {

            result = " Entrant " + selectedEntrant.getNumber() + " successfully completed their course.";

        } else if (selectedEntrant.getIsExcluded()) {

            result = " Entrant " + selectedEntrant.getNumber() + " has been excluded from their course.";

        } else {

            /*
             * Check whether the next node in the array (i.e. the next node that the 
             * entrant SHOULD have reached) is actually the node sumbitted.
             */
            if (courseNodes.get(nextNodeIndex).getNumber() != newNode) {

                result = "Entrant " + selectedEntrant.getNumber() + 
                        " has gone the INCORRECT way. (Expected node: " + courseNodes.get(nextNodeIndex).getNumber() + ")";

                /*
                 * If they do not match, the entrant has gone the wrong way.
                 * Append this new time log with the 'I' time delimter to the 
                 * times file ("times.txt").
                 */
                fileIO.writeFile(new File("../files/times.txt"), "I " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");

            } else {
                
                result = "Entrant " + selectedEntrant.getNumber() + 
                        " has gone the CORRECT way. (Expected node: " + courseNodes.get(nextNodeIndex).getNumber() + ")";

                /*
                 * Otherwise if they do  match, the entrant has gone the right way.
                 * Append this new time log with the 'T' time delimter to the 
                 * times file ("times.txt").
                 */
                fileIO.writeFile(new File("../files/times.txt"), "T " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");
            }

        }

        return result;

    }

    /**
     * Processes a new time log submitted by the user by determining whether the
     * entrant is on the correct path or not and updates the "times.txt" file
     * with the resulting time log (Processes medical checkpoints).
     *
     * @param courseNodes The collection of nodes that make up the course the
     * current entrant is registered for.
     * @param selectedEntrant The current entrant being processed.
     * @param newNode The newly submitted node that the entrant has arrived at.
     * @param mcType Whether the entrant was arriving or departing from the MC.
     * @param time The inputted time of the entrant's arrival at the CP.
     */
    public String processTimeLog(ArrayList<Node> courseNodes, Entrant selectedEntrant, int newNode, String mcType, String time) {

        int nextNodeIndex = selectedEntrant.getCurrentProgress();
        String result = null;

        //Check that the entrant has not already finished, or been excluded.
        if (selectedEntrant.getCurrentProgress() >= courseNodes.size()) {

            result = " Entrant " + selectedEntrant.getNumber() + " successfully completed their course.";

        } else if (selectedEntrant.getIsExcluded()) {

            result = " Entrant " + selectedEntrant.getNumber() + " has been excluded from their course.";

        } else {

            if (courseNodes.get(nextNodeIndex).getNumber() != newNode) {

                fileIO.addActivityLog("Submitted checkpoint incorrect for course. (Entrant No: " + selectedEntrant.getNumber() + ")");
                
                result = "Entrant " + selectedEntrant.getNumber() + 
                        " has gone the wrong way. (Expected node: " + courseNodes.get(nextNodeIndex).getNumber() + ")";
                        
                fileIO.writeFile(new File("../files/times.txt"), "I " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");

            } else {

                /*
                 * If they do match, the entrant has gone the right way.
                 * Determine whether the entrant was arriving at, or departing
                 * from the MC and update the time log file ("times.txt") 
                 * accordingly.
                 */
                if (mcType.equals("Arriving")) {

                    fileIO.addActivityLog("New MC arrival time submitted. (Entrant No: " + selectedEntrant.getNumber() + ")");
                    fileIO.writeFile(new File("../files/times.txt"), "A " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");

                } else {

                    fileIO.addActivityLog("New MC departure time submitted. (Entrant No: " + selectedEntrant.getNumber() + ")");
                    fileIO.writeFile(new File("../files/times.txt"), "D " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");
                }
            }

        }

        return result;

    }

    /**
     * Obtains all the times from the time log file ("times.txt") before
     * processing each time log.
     */
    public boolean getTimes() {

        //Obtain a collection of ALL the time logs read in from the "times.txt" file.
        File timesFile = new File("../files/times.txt");

        if (timesFile.exists()) {

            ArrayList<String[]> times = fileIO.readIn(timesFile, true);

            //For every time log read in from the file...
            for (String[] newTime : times) {

                //... process this time log and update the internal record of entrants.
                processNewTime(newTime[0], Integer.parseInt(newTime[1]), Integer.parseInt(newTime[2]));

                this.lastLoggedTime = newTime[3];

            }

            //Log this activity in the log file ("log.txt");
            fileIO.addActivityLog("Time logs file loaded successfully (times.txt)");

            return true;

        }

        return false;
    }

    /**
     * Compares the time of the last read-in time log, with the new time being
     * submitted to check that the user is not entering a time in the past.
     *
     * @param oldTimeString The last time value read-in from "times.txt".
     * @param newTimeString The new time value being submitted by the user.
     * @return A boolean determining if the new time value is in the past.
     */
    public boolean compareTimes(String oldTimeString, String newTimeString) {

        SimpleDateFormat df = new SimpleDateFormat("HH:mm");

        Date lastRecordedTime;
        Date newTime;

        try {

            //Create new Date objects using the last logged, and new time values.
            lastRecordedTime = df.parse(oldTimeString);
            newTime = df.parse(newTimeString);

            //Check if the new time entered is before the last read-in time.
            if (df.format(lastRecordedTime).compareTo(df.format(newTime)) > 0) {

                //If so, then this cannot be allowed.
                
                //Log this activity in the log file ("log.txt");
                fileIO.addActivityLog("User attempted to enter new time value in the past. (New time: " + df.format(newTime) + ")");
                
                return true;
            }

        } catch (ParseException ex) {
            Logger.getLogger(ProcessData.class.getName()).log(Level.SEVERE, null, ex);
        }

        return false;
    }
}