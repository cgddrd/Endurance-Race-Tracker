package aber.dcs.cs22510.clg11.driver;

import aber.dcs.cs22510.clg11.util.LoadData;
import aber.dcs.cs22510.clg11.gui.GUIFrame;
import aber.dcs.cs22510.clg11.model.Datastore;
import aber.dcs.cs22510.clg11.model.Datatype;
import aber.dcs.cs22510.clg11.util.FileIO;

/**
 * Bootstrap class - Initialises the application.
 *
 * @author Connor Goddard (clg11) Copyright: Aberystwyth University,
 * Aberystwyth.
 */
public class CMDriver {

    /**
     * The main method used to initialise the main application.
     *
     * @param args The file names for the data files.
     */
    public static void main(String[] args) {

        //Instantiate new Datastore object that will be shared by other classes.
        Datastore data = new Datastore();

        //Instantiate new Datastore object that will be shared by other classes.
        LoadData load = new LoadData(data);


        //Load input files into Datastore class (nodes, tracks and courses).     
       try {

            load.loadFiles(Datatype.NODE, args[0]);
            load.loadFiles(Datatype.COURSE, args[1]);
            load.loadFiles(Datatype.ENTRANT, args[2]);
            
            //Once loading via textual interface is complete, display GUI.
            new GUIFrame(data);

       } catch (IndexOutOfBoundsException eX) {
           
            System.out.println("ERROR: File parameters missing.");
            System.out.println("Parameter format = <node path> <courses path> <entrants path>");
       }

    }
}
