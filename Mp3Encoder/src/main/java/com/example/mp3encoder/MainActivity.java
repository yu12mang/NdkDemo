package com.example.mp3encoder;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.io.File;

public class MainActivity extends AppCompatActivity {


    private final String inputPath = Environment.getExternalStorageDirectory()+
            File.separator+"test_pcm.pcm";

    private final String outputPath = Environment.getExternalStorageDirectory()+
            File.separator+"test_mp3.mp3";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        new Thread(new Runnable() {
            @Override
            public void run() {

                if (new File(inputPath).exists()){

                    Log.i("ddlog", "run: "+inputPath);
                    new Mp3Encoder().init(inputPath,2,128*1024,44100,outputPath);
                }
            }
        }).start();

    }
}
