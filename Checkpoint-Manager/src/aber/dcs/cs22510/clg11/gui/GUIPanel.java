/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package aber.dcs.cs22510.clg11.gui;

import aber.dcs.cs22520.clg11.model.Datastore;
import aber.dcs.cs22520.clg11.model.Entrant;
import aber.dcs.cs22520.clg11.util.LoadData;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
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
    private JSpinner spinner;
    private SpinnerDateModel sm;

    private Datastore data;
    private LoadData load;
    
    public GUIPanel(Datastore newData, LoadData newLoad) {
        
        this.data = newData;
        this.load = newLoad;

        //Set the size of the panel
        this.setPreferredSize(new Dimension(500, 400));

        initComponents();

    }

    public void initComponents() {

        String[] petStrings = {"Bird", "Cat", "Dog", "Rabbit", "Pig"};

        entrantList = new JComboBox(getAllEntrants().toArray());
        entrantList.setSelectedIndex(0);

        nodeList = new JComboBox(petStrings);
        nodeList.setSelectedIndex(0);

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

    /**
     * Sets up the 'SpringLayout' layout manager to organise all components on
     * the panel.
     */
    public void setUpLayout() {

        /*	//Set the NORTH edge of the button to be 5 pixels down from the NORTH edge of the panel
         layout.putConstraint(SpringLayout.NORTH,newOrder,5,SpringLayout.NORTH,this);

         //Set the WEST edge of the button to be 80 pixels to the right of the WEST edge of the panel
         layout.putConstraint(SpringLayout.WEST,newOrder,80,SpringLayout.WEST,this);

         layout.putConstraint(SpringLayout.NORTH,printReceipt,5,SpringLayout.NORTH,this);
         layout.putConstraint(SpringLayout.WEST,printReceipt,10,SpringLayout.EAST,newOrder);

         layout.putConstraint(SpringLayout.NORTH,saveTill,10,SpringLayout.SOUTH,newOrder);
         layout.putConstraint(SpringLayout.WEST,saveTill,10,SpringLayout.WEST,this);

         layout.putConstraint(SpringLayout.NORTH,loadTill,10,SpringLayout.SOUTH,newOrder);
         layout.putConstraint(SpringLayout.WEST,loadTill,10,SpringLayout.EAST,saveTill);

         layout.putConstraint(SpringLayout.NORTH,exitTill,10,SpringLayout.SOUTH,newOrder);
         layout.putConstraint(SpringLayout.WEST,exitTill,10,SpringLayout.EAST,loadTill);

         */
    }

    public void actionPerformed(ActionEvent evt) {
        
        String actionCommand = evt.getActionCommand();
        //If the "New Order" button is clicked
        switch (actionCommand) {
            
            case "Submit Checkpoint Time":
                SimpleDateFormat sdf = new SimpleDateFormat("HH:mm");
                System.out.println("THE CURRENT TIME: " + sdf.format(spinner.getValue()));
                break;
            case "Set to Current Time":
                Calendar currentTime = Calendar.getInstance();
                spinner.setValue(currentTime.getTime());
                break;

        }
    }
}
