//
// Created by william on 19-9-5.
//

#ifndef STACKAPPLICATION_JNILIB_H
#define STACKAPPLICATION_JNILIB_H

#include <jni.h>
#include <cstring>
#include <cstdlib>

char* jstringToCstr(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = (*env).FindClass("java/lang/String");
    jstring strencode = (*env).NewStringUTF("GB2312");
    jmethodID mid = (*env).GetMethodID(clsstring, "getBytes","(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env).CallObjectMethod(jstr, mid,strencode); // String .getByte("GB2312");
    jsize alen = (*env).GetArrayLength(barr);
    jbyte* ba = (*env).GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*)malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = '\0';
    }
    (*env).ReleaseByteArrayElements(barr, ba, 0); //释放内存
    return rtn;
}

#endif //STACKAPPLICATION_JNILIB_H
