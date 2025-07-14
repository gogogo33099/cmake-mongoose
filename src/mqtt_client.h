#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

int iotng_mqtt_connect(struct mg_mgr *mgr);

#ifdef __cplusplus
}
#endif
#endif  // MQTT_CLIENT_H