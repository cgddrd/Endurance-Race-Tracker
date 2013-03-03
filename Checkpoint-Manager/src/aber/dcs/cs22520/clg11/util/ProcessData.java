/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.util;

import aber.dcs.cs22520.clg11.model.Course;
import aber.dcs.cs22520.clg11.model.Datastore;
import aber.dcs.cs22520.clg11.model.Entrant;
import aber.dcs.cs22520.clg11.model.Node;
import java.io.File;
import java.util.ArrayList;

/**
 *
 * @author Connor Luke Goddard (clg11)
 */
public class ProcessData {

    private Datastore data;
    private FileIO fileIO = new FileIO();

    public ProcessData() {
    }

    public ProcessData(Datastore newData) {

        this.data = newData;

    }
    
    public void resetEntrantProgress() {
        
        for (Entrant e : data.getEntrants()) {
            
            e.setCurrentProgress(0);
        }
        
         fileIO.addActivityLog("All entrant details successfully reset."); 
    }

    public void processNewTime(String timeDelimiter, int nodeNo, int entrantNo) {

        boolean isUpdated = false;
        Entrant e = obtainEntrant(entrantNo);

        if (timeDelimiter.equals("I")) {

            excludeEntrant(entrantNo);
            System.out.println("ENTRANT EXCLUDED - " + entrantNo);
            fileIO.addActivityLog("Entrant no: " + entrantNo + " successfully excluded."); 

        } else if (!e.getIsExcluded()) {

            ArrayList<Node> courseNodes = obtainCourseNodes(e);
            for (int i = 0; i < courseNodes.size(); i++) {

                if (i > (e.getCurrentProgress() - 1) && courseNodes.get(i).getNumber() == nodeNo && !isUpdated) {

                    if (timeDelimiter.equals("A")) {

                        isUpdated = true;
                        System.out.println("ENTRANT PARTIALLY UPDATED: Entrant No: " + entrantNo + ", Node: " + nodeNo + " Progress: " + e.getCurrentProgress());
                        fileIO.addActivityLog("Entrant no: " + entrantNo + " has arrived at medical checkpoint " + nodeNo + "."); 
                        
                    } else {

                        //If the read in node from time file is further along the course than the current progress,
                        // update the current progress. 
                        e.setCurrentProgress((i + 1));
                        
                        if (e.getCurrentProgress() >= courseNodes.size()) {
                            
                            System.out.println("CURRENT PROGRESS = " + e.getCurrentProgress() + ", COURSE NODES SIZE = " + courseNodes.size());
                            e.setIsFinished(true);
                            fileIO.addActivityLog("Entrant no: " + e.getNumber() + " has sucessfully finished the course."); 
                        }
                        
                        isUpdated = true;

                        System.out.println("ENTRANT UPDATED: Entrant No: " + entrantNo + ", Node: " + nodeNo + " Progress: " + e.getCurrentProgress());
                        fileIO.addActivityLog("Entrant no: " + entrantNo + " has been updated to checkpoint " + nodeNo + "."); 

                    }
                }
            }
        }
    }

    public Entrant obtainEntrant(int requiredEntrant) {

        for (Entrant e : data.getEntrants()) {

            if (e.getNumber() == requiredEntrant) {

                return e;
            }

        }

        return null;

    }

    public ArrayList<Node> obtainCourseNodes(Entrant selectedEntrant) {

        for (Course c : data.getCourses()) {

            if (c.getCourseID() == selectedEntrant.getCourseID()) {

                return c.getCourseNodes();
            }

        }

        return null;
    }

    public void excludeEntrant(int entrantNo) {

        for (Entrant e : data.getEntrants()) {

            if (e.getNumber() == entrantNo) {

                e.setIsExcluded(true);
            }

        }

    }
    
    public void processNextNode(ArrayList<Node> courseNodes, Entrant selectedEntrant, int newNode, String time) {
        
        int nextNodeIndex = selectedEntrant.getCurrentProgress();

        if (selectedEntrant.getCurrentProgress() < courseNodes.size() && !selectedEntrant.getIsExcluded()) {

            if (courseNodes.get(nextNodeIndex).getNumber() != newNode) {

                System.out.println("ENTRANT HAS GONE THE WRONG WAY - " + courseNodes.get(nextNodeIndex).getNumber() + " / " + newNode);
                fileIO.writeFile(new File("../files/times.txt"), "I " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");

            } else {

                System.out.println("ENTRANT HAS GONE THE RIGHT WAY - " + courseNodes.get(nextNodeIndex).getNumber() + " / " + newNode);
                fileIO.writeFile(new File("../files/times.txt"), "T " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");
            }

        } else {
            
            System.out.println("ENTRANT FINISHED!!");
            
        }

    }
    
    public void processNextNode(ArrayList<Node> courseNodes, Entrant selectedEntrant, int newNode, String mcType, String time) {

        int nextNodeIndex = selectedEntrant.getCurrentProgress();

        if (selectedEntrant.getCurrentProgress() < courseNodes.size() && !selectedEntrant.getIsExcluded()) {

            if (courseNodes.get(nextNodeIndex).getNumber() != newNode) {

                fileIO.addActivityLog("Submitted checkpoint incorrect for course. (Entrant No: " + selectedEntrant.getNumber() + ")"); 
                System.out.println("ENTRANT HAS GONE THE WRONG WAY - " + courseNodes.get(nextNodeIndex).getNumber() + " / " + newNode);
                fileIO.writeFile(new File("../files/times.txt"), "I " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");

            } else {
                
                if (mcType.equals("Arriving")) {
                   
                    fileIO.addActivityLog("New MC arrival time submitted. (Entrant No: " + selectedEntrant.getNumber() + ")"); 
                    fileIO.writeFile(new File("../files/times.txt"), "A " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");
                    
                } else {
                    
                    fileIO.addActivityLog("New MC departure time submitted. (Entrant No: " + selectedEntrant.getNumber() + ")"); 
                    fileIO.writeFile(new File("../files/times.txt"), "D " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");
                }
            }

        } else {
            
            System.out.println("ENTRANT FINISHED!!");
            
        }

    }

    public void getTimes() {

        ArrayList<String[]> times = fileIO.readIn(new File("../files/times.txt"));

        for (String[] newTime : times) {

            processNewTime(newTime[0], Integer.parseInt(newTime[1]), Integer.parseInt(newTime[2]));
            //System.out.println("FROM FILE: Node = " + Integer.parseInt(newTime[1]) + ", Entrant = " + Integer.parseInt(newTime[2]));

        }
        
        fileIO.addActivityLog("Time logs file loaded successfully (times.txt)");
    }

    public ArrayList<Node> getEntrantCourseNodes(Entrant e) {

        ArrayList<Node> nodes = new ArrayList();

        for (Course c : data.getCourses()) {

            if (c.getCourseID() == e.getCourseID()) {

                nodes = c.getCourseNodes();
            }

        }

        return nodes;
    }
    
}