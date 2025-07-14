#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

const char* iotng_timestamp();

uint64_t iotng_unix_timestamp_ms();

#ifdef __cplusplus
}
#endif
#endif  // UTIL_H