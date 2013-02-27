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
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Connor Luke Goddard (clg11)
 */
public class ProcessData {

    Datastore data = new Datastore();

    public ProcessData() {
    }

    public ProcessData(Datastore newData) {

        this.data = newData;

    }

    public void processNewTime(int nodeNo, int entrantNo) {
        
        boolean isUpdated = false;

        for (Entrant e : data.getEntrants()) {

            if (e.getNumber() == entrantNo) {

                for (Course c : data.getCourses()) {

                    if (c.getCourseID() == e.getCourseID()) {

                        for (int i = 0; i < c.getCourseNodes().size(); i++) {

                            if (i > (e.getCurrentProgress() - 1) && c.getCourseNodes().get(i).getNumber() == nodeNo && !isUpdated) {

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

        }


    }
    
    public void checkNextNode(ArrayList<Node> courseNodes, int currentNodeProgress, int newNode) {
        
       boolean nodeFound = false; 
        
       for (int i = currentNodeProgress; i < courseNodes.size(); i++) {
          
          if (courseNodes.get(i).getNumber() == newNode) {
            
            //Entrant at the correct node
          //  System.out.println("THIS CAN BE DONE - " + i + " / " + courseNodes.get(i).getNumber());
            nodeFound = true;
            
        } /*else {
            
           //Entrant on the wrong path
            System.out.println("THIS CANNOT BE DONE - " + i + " / " + courseNodes.get(i).getNumber());
        } */
        
           
       }
       
       if (!nodeFound) {
           
           System.out.println("ENTRANT HAS GONE THE WRONG WAY");
       } else {
           
           System.out.println("ENTRANT HAS GONE THE RIGHT WAY");   
       }
  
    }

    public void getCourse() {

        System.out.println("TWAT");

        for (int i = 0; i < data.getCourses().size(); i++) {

            System.out.println(data.getCourses().get(i).getCourseID());
        }

    }

    public void getTimes() {

        try {

            //Create File IO objects
            FileReader fileReader;
            BufferedReader bufferedReader;

            //Initialise the File IO objects, passing in the selected file path
            fileReader = new FileReader("times.txt");
            bufferedReader = new BufferedReader(fileReader);

            //Initialise local variable used to store the current line being read in
            String line;


            //While there are still lines to read in from the file (i.e. read in every line in the file)
            while ((line = bufferedReader.readLine()) != null) {

                String[] details = line.split(" ");

                processNewTime(Integer.parseInt(details[1]), Integer.parseInt(details[2]));

            }

            //Once completed, safely close the file reader
            bufferedReader.close();

            //If any IO exceptions occur...
        } catch (IOException iOE) {

            System.out.println("WE GOT A PROBLEM...");
            iOE.printStackTrace();
        }

    }
}
