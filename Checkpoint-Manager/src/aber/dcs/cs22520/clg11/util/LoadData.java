/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.util;

import aber.dcs.cs22520.clg11.model.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author connor
 */
public class LoadData {
    
    private Datastore comp;
    
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
        } else if (type.equals(Datatype.ENTRANT)){
            System.out.println("Please enter an entrants filename:");
        }
        
                    f = new File(scan.next());

        while (!f.exists()) {

            System.out.println("File does not exist. Please try again:");
            f = new File(scan.next());

        }
        
        readValues = readIn(f);

        if (type.equals(Datatype.NODE)) {

            for (String [] newItem : readValues) {
                
                loadNodes(newItem);
                
            }
            
            displayNodes();

        } else if (type.equals(Datatype.COURSE)) {

            for (String [] newItem : readValues) {
                
                loadCourses(newItem);
                
            }
            
            displayCourses();

        } else {

            for (String [] newItem : readValues) {
                
                loadEntrants(newItem);
                
            }
            
            displayEntrants();
        }
    }

    /**
     * Reads in the contents of internal/external dictionary files and places
     * the contents into a Vector which is then returned, and used to populate
     * the {@link aber.dcs.clg11.wordladder.model.Graph}.
     *
     * @param fileName The directory of the file to be parsed.
     * @return Vector containing the contents of the parsed file.
     */
    public ArrayList<String[]> readIn(File fileName) {
        
        ArrayList<String[]> values = new ArrayList<>();

        try {

            //Create File IO objects
            FileReader fileReader;
            BufferedReader bufferedReader;

            //Initialise the File IO objects, passing in the selected file path
            fileReader = new FileReader(fileName);
            bufferedReader = new BufferedReader(fileReader);

            //Initialise local variable used to store the current line being read in
            String line;

            //While there are still lines to read in from the file (i.e. read in every line in the file)
            while ((line = bufferedReader.readLine()) != null) {

                String[] details = line.split(" ");
                values.add(details);

            }

            //Once completed, safely close the file reader
            bufferedReader.close();
            return values;

            //If any IO exceptions occur...
        } catch (IOException iOE) {

            System.out.println("WE GOT A PROBLEM...");
            iOE.printStackTrace();
            return null;
        }

    }

    public void loadCourses(String[] newLine) {

        Course newCourse = new Course();

        newCourse.setCourseID(newLine[0].charAt(0));
        newCourse.setCourseLength(Integer.parseInt(newLine[1]));

        for (int i = 2; i < (newLine.length); i++) {

            for (Node n : comp.getNodes()) {

                int test1 = n.getNumber();
                int test2 = Integer.parseInt(newLine[i]);

                if (test1 == test2 && (n.getType().equals("CP") || n.getType().equals("MC"))) {

                    newCourse.addNewNode(n);
                }
            }

        }

        comp.getCourses().add(newCourse);

    }

    public void loadNodes(String[] newLine) {

        try {

            Node newNode = new Node();

            newNode.setNumber(Integer.parseInt(newLine[0]));
            newNode.setType(newLine[1]);

            comp.getNodes().add(newNode);

        } catch (Exception e) {

            System.out.println("Cannot parse Node. - " + e);
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

            System.out.println("Cannot parse Entrant. - " + e);
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
    
    public void writeTime(File writeFile, String timeStamp) {
        
        try {
 
			// if file doesnt exists, then create it
			if (!writeFile.exists()) {
				writeFile.createNewFile();
			}
 
			FileWriter fw = new FileWriter(writeFile.getAbsoluteFile(), true);
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write(timeStamp);
			bw.close();
 
			System.out.println("Done");
 
		} catch (IOException e) {
			e.printStackTrace();
		}
    }
}