#include "jni.h"
#include "../Utilities/JNIHelper.h"

JNIHelper* g_HelperObject = nullptr;


extern "C"
JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainActivity_CreateObjectNative(JNIEnv *env, jobject thiz,
                                                        jobject asset_manager,
                                                        jstring path_to_internal_dir) {
    g_HelperObject = new JNIHelper(env, thiz, asset_manager, path_to_internal_dir);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainActivity_DeleteObjectNative(JNIEnv *env, jobject thiz) {
    if (g_HelperObject)
        delete g_HelperObject;
}