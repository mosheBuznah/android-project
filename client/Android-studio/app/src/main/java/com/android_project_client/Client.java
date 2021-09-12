package com.android_project_client;

import android.os.AsyncTask;
import android.os.Handler;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Arrays;

public class Client {
    private byte[] m_message_from_server;
    private Socket m_client_sock = null;
    private String m_ip = "";
    private int m_port = 0;

    public Client(String ip, int port)
    {
        m_ip = ip;
        m_port = port;
        createSocket();
    }

    public byte[] getMessageFromServer()
    {
        return m_message_from_server;
    }

    public void createSocket()
    {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    m_client_sock = m_client_sock == null ? new Socket(m_ip, m_port): m_client_sock;
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();

    }

    public void sendMessage(final byte[] msg) {

        final Handler handler = new Handler();
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    while(m_client_sock == null)
                    {
                        System.out.println("wait for socket...");
                    }
                    OutputStream out = m_client_sock.getOutputStream();

                    PrintWriter output = new PrintWriter(out);

                    output.print(msg);
                    output.flush();
                    //   output.close();
                    // out.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();

    }

    public void recv()
    {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    while(m_client_sock == null)
                    {
                        System.out.println("wait for socket...");
                    }
                    BufferedReader input = new BufferedReader(new InputStreamReader(m_client_sock.getInputStream()));
                    m_message_from_server = input.readLine().getBytes();
                    System.out.println("From server: ");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });


        thread.start();
    }
}


