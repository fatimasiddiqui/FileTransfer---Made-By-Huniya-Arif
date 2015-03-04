package huniya;

import java.io.*;
import java.net.*;

class Server {

	private final static String fileOutput = "heh1.txt";
	
    public static void main(String args[]) {
    	System.out.println("Welcome to server.");
        while (true) {
            ServerSocket welcomeSocket = null;
            Socket connectionSocket = null;
            byte[] aByte = new byte[1];
            int bytesRead;
            InputStream is = null;

            try {
            	//attaching port to the socket
                welcomeSocket = new ServerSocket(55554);
                connectionSocket = welcomeSocket.accept();
                //getting ready to scan
                is = connectionSocket.getInputStream();
            } catch (IOException ex) {
                // Do exception handling
            }
            ByteArrayOutputStream baos = new ByteArrayOutputStream();

            if (is != null) {
            	 FileOutputStream fos = null;
                 BufferedOutputStream bos = null;
                 try {
                     fos = new FileOutputStream( fileOutput );
                     bos = new BufferedOutputStream(fos);
                     //receive data from server
                     bytesRead = is.read(aByte, 0, aByte.length);

                     do {
                             baos.write(aByte);
                             bytesRead = is.read(aByte);
                     } while (bytesRead != -1);

                     bos.write(baos.toByteArray());
                     bos.flush();
                     bos.close();
                     connectionSocket.close();
                 } catch (IOException ex) {
                     // Do exception handling
                 }
            
            }
        }
    }
}