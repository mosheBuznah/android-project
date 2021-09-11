package com.android_project_client;

import android.os.AsyncTask;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client extends AsyncTask<String, Void, Void>
{
    // initialize socket and input output streams
    private Socket m_socket            = null;
    private DataInputStream m_input   = null;
    private DataOutputStream m_out     = null;
    private PrintWriter m_pw = null;


    @Override
    protected Void doInBackground(String... voids) {
        String message = voids[0];

        try {
            m_socket = new Socket("10.100.102.22", 3000);
            m_pw = new PrintWriter(m_socket.getOutputStream());
            m_pw.write(message);

            System.out.println("finish send message");
            m_pw.flush();
            m_pw.close();
            m_socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}

/*
public class Client
{
    private Socket m_socket            = null;
    private DataInputStream m_input   = null;
    private DataOutputStream m_out     = null;
    private PrintWriter m_pw = null;

    public Client(String ip_address, int port, String message) {
        try {
            m_socket = new Socket(ip_address, port);
            m_pw = new PrintWriter(m_socket.getOutputStream());
            m_pw.write(message);

            System.out.println("finish send message");
            m_pw.flush();
            m_pw.close();
            m_socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}*/

