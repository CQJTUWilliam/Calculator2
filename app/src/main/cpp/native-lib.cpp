#include <jni.h>
#include <string>
#include "JniLib.h"
#include "stackapplication.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_learning_calculator2_MainActivity_countInfix(JNIEnv *env, jobject thiz, jstring infix) {
    const char *c_str = jstringToCstr(env,infix);
    string* postfix = infixToPostfix(c_str);
    double result =  countPostfix(postfix);
    delete []postfix;
    return result;
}