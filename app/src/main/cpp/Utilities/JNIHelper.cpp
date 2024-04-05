//
// Created by tts on 4/5/2024.
//

#include "JNIHelper.h"

JNIHelper::JNIHelper(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir) {
    p_apkAssetManager = AAssetManager_fromJava(env, assetManager);

    //Save app internal data storage path -- we will extract assets and save here
    const char *cPathToInternalDir;
    cPathToInternalDir = env->GetStringUTFChars(pathToInternalDir, NULL ) ;
    _apkInternalPath = std::string(cPathToInternalDir);
    env->ReleaseStringUTFChars(pathToInternalDir, cPathToInternalDir);

    //mutex for thread safety
    pthread_mutex_init(&_threadMutex, NULL );
}

JNIHelper::~JNIHelper() {
    pthread_mutex_destroy( &_threadMutex);
}

void JNIHelper::Init(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir) {

}

bool JNIHelper::ExtractAssetReturnFilename(std::string assetName, std::string &filename,
                                           bool checkIfFileIsAvailable) {
    // construct the filename in internal storage by concatenating with path to internal storage
    filename = _apkInternalPath + "/" + std::filesystem::path(assetName).filename().string();
    // check if the file was previously extracted and is available in app's internal dir
    FILE* file = fopen(filename.c_str(), "rb");
    if (file && checkIfFileIsAvailable) {
        __android_log_print(ANDROID_LOG_INFO, "JNIHelper", "Found extracted file in assets: %s", filename.c_str());
        fclose(file);
        pthread_mutex_unlock( &_threadMutex);
        return true;
    }

    // let us look for the file in assets
    bool result = false;

    // AAsset objects are not thread safe and need to be protected with mutex
    pthread_mutex_lock( &_threadMutex);

    // Open file
    AAsset* asset = AAssetManager_open(p_apkAssetManager, assetName.c_str(), AASSET_MODE_STREAMING);

    char buf[BUFSIZ];
    int nb_read = 0;
    if (asset) {
        FILE* out = fopen(filename.c_str(), "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0){
            fwrite(buf, nb_read, 1, out);
        }
        fclose(out);
        AAsset_close(asset);
        result = true;

        __android_log_print(ANDROID_LOG_INFO, "JNIHelper", "Asset extracted: %s", filename.c_str());
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "JNIHelper", "Asset not found: %s", filename.c_str());
    }

    pthread_mutex_unlock( &_threadMutex);
    return result;

}

bool JNIHelper::ReadFileFromAssetsToBuffer(const char *filename, std::vector<uint8_t> *bufferRef) {
    return false;
}
