package com.android_project_client;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.method.LinkMovementMethod;
import android.view.View;
import android.widget.TextView;

public class Login extends AppCompatActivity {

    TextView forgotPasswordTv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);
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
}