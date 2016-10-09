package com.mio.newdynamicc;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText userNameET;
    private EditText passwordET;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.sample_text);
        userNameET = (EditText) findViewById(R.id.userName);
        passwordET = (EditText) findViewById(R.id.password);
        findViewById(R.id.login1).setOnClickListener(this);
        findViewById(R.id.login2).setOnClickListener(this);
        findViewById(R.id.sort).setOnClickListener(this);
        tv.setText(newStringFromJNI());
    }


    public native String newStringFromJNI();


    static {
        System.loadLibrary("native-lib");
    }

    @Override
    public void onClick(View v) {
        int id = v.getId();
        String userName = userNameET.getText().toString().trim();
        String password = passwordET.getText().toString().trim();
        int result = 0;
        String msg;
        if (id == R.id.login1) {
            result = CUtils.loginOne(userName.getBytes(), password.getBytes());
        } else if (id == R.id.login2) {
            result = CUtils.loginTwo(userName, password);
        } else if (id == R.id.sort) {
            startActivity(new Intent(this, SortActivity.class));
        }
        switch (result) {
            case 1:
                msg = "登陆成功";
                break;
            case 2:
                msg = "密码错误";
                break;
            case 3:
                msg = "用户名不存在";
                break;
            default:
                msg = null;
                break;
        }
        if (msg != null)
            Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
    }
}
