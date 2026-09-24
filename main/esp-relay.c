#include <stdio.h>
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"


void
wifi_init() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

}


void
app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init();

}
