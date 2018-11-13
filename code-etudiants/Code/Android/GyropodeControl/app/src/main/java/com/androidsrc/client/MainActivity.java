package com.androidsrc.client;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;

import android.app.Activity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.Toast;

public class MainActivity extends Activity implements JoystickView.JoystickListener {
    char[] array = new char[16];
    private Socket socket;
    private static final int SERVERPORT = 8888;
    private String SERVER_IP = "10.32.0.206";
    DisplayMetrics screen;
    float screenWidth, screenHeight;
    JoystickView myJoystick;
    Button connect, disconnect;
    Boolean connected = false;
    EditText ip_adress;
    MessageThread myThread;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        screen = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(screen);
        screenWidth = screen.widthPixels;
        screenHeight = screen.heightPixels;

        myJoystick = (JoystickView) findViewById(R.id.testJoystick);
        myJoystick.getLayoutParams().height = (int) (screenWidth);
        myJoystick.getLayoutParams().width = (int) (screenWidth);

        RelativeLayout.LayoutParams marginParams = (RelativeLayout.LayoutParams) myJoystick.getLayoutParams();
        marginParams.setMargins(0, 0, 0, (int) (0.1f * screenWidth));
        myJoystick.setLayoutParams(marginParams);

        connect = (Button) findViewById(R.id.button_connect);
        connect.getLayoutParams().width = (int) (0.4f * screenWidth);
        connect.setOnClickListener(connectionManager);

        disconnect = (Button) findViewById(R.id.button_disconnect);
        disconnect.getLayoutParams().width = (int) (0.4f * screenWidth);
        disconnect.setOnClickListener(connectionManager);
        disconnect.setEnabled(false);

        ip_adress = (EditText) findViewById(R.id.ip_adress);
        ip_adress.setText(SERVER_IP);


    }

    View.OnClickListener connectionManager = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            if (v.getId() == connect.getId()) {
                socket = new Socket();
                Thread clientThread = new Thread(new ClientThread());
                connect.setEnabled(false);
                Toast.makeText(MainActivity.this, "Trying to connect to" + SERVER_IP + "...", Toast.LENGTH_SHORT).show();
                clientThread.start();
                Thread.State state = clientThread.getState();
                while (state != Thread.State.TERMINATED) {
                    state = clientThread.getState();
                }
                if (connected) {
                    disconnect.setEnabled(true);
                    Toast.makeText(MainActivity.this, "Connected", Toast.LENGTH_SHORT).show();
                    array = setArray(array, "0.10", "90.0", "1");
                    myThread = new MessageThread(socket, array);
                    myThread.start();
                } else {
                    connect.setEnabled(true);
                    Toast.makeText(MainActivity.this, "Failed to connect to " + SERVER_IP, Toast.LENGTH_SHORT).show();
                }
            }


            if (v.getId() == disconnect.getId()) {
                try {
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                connected = false;
                connect.setEnabled(true);
                disconnect.setEnabled(false);
                myThread.interrupt();

            }
        }
    };


    @Override
    public void onJoystickMoved(float Puissance, float Angle, int Sens, int id) {
        array = setArray(array, String.valueOf(Puissance), String.valueOf(Angle), String.valueOf(Sens) );
        if (myThread != null) {
            if (!myThread.isInterrupted()) {
                myThread.set_array(array);
            }
        }
    }

    public char[] setArray(char[] array, String puissance, String angle, String sens) {
        while (puissance.length()<4) {
            puissance = puissance + '0';
        }

        while (angle.length()<4) {
            angle = angle+ '0';
        }
        array[0] = '<';
        array[1] = 'p';
        array[2] = puissance.charAt(0);
        array[3] = puissance.charAt(1);
        array[4] = puissance.charAt(2);
        array[5] = puissance.charAt(3);
        array[6] = '<';
        array[7] = 'a';
        array[8] = angle.charAt(0);
        array[9] = angle.charAt(1);
        array[10] = angle.charAt(2);
        array[11] = angle.charAt(3);
        array[12] = '<';
        array[13] = 's';
        array[14] = sens.charAt(0);
        array[15] = '\0';
        return array;
    }


class ClientThread implements Runnable {

    @Override
    public void run() {

        try {
            SERVER_IP = String.valueOf(ip_adress.getText());
            InetAddress serverAddr = InetAddress.getByName(SERVER_IP);
            // Creates an unconnected socket
            int timeout = 5000;   // 5000 millis = 5 seconds
            SocketAddress sockaddr = new InetSocketAddress(serverAddr, SERVERPORT);
            // Connects this socket to the server with a specified timeout value
            // If timeout occurs, SocketTimeoutException is thrown
            socket.connect(sockaddr, timeout);

            //socket = new Socket(serverAddr, SERVERPORT);
            if (socket.isConnected()) {
                connected = true;
            }

        } catch (UnknownHostException e1) {
            e1.printStackTrace();
        } catch (IOException e1) {
            e1.printStackTrace();
        }
    }
}
}