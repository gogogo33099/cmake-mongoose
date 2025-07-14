#ifndef IOTNG_H
#define IOTNG_H

#ifdef __cplusplus
extern "C" {
#endif
#include "mongoose.h"

#if MG_ARCH == MG_ARCH_WIN32
#include <locale.h>
#endif

#include "util.h"
#include "log.h"
#include "http_server.h"
#include "mqtt_client.h"

#define IOTNG_SUCCESS 0
#define IOTNG_FAIL 1

// End of line
#if MG_ARCH == MG_ARCH_WIN32
#define IOTNG_EOL "\r\n"
#elif MG_ARCH == MG_ARCH_UNIX
#define IOTNG_EOL "\n"
#else
#define IOTNG_EOL "\r\n"
#endif

#ifdef __cplusplus
}
#endif
#endif  // IOTNG_H