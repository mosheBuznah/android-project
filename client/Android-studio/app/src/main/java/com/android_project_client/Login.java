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

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.Serializable;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Objects;

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

        JSONObject j = new JSONObject();
       /* try {
            j.put("userName", userNameStr);
            j.put("password", passwordStr);
        } catch (JSONException e) {
            e.printStackTrace();
        }*/

        //c.sendMessage(RequestSerializer.create_message((byte) Constants.LOGIN_REQUEST, j.toString()));
        c.sendMessage("moshe");
        c.recv();
        Toast.makeText(this, new String(c.getMessageFromServer(), StandardCharsets.UTF_8), Toast.LENGTH_LONG).show();
        /*
        int status = 0;
        try {
            status = (int) Objects.requireNonNull(RequestDeserializer.getJsonData(c.getMessageFromServer())).get("status");
        } catch (JSONException e) {
            e.printStackTrace();
        }

        if (status == 1)
        {
            Intent go = new Intent(Login.this, Posts.class);
            go.putExtra("client", c);
            startActivity(go);
        }
        else
            Toast.makeText(this, "User not exist in the database", Toast.LENGTH_SHORT).show();
        */
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

    public void make_toast(String message)
    {
        Toast.makeText(getApplicationContext(), message, Toast.LENGTH_SHORT).show();
    }
}