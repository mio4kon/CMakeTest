#include <jni.h>
#include <string>



jstring
Java_com_mio_newdynamicc_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_mio_newdynamicc_MainActivity_newStringFromJNI(JNIEnv *env, jobject instance) {
    std::string hello = " String from C++";
    return env->NewStringUTF(hello.c_str());
}

