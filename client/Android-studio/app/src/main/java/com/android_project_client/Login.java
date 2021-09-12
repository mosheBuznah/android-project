package com.android_project_client;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
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
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Objects;

public class Login extends AppCompatActivity {
    EditText userName;
        EditText password;
        Button loginButton;
        Socket client_sock = null;
        String message_from_server = "";
        Client c;

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.login);

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


    }

    private void login_handle()
    {
        String userNameStr = userName.getText().toString();
        String passwordStr = password.getText().toString();

        JSONObject j = new JSONObject();
        try {
            j.put("userName", userNameStr);
            j.put("password", passwordStr);
        } catch (JSONException e) {
            e.printStackTrace();
        }

        c.sendMessage(RequestSerializer.create_message((byte) Constants.LOGIN_REQUEST, j.toString()));
        c.recv();

        int status = 0;
        try {
            status = (int) Objects.requireNonNull(RequestDeserializer.getJsonData(c.getMessageFromServer())).get("status");
        } catch (JSONException e) {
            e.printStackTrace();
        }

        if (status == 1)
        {
            System.out.println("enter");
        }
    }

    public void make_toast(String message)
    {
        Toast.makeText(getApplicationContext(), message, Toast.LENGTH_SHORT).show();
    }
}