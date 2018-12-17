package com.example.mp3encoder;

public class Mp3Encoder {
    static {
        System.loadLibrary("native-lib");
    }

    public native  void init(String pcmPath,
                             int channels,
                             int bitRate,
                             int SampleRate,
                             String mp3Path);


    public native  void encode();

    public native  void destroy();

}
