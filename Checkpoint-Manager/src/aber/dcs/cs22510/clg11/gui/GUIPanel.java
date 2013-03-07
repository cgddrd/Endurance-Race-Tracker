package aber.dcs.cs22510.clg11.gui;

import aber.dcs.cs22510.clg11.model.Datastore;
import aber.dcs.cs22510.clg11.model.Entrant;
import aber.dcs.cs22510.clg11.model.Node;
import aber.dcs.cs22510.clg11.util.FileIO;
import aber.dcs.cs22510.clg11.util.LoadData;
import aber.dcs.cs22510.clg11.util.ProcessData;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import javax.swing.*;

/**
 * Contains the GUI elements accessed by the user to interact with the application.
 * Allows the user to select entrants and nodes. Enter a new time (or use system
 * time) and then submit this new time to the log file. Any problems that occur
 * will be displayed to the user.
 * 
 * @author Connor Goddard (clg11)
 * Copyright: Aberystwyth University, Aberystwyth.
 */
public class GUIPanel extends JPanel implements ActionListener {

    /**
     * Buttons that represent system-wide operations.
     */
    private JButton submitTime, setCurrentTime;
    
    /**
     * The layout manager used by the panel.
     */
    private SpringLayout layout = new SpringLayout();
    
    
    /**
     * Drop-down selected boxes used to select entrants and nodes.
     */
    private JComboBox<String> entrantList;
    private JComboBox<String> nodeList;
    
    /**
     * Determines whether an entrant is arriving or leaving medical checkpoint.
     */
    private JComboBox<String> mcType;
    private String[] mcArriveDepart = {"Arriving", "Departing"};
    
    /**
     * Spinner used to allow the user to select a time value.
     */
    private JSpinner spinner;
    private SpinnerDateModel sm;
    
    
    private Datastore data;
    private LoadData load;
    
    /**
     * Enables the GUI to access the methods used for processing times.
     */
    private ProcessData proc;
    
    private FileIO fileIO;

    /**
     * Constructor to instantiate a new GUIPanel. Takes the two classes passed 
     * from GUIFrame as parameters to allow panel to acccess shared data store
     * and loading facilities.
     * @param newData Datastore object passed down from GUIFrame.
     * @param newLoad LoadData object passed down from GUIFrame.
     */
    public GUIPanel(Datastore newData, LoadData newLoad, FileIO newFileIO) {

        this.data = newData;
        this.load = newLoad;
        this.fileIO = newFileIO;
        

        //Set the size of the panel
        this.setPreferredSize(new Dimension(500, 400));

        //Initialise and add all of the panel GUI components.
        initComponents();

    }

    /**
     * Initialises the panel components (including linking components to 
     * listeners where required) before adding the components to the panel.
     */
    public void initComponents() {
        
        String[] comboValues;
        
        /*
         * Instantiate new ProcessData class to allow access to data processing
         * facilties.
         */
        proc = new ProcessData(data, fileIO);

        //Load all entrant names into entrant drop-down GUI box component.
        comboValues = Arrays.copyOf(getAllEntrants().toArray(), getAllEntrants().toArray().length, String[].class);
        
        entrantList = new JComboBox<String>(comboValues);
        entrantList.setSelectedIndex(0);

        //Load all node numbers into node drop-down GUI box component.
        comboValues = Arrays.copyOf(getAllCheckpoints().toArray(), getAllCheckpoints().toArray().length, String[].class);
        
        nodeList = new JComboBox<String>(comboValues);
        nodeList.setSelectedIndex(0);
        
        //Add local action listener (Required for determining a MC).
        nodeList.addActionListener(this);
        
        //Load the MC "arrive/depart" options into drop-down GUI box.
        mcType = new JComboBox<String>(mcArriveDepart);
        mcType.setSelectedIndex(0);
        mcType.setEnabled(false);
     

        //Create new instance of JButton with specified button text
        submitTime = new JButton("Submit Checkpoint Time");
        submitTime.addActionListener(this);

        setCurrentTime = new JButton("Set to Current Time");
        setCurrentTime.addActionListener(this);

        
        //Create new JSpinner model that will access the current system time.
        sm = new SpinnerDateModel();
        sm.setCalendarField(Calendar.MINUTE);
        
        //Create a new Spinner object and set the above model to it.
        spinner = new JSpinner();
        spinner.setModel(sm);

        //Set the time format to be diplayed in the JSpinner.
        JSpinner.DateEditor de = new JSpinner.DateEditor(spinner, "HH:mm");
        spinner.setEditor(de);

        //Add all the components to the GUI panel.
        this.add(spinner);
        this.add(entrantList);
        this.add(nodeList);
        this.add(mcType);
        this.add(submitTime);
        this.add(setCurrentTime);

    }
    
    /**
     * Sets up the 'SpringLayout' layout manager to organise all components on
     * the panel.
     */
    public void setUpLayout() {

        /*	//Set the NORTH edge of the button to be 5 pixels down from the NORTH edge of the panel
         layout.putConstraint(SpringLayout.NORTH,newOrder,5,SpringLayout.NORTH,this);

         //Set the WEST edge of the button to be 80 pixels to the right of the WEST edge of the panel
         layout.putConstraint(SpringLayout.WEST,newOrder,80,SpringLayout.WEST,this);

         */
    }

