/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.util;

import aber.dcs.cs22520.clg11.model.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


/**
 *
 * @author connor
 */
public class LoadData {
    
    private ArrayList<Course> courses = new ArrayList<>();
    private ArrayList<Node> nodes = new ArrayList<>();
    private ArrayList<Entrant> entrants = new ArrayList<>();
    
	/**
	 * Reads in the contents of internal/external dictionary files and places the contents into a Vector 
	 * which is then returned, and used to populate the {@link aber.dcs.clg11.wordladder.model.Graph}.
	 *
	 * @param fileName The directory of the file to be parsed.
	 * @return Vector containing the contents of the parsed file.
	 */;
    
	/**
	 * Reads in the contents of internal/external dictionary files and places the contents into a Vector 
	 * which is then returned, and used to populate the {@link aber.dcs.clg11.wordladder.model.Graph}.
	 *
	 * @param fileName The directory of the file to be parsed.
	 * @return Vector containing the contents of the parsed file.
	 */
	public void readIn(String fileName, Datatype type) {

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
                                
                                if (type == Datatype.COURSE) {
                                    
                                    loadCourses(details);
                                    
                                } else if (type == Datatype.ENTRANT) {
                                    
                                    loadEntrants(details);
                                           
                                } else if (type == Datatype.NODE) {
                                    
                                    loadNodes(details);
                                       
                                }

			}

			//Once completed, safely close the file reader
			bufferedReader.close();

		//If any IO exceptions occur...
		} catch (IOException iOE) {
			
			System.out.println("WE GOT A PROBLEM...");
		}

	}
        
        
    public void loadCourses(String[] newLine) {
        
        Course newCourse = new Course();
        
        newCourse.setCourseID(newLine[0].charAt(0));
        newCourse.setCourseLength(Integer.parseInt(newLine[1]));
        
        for (int i = 2; i < (newLine.length); i++) {
            
            for (Node n : nodes) {
                
                int test1 = n.getNumber();
                int test2 = Integer.parseInt(newLine[i]);
                
                if (test1 == test2) {
                    
                    newCourse.addNewNode(n);
                }
            }
            
        }
        
        courses.add(newCourse);
        
    }
    
    public void loadNodes(String[] newLine) {
        
       try {
        
        Node newNode = new Node();
        
        newNode.setNumber(Integer.parseInt(newLine[0]));
        newNode.setType(newLine[1]);
        
        nodes.add(newNode);
        
       } catch (Exception e) {
           
           System.out.println("Cannot parse Node. - " + e);
       }
        
    }
    
    public void loadEntrants(String[] newLine) {
        
       try {
        
        Entrant newEntrant = new Entrant();
        
        newEntrant.setNumber(Integer.parseInt(newLine[0]));
        newEntrant.setCourseID(newLine[0].charAt(0));
        newEntrant.setFirstName(newLine[1]);
        newEntrant.setLastName(newLine[2]);
        
        entrants.add(newEntrant);
        
       } catch (Exception e) {
           
           System.out.println("Cannot parse Entrant. - " + e);
       }
        
    }
    
    public void displayCourses() {
        
        for (int i = 0; i < courses.size(); i++) {
            
            System.out.println(courses.get(i).getCourseID());
            System.out.println(courses.get(i).getCourseLength());
            System.out.println("Course Nodes:");
            
            for (Node n : courses.get(i).getCourseNodes()) {
                
                System.out.println(n.getNumber() + " - " + n.getType());
                
            }
            
            System.out.println("******************\n");
        }
    }
    
    public void displayNodes() {
        
        for (int i = 0; i < nodes.size(); i++) {
            
            System.out.println(nodes.get(i).getNumber() + " - " + nodes.get(i).getType());
            System.out.println("******************\n");
        }
    }
    
    public void displayEntrants() {
        
        for (int i = 0; i < entrants.size(); i++) {
            
            System.out.println(entrants.get(i).getNumber() + " - " + entrants.get(i).getCourseID() + " - " + entrants.get(i).getFullName());
            System.out.println("******************\n");
        }
    }
}