#include "iotng.h"

static char s_datetime[32] = {0};
const char* iotng_timestamp() {
    // Get the current (Seconds)
    time_t now = time(NULL);
    // Convert to local time
    struct tm *t = localtime(&now);

    // YYYY-MM-DD HH:MM:SS
    strftime(s_datetime, sizeof(s_datetime), "%Y-%m-%d %H:%M:%S", t); 
    return s_datetime;
}

uint64_t iotng_unix_timestamp_ms() {
#if MG_ARCH == MG_ARCH_WIN32
    FILETIME ft;
    ULARGE_INTEGER li;

    // 获取自 1601-01-01 至今的 100 纳秒数
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;

    // 转换为自 1970-01-01 的毫秒数（减去 11644473600000ms 的偏移）
    uint64_t timestamp = (li.QuadPart - 116444736000000000ULL) / 10000;
    return timestamp;
#elif MG_ARCH == MG_ARCH_UNIX
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
#else
    return 0;
#endif
}