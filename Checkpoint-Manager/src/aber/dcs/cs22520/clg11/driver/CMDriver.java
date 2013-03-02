/*
 * This is a test!!
 * this is test 2...
 */
package aber.dcs.cs22520.clg11.driver;

import aber.dcs.cs22510.clg11.gui.GUIFrame;
import aber.dcs.cs22520.clg11.model.Datastore;
import aber.dcs.cs22520.clg11.model.Datatype;
import aber.dcs.cs22520.clg11.model.Node;
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
        
    //    ProcessData proc = new ProcessData(comp, load);
        
      /*  proc.getTimes();
        
        if (!comp.getEntrants().get(1).getIsExcluded()) {

            proc.checkNextNode(comp.getCourses().get(0).getCourseNodes(), comp.getEntrants().get(1), 4, "11:23");
        
        System.out.println("COURSE NODES:");
        
        for (Node n : comp.getCourses().get(0).getCourseNodes()) {
            
            
             System.out.println(n.getNumber());
            
            }
        
        } */
        
        GUIFrame test = new GUIFrame(comp, load);
         
    } 
}
