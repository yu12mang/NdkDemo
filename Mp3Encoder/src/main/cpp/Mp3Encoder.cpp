#include <jni.h>
#include <string>
#include <stdio.h>
#include "mp3_encoder.h"
#include "logutil.h"

using namespace std;




extern "C"
JNIEXPORT void JNICALL
Java_com_example_mp3encoder_Mp3Encoder_init(JNIEnv *env, jobject instance, jstring pcmPath_,
                                            jint channels, jint bitRate, jint SampleRate,
                                            jstring mp3Path_) {
    const char *pcmPath = env->GetStringUTFChars(pcmPath_, 0);
    const char *mp3Path = env->GetStringUTFChars(mp3Path_, 0);

    LOGI("encode");

    mp3_encoder *encoder;
    encoder = new mp3_encoder();
    int result = encoder->Init(pcmPath,mp3Path,SampleRate,channels,bitRate);
    if (result == SUCCESS){
        encoder->Encode();
        encoder->Destroy();
    }

    env->ReleaseStringUTFChars(pcmPath_, pcmPath);
    env->ReleaseStringUTFChars(mp3Path_, mp3Path);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_mp3encoder_Mp3Encoder_encode(JNIEnv *env, jobject instance) {




}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mp3encoder_Mp3Encoder_destroy(JNIEnv *env, jobject instance) {

    // TODO

}

