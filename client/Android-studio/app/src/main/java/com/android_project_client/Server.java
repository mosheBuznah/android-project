package com.android_project_client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.LogRecord;
import android.os.*;
import android.widget.Toast;

/*
public class Server implements Runnable
{
    Socket s;
    ServerSocket ss;
    InputStreamReader isr;
    BufferedReader bufferedReader;
    Handler h = new Handler();

    String message;

    @Override
    public void run() {
        try {
            ss = new ServerSocket(3000);
        } catch (IOException e) {
            e.printStackTrace();
        }


        while (true) {
            try {
                s = ss.accept();
                isr = new InputStreamReader(s.getInputStream());
                bufferedReader = new BufferedReader(isr);
                message = bufferedReader.readLine();

                h.post(new Runnable() {
                    @Override
                    public void run() {
                        //Login l = new Login();
                      //  l.make_toast(message);
                        System.out.println("recieve message = "+message);
                    }
                });
            } catch (IOException e) {
                e.printStackTrace();
            }

        }

    }
}*/