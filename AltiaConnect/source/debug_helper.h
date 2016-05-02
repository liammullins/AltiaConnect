#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define ALTIA_CLEAN_ERRORNO() (errno == 0 ? "None" : strerror(errno))

#define ALTIA_LOG_ERROR(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILENAME__, __LINE__, ALTIA_CLEAN_ERRORNO(), ##__VA_ARGS__)

#define ALTIA_LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILENAME__, __LINE__, ALTIA_CLEAN_ERRORNO(), ##__VA_ARGS__)

#define ALTIA_LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)

#endif