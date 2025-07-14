#include "iotng.h"

static char* s_log_buf = NULL;
static size_t s_log_buf_size = 0;
static size_t s_log_pos_s = 0;
static size_t s_log_pos_e = 0;

// Custom log for mongoose
#if MG_ENABLE_CUSTOM_LOG
static const char* log_level_str(int level) {
    const char* ll = "";
    switch (level) {
        case MG_LL_NONE:
            ll = "NONE";
            break;
        case MG_LL_ERROR:
            ll = "ERROR";
            break;
        case MG_LL_INFO:
            ll = "INFO";
            break;
        case MG_LL_DEBUG:
            ll = "DEBUG";
            break;
        case MG_LL_VERBOSE:
            ll = "VERBOSE";
            break;
        default:
            ll = "NONE";
            break;
    }
    return ll;
}

static void pfn_log(char c, void *param) {
    // Write to Console
    putchar(c);
    // Write to memory buffer
    if (s_log_buf) {
        s_log_buf[s_log_pos_e] = c;
        s_log_pos_e++;
        if (s_log_pos_e >= s_log_buf_size) s_log_pos_e = 0;

        if (s_log_pos_s == s_log_pos_e) s_log_pos_s++;
        if (s_log_pos_s >= s_log_buf_size) s_log_pos_s = 0;
    }
    (void) param;
}

static void logc(unsigned char c) {
    pfn_log((char) c, NULL);
}

static void logs(const char *buf, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) logc(((unsigned char *) buf)[i]);
}

// Custom mg_log_prefix
void mg_log_prefix(int level, const char *file, int line, const char *fname) {
    char buf[32];
    size_t n;
    n = mg_snprintf(buf, sizeof(buf), "%s [%s]:"
                    , iotng_timestamp()
                    , log_level_str(level));
    if (n > sizeof(buf) - 2) n = sizeof(buf) - 2;
    while (n < sizeof(buf)) buf[n++] = ' ';
    logs(buf, n - 1);
}

// Custom mg_log
void mg_log(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    mg_vxprintf(pfn_log, NULL, fmt, &ap);
    va_end(ap);
    logs("\r\n", 2);
}
#endif

static unsigned int s_is_hexdump = 0;
int iotng_log_set(int level, size_t size, unsigned int is_hexdump) {
#if MG_ENABLE_CUSTOM_LOG
    mg_log_set_fn(pfn_log, NULL);
#endif
    mg_log_set(level);
    s_is_hexdump = is_hexdump;

    if (s_log_buf) free(s_log_buf);
    s_log_buf_size = (size > IOTNG_LOG_MAX_SIZE) ? IOTNG_LOG_MAX_SIZE : size;
    // Bytes
    s_log_buf_size *= 1024;
    s_log_pos_s = 0;
    s_log_pos_e = 0;
    s_log_buf = NULL;

    if (s_log_buf_size > 0) {
        s_log_buf = malloc(s_log_buf_size);
    }
    return IOTNG_SUCCESS;
}

unsigned int iotng_is_hexdump() {
    return s_is_hexdump;
}