#ifndef __YARN_SIMULATOR_UTILS_H__
#define __YARN_SIMULATOR_UTILS_H__

#include <cstdio>

#define String std::string

#define VALID(ptr) (NULL != (ptr))
#define INVALID(ptr) (NULL == (ptr))
#define UNUSED(arg) ((void)arg)

#define INIT(ptr) (memset((ptr), 0, sizeof(*(ptr))))

// LOG
#define LOG_PREFIX printf("[YarnSimualtor] ");
#define LOG_INFO_PREFIX LOG_PREFIX printf("[INFO] ");
#define LOG_WARN_PREFIX LOG_PREFIX printf("[WARN] ");
#define LOG_INFO(fmt, arg...) LOG_INFO_PREFIX printf(fmt, ##arg); printf("\n")
#define LOG_WARN(fmt, arg...) LOG_WARN_PREFIX printf(fmt, ##arg); printf("\n")

#endif
