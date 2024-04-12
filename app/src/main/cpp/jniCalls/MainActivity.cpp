#include "jni.h"
#include "../Utilities/JNIHelper.h"
#include "../Viewer.h"

extern "C" JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainActivity_CreateObjectNative(JNIEnv *env, jobject thiz,
                                                        jobject asset_manager,
                                                        jstring path_to_internal_dir) {
//    g_HelperObject = new JNIHelper(env, thiz, asset_manager, path_to_internal_dir);
    JNIHelper::Init(env, thiz, asset_manager, path_to_internal_dir);

}

extern "C" JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainActivity_DeleteObjectNative(JNIEnv *env, jobject thiz) {
    JNIHelper::Clean();
}

std::shared_ptr<Viewer> _viewer = std::make_shared<Viewer>();

extern "C" JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainRenderer_SurfaceCreate(JNIEnv *env, jclass clazz,
                                                   jobject asset_manager) {
    // TODO: implement SurfaceCreate()
    _viewer->Create();
}

extern "C" JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainRenderer_SurfaceChange(JNIEnv *env, jclass clazz, jint width,
                                                   jint height) {
    // TODO: implement SurfaceChange()
    _viewer->Change(width, height);
}
extern "C" JNIEXPORT void JNICALL
Java_com_thanhdo_vtmaps_MainRenderer_DrawFrame(JNIEnv *env, jclass clazz) {
    // TODO: implement DrawFrame()
    _viewer->Draw();
}