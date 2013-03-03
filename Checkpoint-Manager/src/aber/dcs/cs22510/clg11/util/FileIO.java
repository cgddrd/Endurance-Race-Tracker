/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
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
 *
 * @author Connor Luke Goddard (clg11)
 */
public class FileIO {

    public FileIO() {
        
    }

    /**
     * Reads in the contents of internal/external dictionary files and places
     * the contents into a Vector which is then returned, and used to populate
     * the {@link aber.dcs.clg11.wordladder.model.Graph}.
     *
     * @param fileName The directory of the file to be parsed.
     * @return Vector containing the contents of the parsed file.
     */
    public ArrayList<String[]> readIn(File fileName) {

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

                String[] details = line.split(" ");
                values.add(details);

            }

            //Once completed, safely close the file reader
            bufferedReader.close();
            return values;

            //If any IO exceptions occur...
        } catch (IOException iOE) {

            System.out.println("WE GOT A PROBLEM...");
            iOE.printStackTrace();
            return null;
        }

    }

    public void writeFile(File writeFile, String output) {

        try {

            if (!writeFile.exists()) {
                writeFile.createNewFile();
            }

            FileOutputStream fos = new FileOutputStream(writeFile.getAbsoluteFile(), true);
            FileLock fl = fos.getChannel().tryLock();

            if (fl != null) {

                System.out.println("OK we have the lock.. adding to the file");

                FileWriter fw = new FileWriter(fos.getFD());

                fw.write(output);

                fl.release();
                System.out.println("Released Lock");
                fw.close();

            } else {
                System.out.println("Already locked by another process... bad luck\n");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public void addActivityLog(String logMessage) {
        
      DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
      Calendar cal = Calendar.getInstance();
      
      String logOutput = "LOG - CM: " + logMessage  + " - " + dateFormat.format(cal.getTime()) + "\n";
        
      writeFile(new File("../files/log.txt"), logOutput);
         
    }
}
