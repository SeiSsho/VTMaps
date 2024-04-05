//
// Created by tts on 4/5/2024.
//

#ifndef VTMAPS_JNIHELPER_H
#define VTMAPS_JNIHELPER_H

#include <pthread.h>
#include <string>
#include <jni.h>
#include <vector>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <filesystem>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif

class JNIHelper {
private:
    mutable pthread_mutex_t _threadMutex;
    std::string _apkInternalPath;
    AAssetManager* p_apkAssetManager;

public:
    JNIHelper(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir);

    ~JNIHelper();

    void Init(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir);

    bool ExtractAssetReturnFilename(std::string assetName, std::string &filename,
                                    bool checkIfFileIsAvailable = false);

    bool ReadFileFromAssetsToBuffer(const char *filename, std::vector<uint8_t> *bufferRef);
};

extern JNIHelper *gHelperObject;

#ifdef __cplusplus
}
#endif

#endif //VTMAPS_JNIHELPER_H
