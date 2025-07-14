#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif

int iotng_http_listen(struct mg_mgr *mgr);

#ifdef __cplusplus
}
#endif
#endif  // HTTP_SERVER_H