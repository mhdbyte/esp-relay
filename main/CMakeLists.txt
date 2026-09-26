idf_component_register(
	SRCS "esp-relay.c"
	INCLUDE_DIRS "."
	EMBED_TXTFILES "../index.html"
	REQUIRES nvs_flash esp_netif esp_wifi esp_http_server esp_driver_gpio
)
