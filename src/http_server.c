#include "iotng.h"

static const char *s_http_addr = "http://0.0.0.0:8000";  // HTTP port
static const char *s_root_dir = "web_root";
#define MQTT_SERVER "mqtt://broker.hivemq.com:1883"
#define MQTT_PUBLISH_TOPIC "mg/my_device"
#define MQTT_SUBSCRIBE_TOPIC "mg/#"

static struct config {
  char *url, *pub, *sub;
} s_config;

// Try to update a single configuration value
static void update_config(struct mg_str json, const char *path, char **value) {
  char *jval;
  if ((jval = mg_json_get_str(json, path)) != NULL) {
    free(*value);
    *value = strdup(jval);
  }
}

static void fn(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_OPEN && c->is_listening) {
    c->is_hexdumping = iotng_is_hexdump();
    s_config.url = strdup(MQTT_SERVER);
    s_config.pub = strdup(MQTT_PUBLISH_TOPIC);
    s_config.sub = strdup(MQTT_SUBSCRIBE_TOPIC);
  } else if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (mg_match(hm->uri, mg_str("/api/config/get"), NULL)) {
      mg_http_reply(c, 200, "Content-Type: application/json\r\n",
                    "{%m:%m,%m:%m,%m:%m}\n", MG_ESC("url"),
                    MG_ESC(s_config.url), MG_ESC("pub"), MG_ESC(s_config.pub),
                    MG_ESC("sub"), MG_ESC(s_config.sub));
    } else if (mg_match(hm->uri, mg_str("/api/config/set"), NULL)) {
      struct mg_str json = hm->body;
      update_config(json, "$.url", &s_config.url);
      update_config(json, "$.pub", &s_config.pub);
      update_config(json, "$.sub", &s_config.sub);
      mg_http_reply(c, 200, "", "ok\n");
    } else {
      struct mg_http_serve_opts opts = {.root_dir = s_root_dir};
      mg_http_serve_dir(c, ev_data, &opts);
    }
  }
}

int iotng_http_listen(struct mg_mgr *mgr) {
    mg_http_listen(mgr, s_http_addr, fn, NULL);  // Create HTTP listener
    return IOTNG_SUCCESS;
}