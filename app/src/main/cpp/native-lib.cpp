#include <jni.h>
#include <string>
#include <gperf.h>
#include <gmath.h>
#include "adder.h"

extern "C" JNIEXPORT jstring Java_com_thanhdo_vtmaps_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++" + std::to_string(powerOf2(2));
    return env->NewStringUTF(hello.c_str());
}