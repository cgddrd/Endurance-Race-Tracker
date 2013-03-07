package aber.dcs.cs22510.clg11.gui;

import aber.dcs.cs22510.clg11.model.Datastore;
import aber.dcs.cs22510.clg11.util.FileIO;
import aber.dcs.cs22510.clg11.util.LoadData;
import java.awt.Dimension;
import java.awt.Toolkit;
import javax.swing.JFrame;

/**
 * Main JFrame for displaying program GUI. Responsible displaying main GUI
 * window and for instantiating the GUI sub-panel
 * {@link aber.dcs.cs22510.clg11.gui.GUIPanel}. Passes the new {@link aber.dcs.cs22510.clg11.model.Datastore} &
 * {@link aber.dcs.cs22510.clg11.util.LoadData} classes received from
 * {@link aber.dcs.cs22510.clg11.driver.CMDriver}, to the base panel as a
 * parameter to allow access to the data model from the sub-panel.
 *
 * @author Connor Goddard (clg11) Copyright: Aberystwyth University,
 * Aberystwyth.
 */
public class GUIFrame extends JFrame {

    /**
     * The new GUIPanel component.
     */
    private GUIPanel panel;

    /**
     * Constructor to instantiate a new GUIFrame. Takes the two classes created
     * in CMDriver as parameters to pass onto GUI sub-panel.
     *
     * @param newData Datastore class created in main method.
     * @param newLoad LoadData class created in main method.
     */
    public GUIFrame(Datastore newData, LoadData newLoad, FileIO newFileIO) {

        //Initialise and set up GUI frame (window).
        this.setTitle("Checkpoint Manager | Connor Goddard (clg11)");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Prevent user resizing frame.
        this.setResizable(false);

        //Initialise the sub-panel, passing the two shared components.
        panel = new GUIPanel(newData, newLoad, newFileIO);

        //Add this panel to the whole of the frame (No layout set).
        this.add(panel);

        //Fit frame to ensure all panels/components are visible.
        this.pack();

        //Determine centre of user's screen and position frame accordingly.
        Toolkit k = Toolkit.getDefaultToolkit();
        Dimension d = k.getScreenSize();
        this.setLocation(d.width / 2 - this.getWidth() / 2, d.height / 2 - this.getHeight() / 2);

        //Display frame on screen.
        this.setVisible(true);
    }
}
