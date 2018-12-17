#include <jni.h>
#include <string>
#include <stdio.h>
#include "logutil.h"

using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_loganyu_ndkdemo_MainActivity_stringFromJNI(JNIEnv *env, jobject instance/* this */) { //非static方法 jobject
    string hello = "Hello from C++";

#if false
    {

        jclass  clazz = env->GetObjectClass(instance);


        //获取实例域ID
        // TODO 注意：第三个参数里一定要以 ; 结尾
        jfieldID  instanceFieldId = env->GetFieldID(clazz,"instanceField","Ljava/lang/String;");
        //获取实例域
        // TODO 注意：方法里的参数是instance 因为是实例对象是以对象为依赖而存在的
        jstring  instanceStr = (jstring)env->GetObjectField(instance,instanceFieldId);
        LOGI("instanceFieldId1 %d",instanceFieldId);

        const char *javaStr = env->GetStringUTFChars((jstring)instanceStr, 0);
        LOGI("%s",javaStr);


        //获取静态域ID
        jfieldID  staticFieldId = env->GetStaticFieldID(clazz,"staticField","Ljava/lang/String;");
        LOGI("staticFieldId %d ",staticFieldId);

        //获取jstring对象
        // TODO 注意：方法里的参数是clazz 因为是静态对象是以class为依赖而存在的
        jstring staticField= (jstring)env ->GetStaticObjectField(clazz,staticFieldId);

        //jstring转换成可以打印的char
        const char *javaStr1 = env->GetStringUTFChars(staticField, 0);

        LOGI("staticField %s ",javaStr1);



        //获取实例方法
        jmethodID  instanceMethodId = env->GetMethodID(clazz,"instanceMethod","()Ljava/lang/String;");

        //调用实例方法
                jstring  instanceMethodResult = (jstring)(env->CallObjectMethod(instance, instanceMethodId));
        //jstring转换成可以打印的char
        const char *javaStr2 = env->GetStringUTFChars(instanceMethodResult, 0);

        LOGI("instanceMethodResult %s ",javaStr2);


        //获取静态方法
        jmethodID  staticMethodId = env->GetStaticMethodID(clazz,"staticMethod","()Ljava/lang/String;");

        //调用静态方法
        jstring  staticMethodResult = (jstring)(env->CallStaticObjectMethod(clazz, staticMethodId));
        //jstring转换成可以打印的char
        const char *javaStr3 = env->GetStringUTFChars(staticMethodResult, 0);

        LOGI("staticMethodResult %s ",javaStr3);
    }
#endif

#if false
    {
        jclass  clazz = env->FindClass("java/lang/Exception");
        if (clazz != 0){
            jstring result = env->NewStringUTF(hello.c_str());
            env->ThrowNew(clazz,"there is jni exception.");

            //TODO 注意：一定要在抛出异常时把代码中该释放的先释放掉 否则会有ANR
            LOGD("hello");
            return result;
        }
    }
#endif

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_loganyu_ndkdemo_MainActivity_staticFunc(JNIEnv *env,
                                                         jclass type) {//static方法 jclass


}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_loganyu_ndkdemo_MainActivity_javaStrToCString(JNIEnv *env, jclass type,
                                                               jstring javaStr_) {
    //转换成c语言的string
    const char *javaStr = env->GetStringUTFChars(javaStr_, 0);




    //释放字符串
    env->ReleaseStringUTFChars(javaStr_, javaStr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_loganyu_ndkdemo_MainActivity_javaArrToCArr(JNIEnv *env, jclass clazz,
                                                            jintArray intArr_) {
    jint *intArr = env->GetIntArrayElements(intArr_, NULL);

#if false
    {
        //创建原生array
        jintArray array = env->NewIntArray(10);

        //将java数组复制到c数组中
        jint nativeArr[10];
        env->GetIntArrayRegion(array, 0, 10, nativeArr);

        //从c数组向java数组提交修改
        env->SetIntArrayRegion(array, 0, 10, nativeArr);
    }
#endif


//字节缓冲区
#if false
    {
        //创建1024个字节的缓冲区
        unsigned char *buffer = (unsigned char *) malloc(1024);

        jobject directBuffer = env->NewDirectByteBuffer(buffer, 1024);

        //通过java字节缓冲区获取原生字节数组
        unsigned char *buffer1;
        buffer = (unsigned char *) env->GetDirectBufferAddress(directBuffer);
    }
#endif

    env->ReleaseIntArrayElements(intArr_, intArr, 0);
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_loganyu_ndkdemo_MainActivity_IOtest(JNIEnv *env, jobject instance, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);

    /**
     * r:只读
     * w:只写
     * a：以附加方式打开文件 保存文件内容 新输出的内容附加到文件结尾处 如果该文件不存在 就打开一个新文件
     * r+：读写模式下打开文件
     * w+：在读写模式下打开文件 如果该文件已经存在 它会被截断 截断后文件长度为0
     * a+：打开文件进行读取和附和 在读取时 起始文件的位置被设定在开头 而附加时被设定在文件结尾
     */


    //写入文件
#if false
    {
        //TODO 注意：一定要在使用完成后关闭流 否则会导致写入不成功
        FILE *stream = fopen(path,"w");

        if (NULL == stream){
            LOGE("File is Null:%s",path);
        }else{
            //用 size_t fwrite();写入文件
            char data[] = {'w','e','l','l','o','\n'};
            size_t count = sizeof(data) / sizeof(data[0]);
            if (count != fwrite(data, sizeof(char),count,stream)){
                //向流中写数据时产生错误
                LOGE("there is some error");
            }else{
                LOGE("write success");

            }

            //int fputs();向流中写入字符数列

            fflush(stream);//刷新

            const char *data1 = "i am data1 \n";
            if(EOF == fputs(data1,stream)){
                //向流中写数据时产生错误
                LOGE("there is some error1");
            }else{
                LOGE("write success1");

            }

            //int fprintf();向流中写入格式化的数据
            fflush(stream);//刷新
            if (0 > fprintf(stream,"\n the %s is %d","number",2)){
                //向流中写数据时产生错误
                LOGE("there is some error2");
            }else{
                LOGE("write success2");
                fclose(stream);
            }

        }
    }
#endif


    //读取文件
#if true
    {
        //TODO 注意：一定要在使用完成后关闭流 否则会导致写入不成功
        FILE *stream = fopen(path,"r");

        if (NULL == stream){
            LOGE("File is Null:%s",path);
        }else{
            //int fread();从流中读取4个字符
            char buffer[5];
            size_t  count = 4;

            if(count != fread(buffer, sizeof(char),count,stream)){
                //向流中读数据时产生错误
                LOGE("read file error: %s",path);
            }else{
                LOGI("read result:%s",buffer);
            }

            //int fgets();从流中读取字符数列
            char buffer1[1024];
            //检查是否到文件结尾 如果到达结尾会返回非0
            while (0 == feof(stream)){
                if (NULL == fgets(buffer1,1024,stream)){
                    //向流中读数据时产生错误
                    LOGE("read file error1: %s",path);
                }else{
                    LOGI("read result1:%s",buffer1);
                }
            }

            /**
             * int fseek();搜索位置
             *
             * SEEK_SET 开头位置
             * SEEK_CUR 当前位置
             * SEEK_END 结尾位置
             */

            fclose(stream);
        }
    }
#endif
    env->ReleaseStringUTFChars(path_, path);
}


typedef struct{
    bool boolValue;
    char charValue;
    double doubleValue ;
    int intValue;
    char array[255];
    char str[255];
}ParamInfo;



extern "C"
JNIEXPORT void JNICALL
Java_com_example_loganyu_ndkdemo_MainActivity_customObjTest(JNIEnv *env, jobject instance,jobject jobj) {

    //java obj  to  c obj
#if false
{
    ParamInfo info ;

    jclass clazz = env->FindClass("com/example/loganyu/ndkdemo/ParamInfo");

    jfieldID intId = env->GetFieldID(clazz, "intValue", "I");
    info.intValue = env->GetIntField(jobj, intId);


    jfieldID boolId = env->GetFieldID(clazz, "boolValue", "Z");
    info.boolValue = env->GetIntField(jobj, boolId);

    jfieldID charId = env->GetFieldID(clazz, "charValue", "C");
    info.charValue = env->GetIntField(jobj, charId);

    LOGI("info.intValue:%d",info.intValue);
    LOGI("info.boolValue:%d",info.boolValue);
    LOGI("info.charValue:%c",info.charValue);
}
#endif

    // c obj to java obj
#if true
{
    ParamInfo info ;

    info.intValue = 8;

    jclass javaObj = env->FindClass("com/example/loganyu/ndkdemo/ParamInfo");

    jobject javaInfo = env->AllocObject(javaObj);

    jfieldID javaIntId = env->GetFieldID(javaObj, "intValue", "I");

    env->SetIntField(javaInfo, javaIntId, info.intValue);

    //return javaInfo;
}
#endif

}
