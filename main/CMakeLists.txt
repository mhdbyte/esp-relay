idf_component_register(
    SRCS "esp-relay.c"
    INCLUDE_DIRS "."
    REQUIRES nvs_flash
    REQUIRES esp_netif
    REQUIRES esp_wifi
)
