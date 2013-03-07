package aber.dcs.cs22510.clg11.util;

import aber.dcs.cs22510.clg11.model.*;
import java.io.File;
import java.util.ArrayList;

/**
 * Responsible for loading crucial, preliminary data files into the system using
 * a textual interface before the GUI is loaded.
 *
 * @author Connor Luke Goddard (clg11) Copyright: Aberystwyth University,
 * Aberystwyth.
 */
public class LoadData {

    private Datastore data;
    private FileIO fileIO;

    /**
     * Constructor to instantiate a new LoadData. Takes the shared data store
     * object created in {@link aber.dcs.cs22510.clg11.driver.CMDriver} as a
     * parameter to allow accessed to the lists of nodes/entrants/courses loaded
     * in.
     *
     * @param newData Datastore object created in CMDriver.
     */
    public LoadData(Datastore comp, FileIO newFileIO) {

        this.data = comp;
        this.fileIO = newFileIO;

    }

    /**
     * Prompts user for the file path of a specified file before attempting to
     * load the data into it's respective data collection.
     *
     * @param type ENUM denoting the type of data file (Node, Course or
     * Entrant).
     * @param fileName The path of the file to be loaded.
     */
    public void loadFiles(Datatype type, String fileName) {

        File f = new File(fileName);
        ArrayList<String[]> readValues;

        //Check if the file exists.
        if (!f.exists()) {

            //If it does not exist, inform the user.
            if (type == Datatype.NODE) {

                System.out.println("ERROR: Nodes file <" + fileName + "> does not exist.");

            } else if (type == Datatype.COURSE) {

                System.out.println("ERROR: Courses file <" + fileName + "> does not exist.");

            } else {
                
                System.out.println("ERROR: Entrants file <" + fileName + "> does not exist.");
                
            }

            System.out.println("Parameter format = <node path> <courses path> <entrants path>");
            System.exit(0);
        }
        

        //If the file does exist, read in the data from the file.
        readValues = fileIO.readIn(f, false);

        //Determine the type of data being loaded.
        if (type.equals(Datatype.NODE)) {

            for (String[] newItem : readValues) {

                //Load all the nodes from the read-in data.
                loadNodes(newItem);

            }

            displayNodes();

            //Log this activity in the log file ("log.txt");
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

    /**
     * Parses the data read-in from the "courses.txt" file and creates a new
     * {@link aber.dcs.cs22510.clg11.model.Course} object populated with the
     * read-in characteristics. This new Course object is then added to the
     * internal collection of Courses.
     *
     * @param courseData Collection of all course characteristics data read in
     * from "courses.txt".
     */
    public void loadCourses(String[] courseData) {

        try {

            //Create a new empty Course object.
            Course newCourse = new Course();

            //Set the course ID to the first element in the course data array.
            newCourse.setCourseID(courseData[0].charAt(0));

            //Set the course length to the second element in the course data array.
            newCourse.setCourseLength(Integer.parseInt(courseData[1]));

            //Loop through the REST (i=2) of the "read-in" course data array..
            for (int i = 2; i < (courseData.length); i++) {

                //Loop through all the course nodes stored internally.
                for (Node n : data.getNodes()) {

                    int origNodeNo = n.getNumber();

                    //Obtain the node number currently being parsed from the read in data.
                    int courseNodeNo = Integer.parseInt(courseData[i]);

                    /*
                     * If the node number read-in from file matches the current node,
                     * and the node is NOT a junction, add this node to the collection
                     * of nodes within the new Course object. 
                     */
                    if (origNodeNo == courseNodeNo && (n.getType().equals("CP") || n.getType().equals("MC"))) {

                        newCourse.addNewNode(n);
                    }
                }

            }

            /*
             * Once the new Course object has been populated with data,
             * add it to the collection of courses in Datastore.
             */
            data.getCourses().add(newCourse);

            //If an error occurs...
        } catch (Exception e) {

            //... log the error in the "log.txt" file.
            fileIO.addActivityLog("ERROR - Cannot create new course object (" + courseData[0] + ")");
        }

    }

    /**
     * Parses the data read-in from the "nodes.txt" file and creates a new
     * {@link aber.dcs.cs22510.clg11.model.Node} object populated with the
     * read-in characteristics. This new Node object is then added to the
     * internal collection of Nodes.
     *
     * @param nodeData Collection of all node characteristics data read in from
     * "nodes.txt".
     */
    public void loadNodes(String[] nodeData) {

        try {

            Node newNode = new Node();

            newNode.setNumber(Integer.parseInt(nodeData[0]));
            newNode.setType(nodeData[1]);

            data.getNodes().add(newNode);

        } catch (Exception e) {

            fileIO.addActivityLog("ERROR - Cannot create new node object (" + Integer.parseInt(nodeData[0]) + " / " + nodeData[1] + ")");
        }

    }

    /**
     * Parses the data read-in from the "entrants.txt" file and creates a new
     * {@link aber.dcs.cs22510.clg11.model.Entrant} object populated with the
     * read-in characteristics. This new Entrant object is then added to the
     * internal collection of Entrants.
     *
     * @param entrantData Collection of all node characteristics data read in
     * from "nodes.txt".
     */
    public void loadEntrants(String[] entrantData) {

        try {

            Entrant newEntrant = new Entrant();

            newEntrant.setNumber(Integer.parseInt(entrantData[0]));
            newEntrant.setCourseID(entrantData[1].charAt(0));
            newEntrant.setFirstName(entrantData[2]);
            newEntrant.setLastName(entrantData[3]);

            data.getEntrants().add(newEntrant);

        } catch (Exception e) {

            fileIO.addActivityLog("ERROR - Cannot create new entrant object (" + Integer.parseInt(entrantData[0]) + " / " + entrantData[1] + " / " + entrantData[2] + " " + entrantData[3] + ")");
        }

    }

    /**
     * Displays all {@link aber.dcs.cs22510.clg11.model.Courses} objects loaded
     * into the internal collection of courses to screen.
     */
    public void displayCourses() {

        for (int i = 0; i < data.getCourses().size(); i++) {

            System.out.println(data.getCourses().get(i).getCourseID());
            System.out.println(data.getCourses().get(i).getCourseLength());
            System.out.println("Course Nodes:");

            for (Node n : data.getCourses().get(i).getCourseNodes()) {

                System.out.println(n.getNumber() + " - " + n.getType());

            }

            System.out.println("******************\n");
        }
    }

    /**
     * Displays all {@link aber.dcs.cs22510.clg11.model.Entrants} objects loaded
     * into the internal collection of courses to screen.
     */
    public void displayNodes() {

        for (int i = 0; i < data.getNodes().size(); i++) {

            System.out.println(data.getNodes().get(i).getNumber() + " - " + data.getNodes().get(i).getType());
            System.out.println("******************\n");
        }
    }

    /**
     * Displays all {@link aber.dcs.cs22510.clg11.model.Entrants} objects loaded
     * into the internal collection of courses to screen.
     */
    public void displayEntrants() {

        for (int i = 0; i < data.getEntrants().size(); i++) {

            System.out.println(data.getEntrants().get(i).getNumber() + " - " + data.getEntrants().get(i).getCourseID() + " - " + data.getEntrants().get(i).getFullName());
            System.out.println("******************\n");
        }
    }
}