#include "iotng.h"

// Handle interrupts, like Ctrl-C
static int s_signo;
static void signal_handler(int signo) {
    s_signo = signo;
}

int main(void) {
    // Event manager
    struct mg_mgr mgr;
    // Setup signal handlers - exist event
    signal(SIGINT, signal_handler);
    // manager loop on SIGINT and SIGTERM
    signal(SIGTERM, signal_handler);
#if MG_ARCH == MG_ARCH_WIN32
    // 程序的中文编码为UTF-8
    setlocale(LC_ALL, "zh_CN.UTF-8");
#endif
    iotng_log_set(MG_LL_DEBUG, 10, 1);

    printf("你好你好\r\n");

    // Initialise event manager
    mg_mgr_init(&mgr);

    // Start mqtt client
    iotng_mqtt_connect(&mgr);
    // Start web server
    iotng_http_listen(&mgr);

    // Infinite event loop
    while (s_signo == 0) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);

    return 0;
}
