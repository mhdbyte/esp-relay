#include <stdio.h>
#include "esp_err.h"
#include "nvs_flash.h"


void
app_main(void) {
    ESP_ERROR_CHECK(nvs_flash_init());

}