    /**
     * Obtains a list of all the entrant names to populate selection box.
     * Accesses them from the array list of entrants contained within
     * {@link aber.dcs.cs22510.clg11.model.Datastore}.
     * 
     * @return Arraylist of all the entrant's names.
     */
    public ArrayList<String> getAllEntrants() {

        ArrayList<String> entrantList = new ArrayList<String>();

        for (Entrant e : data.getEntrants()) {

            entrantList.add(e.getFullName());

        }

        return entrantList;

    }

    /**
     * Obtains a list of all the checkpoints ONLY to populate the CP selection
     * box. 
     * Accesses them from the array list of nodes contained within
     * {@link aber.dcs.cs22510.clg11.model.Datastore}.
     * 
     * @return Arraylist of all the nodes that are CHECKPOINTS.
     */
    public ArrayList<String> getAllCheckpoints() {

        ArrayList<String> checkpointList = new ArrayList<String>();

        //Loop through all the nodes.
        for (Node cp : data.getNodes()) {

            //If the current node is a checkpoint, and not a junction, add it.
            if (cp.getType().equals("CP") || cp.getType().equals("MC")) {

                checkpointList.add(Integer.toString(cp.getNumber()));

            }

        }

        return checkpointList;

    }
    
    /**
     * Attempts to fetch a specific node denoted by the node number selected from
     * the drop-down GUI box. If such a node cannot be found, NULL us returned.
     * @param nodeNo The number of the selected node.
     * @return The located node or NULL.
     */
    public Node getNode(int nodeNo) {
        
        for (Node n : data.getNodes()) {
            
            if (n.getNumber() == nodeNo) {
                
                return n;
            }
        }
        
        return null;
        
    }

 
    /**
     * Submits a new time log based on user input within the GUI to allow 
     * it to then be processed by the system and logged accordingly. 
     */
    public void submitCheckpoint() {
        
        /*
         * Reset the currrent progress of all entrants to allow the existing 
         * "times" file (with any NEW entries made since it was last read in)
         * to be re-read into the system to track any updates made by other
         * versions of the checkpoint manager running.
         */
        proc.resetEntrantProgress();

        /*
         * Re-read in the "times" file to allow any new times logged by other 
         * running versions of the checkpoint manager to update the information 
         * contained within this version of the CM. 
         */
        proc.getTimes();
        
        //Obtain the selected entrant from the arraylist of entrants.
        Entrant currentEntrant = data.getEntrants().get(entrantList.getSelectedIndex());
                
        //Obtain the arraylist of course nodes that make up the course that entrant is registered for.
        ArrayList<Node> entrantNodes = proc.obtainEntrantCourseNodes(currentEntrant);

        
        //if (!data.getEntrants().get(1).getIsExcluded()) {
            
            //Create a formatter for the time value entered by the user.
            SimpleDateFormat sdf = new SimpleDateFormat("HH:mm");
            
            //Obtain the number of the node selected by the user.
            int nodeNumber = Integer.parseInt((String) nodeList.getSelectedItem());
            
            //Format the time value entered by the user.
            String timeValue = sdf.format(spinner.getValue());
            
            //Check to see if the node selected was a MC.
            if (mcType.isEnabled()) {
                
                //If so determine whether they were arriving or departing.
                String mcSelection = (String) mcType.getSelectedItem();
                
                //Process this new logged time.
                proc.processNextNode(entrantNodes, currentEntrant, nodeNumber, mcSelection , timeValue);
                
            } else {
               
                //The checkpoint is not a MC, and so just process the new logged time.
                proc.processNextNode(entrantNodes, currentEntrant, nodeNumber , timeValue);
                
            }
     //   }
    }
    
    
    /**
     * Listener for actions from sub-panel components, to allow operations to be run 
     * when components are interacted with.
     * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
     * @param evt - ActionEvent called from components in the panels that require an action to be performed.
     */
    public void actionPerformed(ActionEvent evt) {
        
        String actionCommand = evt.getActionCommand();
        
        
        //Switch statement used to capture action commands from buttons.
        switch (actionCommand) {

            case "Submit Checkpoint Time":
                
                //Submit the entered time values.
                submitCheckpoint();
                break;
            
            case "Set to Current Time":
                
                //Obtain the current system time from the Calendar class.
                Calendar currentTime = Calendar.getInstance();
                
                //Update the value of the time spinner to the current time.
                spinner.setValue(currentTime.getTime());
                break;

        }
        
        
        //Listen for events on the nodes drop-down box component.
        if (evt.getSource() == nodeList) {
            
            //Obtain the selected Node object from the collection of nodes.
            Node n = getNode(Integer.parseInt((String) nodeList.getSelectedItem()));
            
            //Determine whether the selected node is a medical checkpoint.
            if (n.getType().equals("MC")) {
                
                //If it is, allow the "arrive/depart" selection box to be used.
                this.mcType.setEnabled(true);
                
            } else {
                
                this.mcType.setEnabled(false);
            }
        }
    }
}