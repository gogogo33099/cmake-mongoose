#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#define IOTNG_ERROR(args) MG_LOG(MG_LL_ERROR, args)
#define IOTNG_INFO(args) MG_LOG(MG_LL_INFO, args)
#define IOTNG_DEBUG(args) MG_LOG(MG_LL_DEBUG, args)
#define IOTNG_VERBOSE(args) MG_LOG(MG_LL_VERBOSE, args)

#define IOTNG_HEXDUMP mg_hexdump

#if defined(TARGET_HTNICE_GC65XX)
// 1*1024 KB
#define IOTNG_LOG_MAX_SIZE 1*1024
#elif defined(TARGET_HTNICE_GT675X)
// 5*1024 KB
#define IOTNG_LOG_MAX_SIZE 5*1024
#else
// 10*1024 KB
#define IOTNG_LOG_MAX_SIZE 10*1024
#endif

int iotng_log_set(int level, size_t size, unsigned int is_hexdump);

unsigned int iotng_is_hexdump();

#ifdef __cplusplus
}
#endif
#endif  // LOG_H