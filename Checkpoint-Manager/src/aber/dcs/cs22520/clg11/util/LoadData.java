/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.util;

import aber.dcs.cs22520.clg11.model.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.channels.FileLock;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author connor
 */
public class LoadData {

    private Datastore comp;
    private FileIO fileIO = new FileIO();

    public LoadData(Datastore comp) {

        this.comp = comp;

    }

    public void loadFiles(Datatype type) {

        Scanner scan = new Scanner(System.in);
        File f;
        ArrayList<String[]> readValues;

        if (type.equals(Datatype.NODE)) {
            System.out.println("Please enter a node filename:");
        } else if (type.equals(Datatype.COURSE)) {
            System.out.println("Please enter a course filename:");
        } else if (type.equals(Datatype.ENTRANT)) {
            System.out.println("Please enter an entrants filename:");
        }

        f = new File(scan.next());

        while (!f.exists()) {

            System.out.println("File does not exist. Please try again:");
            f = new File(scan.next());

        }

        readValues = fileIO.readIn(f);

        if (type.equals(Datatype.NODE)) {

            for (String[] newItem : readValues) {

                loadNodes(newItem);

            }

            displayNodes();
            fileIO.addActivityLog("Nodes file loaded successfully (nodes.txt)");

        } else if (type.equals(Datatype.COURSE)) {

            for (String[] newItem : readValues) {

                loadCourses(newItem);

            }

            displayCourses();
            fileIO.addActivityLog("Courses file loaded successfully (courses.txt)");

        } else {

            for (String[] newItem : readValues) {

                loadEntrants(newItem);

            }

            displayEntrants();
            fileIO.addActivityLog("Entrants file loaded successfully (courses.txt)");
        }
    }

    
    public void loadCourses(String[] newLine) {
        
        try {

        Course newCourse = new Course();

        newCourse.setCourseID(newLine[0].charAt(0));
        newCourse.setCourseLength(Integer.parseInt(newLine[1]));

        for (int i = 2; i < (newLine.length); i++) {

            for (Node n : comp.getNodes()) {

                int origNodeNo = n.getNumber();
                int courseNodeNo = Integer.parseInt(newLine[i]);

                if (origNodeNo == courseNodeNo && (n.getType().equals("CP") || n.getType().equals("MC"))) {

                    newCourse.addNewNode(n);
                }
            }

        }

        comp.getCourses().add(newCourse);
        
        } catch (Exception e) {
            
           fileIO.addActivityLog("ERROR - Cannot create new course object (" + newLine[0] +")"); 
        }

    }

    public void loadNodes(String[] newLine) {

        try {

            Node newNode = new Node();

            newNode.setNumber(Integer.parseInt(newLine[0]));
            newNode.setType(newLine[1]);

            comp.getNodes().add(newNode);

        } catch (Exception e) {

            fileIO.addActivityLog("ERROR - Cannot create new node object (" + Integer.parseInt(newLine[0]) + " / " + newLine[1] + ")");
        }

    }

    public void loadEntrants(String[] newLine) {

        try {

            Entrant newEntrant = new Entrant();

            newEntrant.setNumber(Integer.parseInt(newLine[0]));
            newEntrant.setCourseID(newLine[1].charAt(0));
            newEntrant.setFirstName(newLine[2]);
            newEntrant.setLastName(newLine[3]);

            comp.getEntrants().add(newEntrant);

        } catch (Exception e) {

            fileIO.addActivityLog("ERROR - Cannot create new entrant object (" + Integer.parseInt(newLine[0]) + " / " + newLine[1] + " / " + newLine[2] + " " + newLine[3] + ")");
        }

    }

    public void displayCourses() {

        for (int i = 0; i < comp.getCourses().size(); i++) {

            System.out.println(comp.getCourses().get(i).getCourseID());
            System.out.println(comp.getCourses().get(i).getCourseLength());
            System.out.println("Course Nodes:");

            for (Node n : comp.getCourses().get(i).getCourseNodes()) {

                System.out.println(n.getNumber() + " - " + n.getType());

            }

            System.out.println("******************\n");
        }
    }

    public void displayNodes() {

        for (int i = 0; i < comp.getNodes().size(); i++) {

            System.out.println(comp.getNodes().get(i).getNumber() + " - " + comp.getNodes().get(i).getType());
            System.out.println("******************\n");
        }
    }

    public void displayEntrants() {

        for (int i = 0; i < comp.getEntrants().size(); i++) {

            System.out.println(comp.getEntrants().get(i).getNumber() + " - " + comp.getEntrants().get(i).getCourseID() + " - " + comp.getEntrants().get(i).getFullName());
            System.out.println("******************\n");
        }
    }
}