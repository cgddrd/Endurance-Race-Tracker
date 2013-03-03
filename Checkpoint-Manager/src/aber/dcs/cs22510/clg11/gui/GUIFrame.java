/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22510.clg11.gui;

import aber.dcs.cs22510.clg11.model.Datastore;
import aber.dcs.cs22510.clg11.util.LoadData;
import java.awt.Dimension;
import java.awt.Toolkit;
import javax.swing.JFrame;

/**
 *
 * @author Connor Luke Goddard (clg11)
 */
public class GUIFrame extends JFrame {
    
    private GUIPanel panel;
    
    
            
    public GUIFrame(Datastore newData, LoadData newLoad) {
        
                //Initialise and set up frame
		this.setTitle("Checkpoint Manager | Connor Goddard (clg11)");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);
                
                panel = new GUIPanel(newData, newLoad);
                
                this.add(panel);
                
                //Fit frame to ensure all panels/components are visible
		this.pack();

		//Determine centre of user's screen and position frame accordingly
		Toolkit k=Toolkit.getDefaultToolkit();
		Dimension d=k.getScreenSize();
		this.setLocation(d.width/2-this.getWidth()/2,d.height/2-this.getHeight()/2);

		//Display frame on screen
		this.setVisible(true);
    }
    
}
