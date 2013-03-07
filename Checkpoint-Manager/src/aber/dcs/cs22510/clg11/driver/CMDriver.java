package aber.dcs.cs22510.clg11.driver;

import aber.dcs.cs22510.clg11.util.LoadData;
import aber.dcs.cs22510.clg11.gui.GUIFrame;
import aber.dcs.cs22510.clg11.model.Datastore;
import aber.dcs.cs22510.clg11.model.Datatype;

/**
 * Bootstrap class - Initialises the application.
 *
 * @author Connor Goddard (clg11) 
 * Copyright: Aberystwyth University, Aberystwyth.
 */
public class CMDriver {

    /**
     * The main method used to initialise the main application.
     *
     * @param args The arguments passed on initialisation.
     */
    public static void main(String[] args) {

        //Instantiate new Datastore object that will be shared by other classes.
        Datastore comp = new Datastore();
        
        //Instantiate new Datastore object that will be shared by other classes.
        LoadData load = new LoadData(comp);
        
        //Load input files into Datastore class (nodes, tracks and courses).
        load.loadFiles(Datatype.NODE);
        load.loadFiles(Datatype.COURSE);
        load.loadFiles(Datatype.ENTRANT);

        //Once loading via textual interface is complete, display GUI.
        new GUIFrame(comp, load);

    }
}
