#ifndef VTMAPS_LOGGER_H
#define VTMAPS_LOGGER_H

#include <android/log.h>

#define LOG_INFO(tag, ...) __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__)
#define LOG_ERROR(tag, ...) __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)
#define LOG_DEBUG(tag, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)
#define LOG_FATAL(tag, ...) __android_log_print(ANDROID_LOG_FATAL, tag, __VA_ARGS__)
#define LOG_WARN(tag, ...) __android_log_print(ANDROID_LOG_WARNING, tag, __VA_ARGS__)

#endif //VTMAPS_LOGGER_H
