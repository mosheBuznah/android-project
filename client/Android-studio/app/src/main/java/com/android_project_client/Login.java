package com.android_project_client;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import android.text.method.LinkMovementMethod;
import android.view.View;
import android.widget.TextView;

public class Login extends AppCompatActivity {
    EditText userName;
    EditText password;
    Button loginButton;
    Socket client_sock = null;
    String message_from_server = "";
    Client c;
    TextView signUpTv;
    TextView forgotPasswordTv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);
        signUpTv = findViewById(R.id.signUp);


        signUpTv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent go = new Intent(Login.this, signUp.class);
                startActivity(go);
            }
        });

        userName = findViewById(R.id.login_username);
        password = findViewById(R.id.login_password);
        loginButton = findViewById(R.id.login_button);
        c = new Client("10.100.102.22", 3000);

        loginButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view)
            {
                login_handle();
            }
        });

        forgotPasswordTv = findViewById(R.id.tv_forgotPassword);

        forgotPasswordTv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent go = new Intent(Login.this, ForgotPassword.class);
                startActivity(go);
            }
        });

        forgotPasswordTv.setMovementMethod(LinkMovementMethod.getInstance());

    }

    private void login_handle()
    {
        String userNameStr = userName.getText().toString();
        String passwordStr = password.getText().toString();

        System.out.println("woowwwwwwwwwwwwwwwwwwww");


        c.sendMessage(userNameStr+"&"+passwordStr);
        c.recv();

    }

    private void createSocket()
    {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    client_sock = client_sock == null ? new Socket("10.100.102.22", 3000): client_sock;
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
    }

    private void sendMessage(final String msg) {

        final Handler handler = new Handler();
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    OutputStream out = client_sock.getOutputStream();

                    PrintWriter output = new PrintWriter(out);

                    output.println(msg);
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

    private void recv()
    {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    BufferedReader input = new BufferedReader(new InputStreamReader(client_sock.getInputStream()));
                    message_from_server = input.readLine();
                    System.out.println("From server: "+message_from_server);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
    }

    /*class Server implements Runnable
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
                ss = new ServerSocket(3001);
                while (true) {
                    System.out.println("recieve message = ");
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
                            make_toast(message);
                        }
                    });
                }
            }catch (IOException e) {
                e.printStackTrace();
                System.out.println("fucking errorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr");
            }

            }

    }*/


    public void make_toast(String message)
    {
        Toast.makeText(getApplicationContext(), message, Toast.LENGTH_SHORT).show();
    }
}