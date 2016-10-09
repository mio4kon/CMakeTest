//
// Created by mio4kon on 16/10/8.
//

#include <jni.h>
#include <string>
#include<Android/log.h>

#define TAG "Mio4kon"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)


extern "C" {

/**
 * byte 转出 char
 */
char *jbyte2Char(JNIEnv *env, jbyteArray array) {
    jbyte *datas = env->GetByteArrayElements(array, NULL);
    jsize len = env->GetArrayLength(array);

    char *cstr = (char *) malloc(len + 1);
    memcpy(cstr, datas, len);
    cstr[len] = '\0';
    env->ReleaseByteArrayElements(array, datas, 0);
    return cstr;
}

char *string2Char(JNIEnv *env, jstring str) {
    jclass clazz = env->FindClass("java/lang/String");
    //第三个参数为方法的签名 为了区分重载方法 javap -s -p java/lang/String
    jmethodID mid = env->GetMethodID(clazz, "getBytes", "(Ljava/lang/String;)[B");
    jstring jencode = env->NewStringUTF("utf-8");
    jbyteArray array = (jbyteArray) env->CallObjectMethod(str, mid, jencode);
    char *cstr = jbyte2Char(env,array);
    return cstr;
}

/**
 * check 方法
 */
int check(char *name, char *password) {
    if (strcmp(name, "mio4kon") == 0) {
        if (strcmp(password, "123") == 0) {
            return 1;
        } else {
            return 2;
        }
    } else {
        return 3;
    }
}

JNIEXPORT jint JNICALL
Java_com_mio_newdynamicc_CUtils_loginOne(JNIEnv *env, jclass type, jbyteArray username_,
                                         jbyteArray password_) {
    LOGD("######## Java_com_mio_newdynamicc_CUtils_loginOne ########");
    char *cusername = jbyte2Char(env, username_);
    char *cpassword = jbyte2Char(env, password_);
    return check(cusername, cpassword);
}


JNIEXPORT jint JNICALL
Java_com_mio_newdynamicc_CUtils_loginTwo(JNIEnv *env, jclass type, jstring username_,
                                         jstring password_) {
    LOGD("######## Java_com_mio_newdynamicc_CUtils_loginTwo ########");
    char *cusername = string2Char(env, username_);
    char *cpassword = string2Char(env, password_);
    return check(cusername, cpassword);
}

}

