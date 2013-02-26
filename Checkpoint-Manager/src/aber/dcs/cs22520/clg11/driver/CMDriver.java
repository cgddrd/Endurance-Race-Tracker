/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.driver;

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
       
        LoadData read = new LoadData();
        
        read.readIn("nodes.txt", Datatype.NODE);
        read.displayNodes();
        
        read.readIn("courses.txt", Datatype.COURSE);
        read.displayCourses();
        
        read.readIn("entrants.txt", Datatype.ENTRANT);
        read.displayEntrants();
        
        
        
    }
}
