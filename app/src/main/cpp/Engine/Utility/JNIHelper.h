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
    static std::shared_ptr<JNIHelper> p_instance;
    std::string _apkInternalPath;
    mutable pthread_mutex_t _threadMutex;
    AAssetManager* p_apkAssetManager;

public:
    JNIHelper(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir);

    ~JNIHelper() = default;

    static void Init(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir);
    static void Clean();

    /// Get resource path in folder <i>assets</i> to use in C/C++ code
    /// \note this will extract path, then create a file ( <b>it duplicate the file, must find better way or</b> path to use in C/C++ code
    /// \param assetName Asset path in folder "<i>assets</i>"
    /// \param filename path to use in C/C++ code
    /// \param checkIfFileIsAvailable
    /// \return <i>filename</i> is valid or invalid
    static bool ExtractAssetReturnFilename(std::string assetName, std::string &filename,
                                           bool checkIfFileIsAvailable = true);

    static bool ReadFileFromAssetsToBuffer(const char *filename, std::vector<uint8_t> *bufferRef);
};

#ifdef __cplusplus
}
#endif

#endif //VTMAPS_JNIHELPER_H
