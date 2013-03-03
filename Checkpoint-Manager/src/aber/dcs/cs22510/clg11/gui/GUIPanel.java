/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22510.clg11.gui;

import aber.dcs.cs22520.clg11.model.Course;
import aber.dcs.cs22520.clg11.model.Datastore;
import aber.dcs.cs22520.clg11.model.Entrant;
import aber.dcs.cs22520.clg11.model.Node;
import aber.dcs.cs22520.clg11.util.LoadData;
import aber.dcs.cs22520.clg11.util.ProcessData;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import javax.swing.*;

/**
 *
 * @author Connor Luke Goddard (clg11)
 */
public class GUIPanel extends JPanel implements ActionListener {

    /**
     * Buttons that represent system-wide operations
     */
    private JButton submitTime, setCurrentTime;
    /**
     * The layout manager used by the panel
     */
    private SpringLayout layout = new SpringLayout();
    private JComboBox entrantList;
    private JComboBox nodeList;
    private JComboBox mcType;
    private String[] mcArriveDepart = {"Arriving", "Departing"};
    private JSpinner spinner;
    private SpinnerDateModel sm;
    private Datastore data;
    private LoadData load;
    private ProcessData proc;

    public GUIPanel(Datastore newData, LoadData newLoad) {

        this.data = newData;
        this.load = newLoad;

        //Set the size of the panel
        this.setPreferredSize(new Dimension(500, 400));

        initComponents();

    }

    public void initComponents() {
        
        proc = new ProcessData(data, load);

        entrantList = new JComboBox(getAllEntrants().toArray());
        entrantList.setSelectedIndex(0);

        nodeList = new JComboBox(getAllCheckpoints().toArray());
        nodeList.setSelectedIndex(0);
        nodeList.addActionListener(this);
        
        mcType = new JComboBox(mcArriveDepart);
        mcType.setSelectedIndex(0);
        mcType.setEnabled(false);
     

        //Create new instance of JButton with specified button text
        submitTime = new JButton("Submit Checkpoint Time");
        submitTime.addActionListener(this);

        setCurrentTime = new JButton("Set to Current Time");
        setCurrentTime.addActionListener(this);

        sm = new SpinnerDateModel();
        sm.setCalendarField(Calendar.MINUTE);
        spinner = new JSpinner();
        spinner.setModel(sm);

        JSpinner.DateEditor de = new JSpinner.DateEditor(spinner, "HH:mm");
        spinner.setEditor(de);

        this.add(spinner);
        this.add(entrantList);
        this.add(nodeList);
        this.add(mcType);
        this.add(submitTime);
        this.add(setCurrentTime);

    }

    public ArrayList<String> getAllEntrants() {

        ArrayList<String> entrantList = new ArrayList();

        for (Entrant e : data.getEntrants()) {

            entrantList.add(e.getFullName());

        }

        return entrantList;

    }

    public ArrayList<String> getAllCheckpoints() {

        ArrayList<String> checkpointList = new ArrayList();

        for (Node cp : data.getNodes()) {

            if (cp.getType().equals("CP") || cp.getType().equals("MC")) {

                checkpointList.add(Integer.toString(cp.getNumber()));

            }

        }

        return checkpointList;

    }
    
    public Node getNode(int nodeNo) {
        
        for (Node n : data.getNodes()) {
            
            if (n.getNumber() == nodeNo) {
                
                return n;
            }
        }
        
        return null;
        
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

    public void submitCheckpoint() {
        
        proc.resetEntrantProgress();

        proc.getTimes();
        
        Entrant currentEntrant = data.getEntrants().get(entrantList.getSelectedIndex());
        ArrayList<Node> entrantNodes = proc.getEntrantCourseNodes(currentEntrant);

        if (!data.getEntrants().get(1).getIsExcluded()) {
            
            SimpleDateFormat sdf = new SimpleDateFormat("HH:mm");
            
            if (mcType.isEnabled()) {
                
                proc.checkNextNode(entrantNodes, currentEntrant, Integer.parseInt((String) nodeList.getSelectedItem()), (String) mcType.getSelectedItem(), sdf.format(spinner.getValue()));
                
            } else {
               
                proc.checkNextNode(entrantNodes, currentEntrant, Integer.parseInt((String) nodeList.getSelectedItem()), sdf.format(spinner.getValue()));
                
            }
           
         

        }
    }
    
    

    public void actionPerformed(ActionEvent evt) {
        
        String actionCommand = evt.getActionCommand();
        //If the "New Order" button is clicked
        switch (actionCommand) {

            case "Submit Checkpoint Time":
                submitCheckpoint();
                break;
            case "Set to Current Time":
                Calendar currentTime = Calendar.getInstance();
                spinner.setValue(currentTime.getTime());
                break;

        }
        
        if (evt.getSource() == nodeList) {
            
            Node n = getNode(Integer.parseInt((String) nodeList.getSelectedItem()));
            
            if (n.getType().equals("MC")) {
                
                this.mcType.setEnabled(true);
                
            } else {
                
                this.mcType.setEnabled(false);
            }
        }
    }
}