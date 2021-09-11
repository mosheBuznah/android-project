package com.android_project_client;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class Login extends AppCompatActivity {
    EditText userName;
    EditText password;
    Button loginButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);

        userName = findViewById(R.id.login_username);
        password = findViewById(R.id.login_password);
        loginButton = findViewById(R.id.login_button);

        loginButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view)
            {
                login_handle();
            }
        });

        Thread thread = new Thread(new Server());
        thread.start();

    }

    private void login_handle()
    {
        String userNameStr = userName.getText().toString();
        String passwordStr = password.getText().toString();

        System.out.println("woowwwwwwwwwwwwwwwwwwww");
        Client client = new Client();
        client.execute(userNameStr+"&"+passwordStr);


    }

    class Server implements Runnable
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

    }

    public void make_toast(String message)
    {
        Toast.makeText(getApplicationContext(), message, Toast.LENGTH_SHORT).show();
    }
}