/*
 * This is a test!!
 */
package aber.dcs.cs22520.clg11.driver;

import aber.dcs.cs22520.clg11.model.Datastore;
import aber.dcs.cs22520.clg11.model.Datatype;
import aber.dcs.cs22520.clg11.util.*;

/**
 *
 * @author connor
 */
public class CMDriver {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        Datastore comp = new Datastore();
        LoadData load = new LoadData(comp);
       
        load.loadFiles(Datatype.NODE);
        load.loadFiles(Datatype.COURSE);
        load.loadFiles(Datatype.ENTRANT);
        
        ProcessData proc = new ProcessData(comp);
        
        proc.getCourse();
        
          
    }
}
