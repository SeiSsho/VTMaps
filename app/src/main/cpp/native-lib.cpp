#include <jni.h>
#include <string>
#include <VG/openvg.h>
#include <VG/vgu.h>
#include <VG/vgext.h>
#include <VG/vgplatform.h>

extern "C" JNIEXPORT jstring Java_com_thanhdo_vtmaps_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}