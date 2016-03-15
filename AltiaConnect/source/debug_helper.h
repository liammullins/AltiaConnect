//Thanks Zed's 'Awesome Debug Macros'!

#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>
//for linux use '/' windows use '\\'

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#ifdef NDEBUG
#define debug(M, ...)
#else
#define ALTIA_DEBUG(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define ALTIA_CLEAN_ERRORNO() (errno == 0 ? "None" : strerror(errno))

#define ALTIA_LOG_ERROR(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILENAME__, __LINE__, ALTIA_CLEAN_ERRORNO(), ##__VA_ARGS__)

#define ALTIA_LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILENAME__, __LINE__, ALTIA_CLEAN_ERRORNO(), ##__VA_ARGS__)

#define ALTIA_LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)

#define ALTIA_CHECK_DEBUG(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif