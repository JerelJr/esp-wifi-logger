WiFi Logger component
====================
ESP32 WiFi logger - Log messages over WiFi, using either TCP, UDP or websockets (future releases)
* Generates log messages with same format as ESP-IDF Logging API
* Follows ESP-IDF color pattern for different log levels.

## Requirements

* `protocol_examples_common (esp-idf/examples/common_components/)`

## Installation

```
cd <your_esp_idf_project>
mkdir components
cd components
git clone https://github.com/VedantParanjape/esp-wifi-logger.git wifi_logger
```

## Usage

### How to receive logs

* `sudo apt-get install netcat` netcat is required to receive logs
* `nc -lu <PORT>` receive logs when ***UDP*** is used as network protocol
* `nc -l <PORT>` receive logs when ***TCP*** is used as network protocol

* **Example**: Assume, *port* is **1212** over TCP, command will be: `nc -l 1212`
### How to use in ESP-IDF Projects
```
wifi_log_e() - Generate log with log level ERROR
wifi_log_w() - Generate log with log level WARN
wifi_log_i() - Generate log with log level INFO
wifi_log_d() - Generate log with log level DEBUG
wifi_log_v() - Generate log with log level VERBOSE
```

* Usage pattern same as, `ESP_LOGX()`
* Use `wifi_log()_x` function to print logs over wifi
* Example: `wifi_log(TAG, "%s", "logger test");`
* Call `start_wifi_logger()` in `void app_main()` to start the logger. Logging function `wifi_log` can be called to log messages

* Configure `menuconfig`
  * `Example Connection Configuration` *Set WiFi SSID and password*
  * `Component config`
  * `WiFi Logger configuration`
    * `Network Protocol (TCP/UDP)` - Set network protocol to be used 
    * `Server IP Address` - Set the IP Address of the server which will receive log messages sent by ESP32
    * `Port` - Set the Port of the server

*IP Address of the server can be found out by running `ifconfig` on a linux machine*

## Configuration

```
idf.py menuconfig
```
* `Example Connection Configuration`
  * `WiFi SSID` -  Set WiFi SSID to connect
  * `WiFi Password` - Set WiFi Password

* `Component config`
  * `WiFi Logger configuration`
    * `Network Protocol (TCP/UDP)` - Set network protocol to be used 
    * `Server IP Address` - Set the IP Address of the server which will receive log messages sent by ESP32
    * `Port` - Set the Port of the server
    * `Queue Size` - ***Advanced Config, change at your own risk***** Set the freeRTOS Queue size used to pass log messages to logger task.
    * `logger buffer size` - ***Advanced Config, change at your own risk*** Set the buffer size of char array used to generate log messages in ESP format

## Example
```
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi_logger.h"


void app_main(void)
{
    start_wifi_logger(); // Start wifi logger

    while(1)
    {
        wifi_log_e("test", "%s %d %f", "hello world wifi logger", 43, 45.341223242); // write log over wifi with log level -> ERROR
        wifi_log_w("test", "%s %d %f", "hello world wifi logger", 43, 45.341223242); // write log over wifi with log level -> WARN
        wifi_log_i("test", "%s %d %f", "hello world wifi logger", 43, 45.341223242); // write log over wifi with log level -> INFO
        wifi_log_d("test", "%s %d %f", "hello world wifi logger", 43, 45.341223242); // write log over wifi with log level -> DEBUG
        wifi_log_v("test", "%s %d %f", "hello world wifi logger", 43, 45.341223242); // write log over wifi with log level -> VERBOSE

        vTaskDelay(100);  // Wait for 100ms, prevent watchdog from triggering a reset
    }
}
```