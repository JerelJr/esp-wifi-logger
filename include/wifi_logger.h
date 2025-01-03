#ifndef WIFI_LOGGER_H
#define WIFI_LOGGER_H

#include "tcp_handler.h"
#include "udp_handler.h"
#include "websocket_handler.h"
#include "utils.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESSAGE_QUEUE_SIZE CONFIG_MESSAGE_QUEUE_SIZE
#define BUFFER_SIZE CONFIG_BUFFER_SIZE

#define wifi_log_e(TAG, fmt, ...) generate_log_message(ESP_LOG_ERROR, TAG, __LINE__, __func__, fmt, __VA_ARGS__);
#define wifi_log_w(TAG, fmt, ...) generate_log_message(ESP_LOG_WARN, TAG, __LINE__, __func__, fmt, __VA_ARGS__);
#define wifi_log_i(TAG, fmt, ...) generate_log_message(ESP_LOG_INFO, TAG, __LINE__, __func__, fmt, __VA_ARGS__);
#define wifi_log_d(TAG, fmt, ...) generate_log_message(ESP_LOG_DEBUG, TAG, __LINE__, __func__, fmt, __VA_ARGS__);
#define wifi_log_v(TAG, fmt, ...) generate_log_message(ESP_LOG_VERBOSE, TAG, __LINE__, __func__, fmt, __VA_ARGS__);

/**
 * @brief Initialises message queue
 *
 * @return esp_err_t ESP_OK - if queue init sucessfully, ESP_FAIL - if queue init failed
 **/
esp_err_t init_queue(void);
/**
 * @brief Initialises and connects to wifi
 **/
void init_wifi(void);
/**
 * @brief Sends log message to message queue
 *
 * @param log_message log message to be sent to the queue
 * @return esp_err_t ESP_OK - if queue init sucessfully, ESP_FAIL - if queue init failed
 **/
esp_err_t send_to_queue(char* log_message);
/**
 * @brief Receive data from queue. Timeout is set to portMAX_DELAY, which is around 50 days (confirm from esp32 specs)
 *
 * @return char* - returns log message received from the queue, returns NULL if error
 **/
char* receive_from_queue(void);
/**
 * @brief generates log message, of the format generated by ESP_LOG function
 *
 * @param level set ESP LOG level {E, W, I, D, V}
 * @param TAG Tag for the log message
 * @param line line
 * @param func func
 * @param fmt fmt
 */
void generate_log_message(esp_log_level_t level, const char *TAG, int line, const char *func, const char *fmt, ...);
/**
 * @brief route log messages generated by ESP_LOGX to the wifi logger
 *
 * @param fmt logger string format
 * @param tag arguments
 * @return int return value of vprintf
 */
int system_log_message_route(const char* fmt, va_list tag);
/**
 * @brief wrapper function to start wifi logger
 *
 */
void start_wifi_logger(void);
/**
 * @brief function which handles sending of log messages to server by TCP or UDP
 *
 */
void wifi_logger();
/*
 * @brief A common wrapper function to check connection status for all interfaces
 *
 * @param handle_t Interface handle
 * @return bool True if connected
 */
bool is_connected(void* handle_t);

#ifdef __cplusplus
}
#endif

#endif

