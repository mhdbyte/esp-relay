# esp-relay
A simple 4 relay controller with ESP32

## Hardware

| Module   | Supported |
|----------|-----------|
| ESP32    | Supported |
| ESP32-S2 | Supported |
| ESP32-S3 | Supported |
| ESP32-C3 | Supported |
| ESP32-C5 | Supported |
| ESP32-C6 | Supported |
| ESP32-H2 | Unsupported |
> This project requires an ESP module with Wi-Fi support.

## Requirements
- ESP-IDF 5.5 or later

## How to use
**1.** Before building the project, open `main/esp-relay.c` and configure the following settings:
- Change Wi-Fi SSID & Password 
- Configure GPIO pins used to control the relays
- Configure the relay active state

**2.** Build and flash
```bash
idf.py set-target esp32s3
idf.py menuconfig
idf.py build
idf.py -p PORT flash
```

Replace `esp32s3` with your target module, for example, `esp32` or `esp32s2`.
