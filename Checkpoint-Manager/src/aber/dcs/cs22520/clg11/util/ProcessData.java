/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.util;

import aber.dcs.cs22520.clg11.model.Course;
import aber.dcs.cs22520.clg11.model.Datastore;
import aber.dcs.cs22520.clg11.model.Entrant;
import aber.dcs.cs22520.clg11.model.Node;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 *
 * @author Connor Luke Goddard (clg11)
 */
public class ProcessData {

    Datastore data;
    LoadData load;

    public ProcessData() {
        
    }

    public ProcessData(Datastore newData, LoadData newLoad) {

        this.data = newData;
        this.load = newLoad;

    }

    public void processNewTime(String timeDelimiter, int nodeNo, int entrantNo) {

        boolean isUpdated = false;
        Entrant e = obtainEntrant(entrantNo);
        
        if (timeDelimiter.equals("I")) {

            excludeEntrant(entrantNo);
            System.out.println("ENTRANT EXCLUDED - " + entrantNo);

        } else if (!e.getIsExcluded()) {

            ArrayList<Node> courseNodes = obtainCourseNodes(e);
            for (int i = 0; i < courseNodes.size(); i++) {

                if (i > (e.getCurrentProgress() - 1) && courseNodes.get(i).getNumber() == nodeNo && !isUpdated) {

                    if (timeDelimiter.equals("D")) {

                        isUpdated = true;
                        System.out.println("ENTRANT PARTIALLY UPDATED: Entrant No: " + entrantNo + ", Node: " + nodeNo + " Progress: " + e.getCurrentProgress());

                    } else {

                        //If the read in node from time file is further along the course than the current progress,
                        // update the current progress. 
                        e.setCurrentProgress((i + 1));
                        isUpdated = true;

                        System.out.println("ENTRANT UPDATED: Entrant No: " + entrantNo + ", Node: " + nodeNo + " Progress: " + e.getCurrentProgress());

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

    public void checkNextNode(ArrayList<Node> courseNodes, Entrant selectedEntrant, int newNode, String time) {
        
        int nextNodeIndex = selectedEntrant.getCurrentProgress();
                
        if (courseNodes.get(nextNodeIndex).getNumber() != newNode) {

            System.out.println("ENTRANT HAS GONE THE WRONG WAY - " + courseNodes.get(nextNodeIndex).getNumber() + " / " + newNode);
            load.writeTime(new File("times.txt"), "I " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");

        } else {

            System.out.println("ENTRANT HAS GONE THE RIGHT WAY - " + courseNodes.get(nextNodeIndex).getNumber() + " / " + newNode);
            load.writeTime(new File("times.txt"), "T " + newNode + " " + selectedEntrant.getNumber() + " " + time + "\n");
        }

    }

    public void getCourse() {

        System.out.println("TWAT");

        for (int i = 0; i < data.getCourses().size(); i++) {

            System.out.println(data.getCourses().get(i).getCourseID());
        }

    }

    public void getTimes() {
       
        ArrayList<String[]> times = load.readIn(new File("times.txt"));
        
        for (String[] newTime : times) {
            
           processNewTime(newTime[0], Integer.parseInt(newTime[1]), Integer.parseInt(newTime[2])); 
            
        }
    }
}