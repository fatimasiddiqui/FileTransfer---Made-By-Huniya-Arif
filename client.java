package huniya;

import java.io.*;
import java.net.*;
import java.util.Scanner;

class client {

    private final static String serverIP = "127.0.0.1";
    private final static int serverPort = 55554;
    
    public static void main(String args[]) {
  
        BufferedOutputStream outToServer = null;
        Socket clientSocket = null;
        Scanner user_input = new Scanner( System.in );
        
System.out.println("Welcome to client. Please enter your file name:");
String fileToSend = user_input.next();


        try {
            clientSocket = new Socket( serverIP , serverPort );
       
            outToServer = new BufferedOutputStream(clientSocket.getOutputStream());
        } catch (IOException ex) {
            // Do exception handling
        }

        if (outToServer != null) {
        	File myFile = new File( fileToSend );
            byte[] mybytearray = new byte[(int) myFile.length()];

            FileInputStream fis = null;

            try {
                fis = new FileInputStream(myFile);
            } catch (FileNotFoundException ex) {
                // Do exception handling
            }
            BufferedInputStream bis = new BufferedInputStream(fis);

            try {
                bis.read(mybytearray, 0, mybytearray.length);
                //sending to server
                outToServer.write(mybytearray, 0, mybytearray.length);
                outToServer.flush();
                outToServer.close();
                clientSocket.close();

                // File sent, exit the main method
                return;
            } catch (IOException ex) {
                // Do exception handling
            }
        }
    }
}