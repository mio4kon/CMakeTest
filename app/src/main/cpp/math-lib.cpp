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
 * 排序
 */
void insertSort(int *data, int len) {
    int temp = 0;
    for (int i = 1; i < len; i++) {
        temp = data[i];
        for (int j = i - 1; j > 0; j--) {
            if (data[j] > temp) {
                data[j + 1] = data[j];
            } else {
                break;
            }
            data[j + 1] = temp;
        }

    }
}

/**
 * 这里名字不是JAVA_包名_方法名,而通过动态注册的方式可以随意命名
 */
void native_insertSortArray(JNIEnv *env, jclass type, jintArray data_) {
    jint *data = env->GetIntArrayElements(data_, NULL);
    jsize len = env->GetArrayLength(data_);
    insertSort(data, len);
    env->ReleaseIntArrayElements(data_, data, 0);
}


/**
 *  第一个  inserSortArray : java method name
 *  第二个  ([I)V          : method 签名
 *  签名获取方法:
 *  cd app/build/intermediates/classes/debug
 *  javap -s -p com/mio/newdynamicc/CUtils
 *
 *  第三个 c方法指针
 */
static JNINativeMethod gMethods[] = {
        {
                "inserSortArray",
                "([I)V",
                (void *) native_insertSortArray
        }
};


static int registerNativeMethod(JNIEnv *env) {
    jclass clazz = env->FindClass("com/mio/newdynamicc/CUtils");
    jint result = env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
    return result;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    if (registerNativeMethod(env)<0) {        return -1;    }
    return JNI_VERSION_1_4;//必须返回这个值，否则报错
}
}

