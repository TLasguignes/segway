package com.androidsrc.client;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class MessageThread extends Thread {

    private Socket _socket;
    private char[] _array;


    public MessageThread(Socket socket, char[] array) {
        _socket = socket;
        _array = array;
    }


    @Override
    public void run() {
        try {
            PrintWriter out = new PrintWriter(new BufferedWriter(
                    new OutputStreamWriter(_socket.getOutputStream())),
                    true);
            while (true) {
                try
                {
                    Thread.sleep(40);
                    out.println(_array);
                }
                catch (InterruptedException e)
                {
                    Thread.currentThread().interrupt(); // restore interrupted status
                }
            }
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    public void set_array(char[] array) {
        this._array = array;
    }


}