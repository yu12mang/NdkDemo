package com.example.loganyu.ndkdemo;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.File;

import javax.security.auth.login.LoginException;

public class MainActivity extends AppCompatActivity {

    private final String TAG = "------DDLog------";
    static {
        System.loadLibrary("native-lib");
    }

    //实例域
    private String instanceField = "Instance Field";

    //静态域
    private static String staticField = "Static Field";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);

        IOtest(Environment.getExternalStorageDirectory()+File.separator+"1.txt");
        try{

            stringFromJNI();
            customObjTest(new ParamInfo());

        }catch (Exception e){
            Log.i(TAG, "onCreate: "+e.getMessage());
        }

        //test
        {
            javaArrToCArr(new int[]{1,2});
        }

    }

    public native void customObjTest(ParamInfo info);

    public native void IOtest(String path);

    public native String stringFromJNI();
    public native static void staticFunc();
    //java string to c string
    public native static void javaStrToCString(String javaStr);

    public native static void javaArrToCArr(int[] intArr);


    private String instanceMethod(){
        return "Instance Method";
    }


    private static String staticMethod(){ return "Static Method";
    }

    

}
