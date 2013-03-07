package aber.dcs.cs22510.clg11.util;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.channels.FileLock;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;

/**
 * Provides file I/O facilities to allow data files to be read into the system,
 * and the time file to be updated/appended to as required.
 * 
 * @author Connor Luke Goddard (clg11)
 * Copyright: Aberystwyth University, Aberystwyth.
 */
public class FileIO {
    
    private int timesFilePosition = 0;

    /**
     * Default constructor for FileIO.
     */
    public FileIO() {
        
    }

    /**
     * Reads in the contents of specified data files and places
     * the contents into an Arraylist which is then returned, and used to update
     * the internal data collections used by the application.
     *
     * @param fileName The directory of the file to be parsed.
     * @return Arraylist of String arrays containing the contents of the parsed file.
     */
    public ArrayList<String[]> readIn(File fileName, boolean isTimesFile) {

        ArrayList<String[]> values = new ArrayList<>();

        try {

            //Create File IO objects
            FileReader fileReader;
            BufferedReader bufferedReader;

            //Initialise the File IO objects, passing in the selected file path
            fileReader = new FileReader(fileName);
            bufferedReader = new BufferedReader(fileReader);

            //Initialise local variable used to store the current line being read in
            String line;

            //While there are still lines to read in from the file (i.e. read in every line in the file)
            while ((line = bufferedReader.readLine()) != null) {

                //As there is multiple data on each line, split the values up.
                String[] details = line.split(" ");
                
                //Add these broken down values to the larger collection of lines.
                values.add(details);
                
                if (isTimesFile) {
                    timesFilePosition++; 
                }
               

            }

            //Once completed, safely close the file reader
            bufferedReader.close();
            
            System.out.println("*** LINES IN FILE: " + this.timesFilePosition + " ***");
            return values;

            //If any IO exceptions occur...
        } catch (IOException iOE) {

            System.out.println("WE GOT A PROBLEM...");
            return null;
        }

    }

    /**
     * Writes output data to specified files, as these files are shared, 
     * file locking has to be used to prevent corruption of data/files.
     * @param writeFile The file that is to be written to.
     * @param output The output data string.
     */
    public void writeFile(File writeFile, String output) {

        try {

            //If the file does not exist, create a new file.
            if (!writeFile.exists()) {
                writeFile.createNewFile();
            }

            //Create a new output stream that will append to the file.
            FileOutputStream fos = new FileOutputStream(writeFile.getAbsoluteFile(), true);
            
            //Attempt to lock the file to allow the data to be written.
            FileLock fl = fos.getChannel().tryLock();

            //Check if the lock was successfull.
            if (fl != null) {

                //If so write the data to the file.
                FileWriter fw = new FileWriter(fos.getFD());
                fw.write(output);

                //Once the data has been successfully written, release the lock.
                fl.release();
                
                //Close the connection to the file.
                fw.close();

            } else {
                
                //Otherwise if the file was already locked, inform the user.
                System.out.println("Already locked by another process... bad luck\n");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    /**
     * Adds a new log message to the "logs.txt" file.
     * Called when a major activity occurs in the application.
     * @param logMessage Message describing the activity.
     */
    public void addActivityLog(String logMessage) {
      
      //Obtain the current date/time and format it for use in the log file.
      DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
      Calendar cal = Calendar.getInstance();
      
      //Build the log message using predefined output template.
      String logOutput = "LOG - CM: " + logMessage  + " - " + dateFormat.format(cal.getTime()) + "\n";
      
      //Write the log message to the log file.
      writeFile(new File("../files/log.txt"), logOutput);
         
    }
}
