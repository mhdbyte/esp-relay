#include <stdio.h>
#include <string.h>
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_http_server.h"


#define AP_SSID "esp_relay"
#define AP_PASSWORD "12345678"


extern const char index_html_start[] asm("_binary_index_html_start");
extern const char index_html_end[]   asm("_binary_index_html_end");


esp_err_t
root_handler(httpd_req_t *req) {
    size_t index_len = index_html_end - index_html_start;

    ESP_ERROR_CHECK(httpd_resp_set_type(req, "text/html"));
    ESP_ERROR_CHECK(httpd_resp_send(req, index_html_start, index_len));

    return ESP_OK;
}


esp_err_t
relay_handler(httpd_req_t *req) {
    int req_len = req -> content_len;
    char command[16];
    httpd_req_recv(req, command, req_len);
    command[req_len] = '\0';

    printf("Received: %s\n", command);

    ESP_ERROR_CHECK(httpd_resp_send(req, "Received", 8));
    return ESP_OK;
}


void
web_server_init() {
    const static httpd_uri_t root = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = root_handler,
        .user_ctx = NULL
    };

    const static httpd_uri_t relay = {
        .uri = "/relay",
        .method = HTTP_POST,
        .handler = relay_handler,
        .user_ctx = NULL
    };

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if(httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &root);
        httpd_register_uri_handler(server, &relay);
    }
}


void
wifi_init() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t wifi_init_cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));

    wifi_config_t wifi_cfg = {
        .ap = {
            .ssid = AP_SSID,
            .password = AP_PASSWORD,
            .ssid_len = strlen(AP_SSID),
            .channel = 0,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());
}


void
app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init();
    web_server_init();

}
