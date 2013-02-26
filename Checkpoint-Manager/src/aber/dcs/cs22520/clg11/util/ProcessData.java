/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22520.clg11.util;

import aber.dcs.cs22520.clg11.model.Datastore;

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
    
    public void processNewTime() {
    
        
    }
    
    public void getCourse() {
        
        System.out.println("TWAT");
        
        for (int i = 0; i < data.getCourses().size(); i++) {
            
            System.out.println(data.getCourses().get(i).getCourseID());
        }
        
    }
    
}
