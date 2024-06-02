#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "cJSON.h"
#include "esp_vfs_dev.h"
#include "string.h"

#include "messaging.h"
#include "provisioning.h"
#include "led.h"

// ---------- messaging.h ---------- //

esp_now_peer_info_t broadcastPeer;
TaskHandle_t receiveSerialTaskHandle, receiveESPNowTaskHandle, sendESPNowTaskHandle, sendSerialTaskHandle, serialDaemonTaskHandle;
QueueHandle_t incomingESPNowQueue, outgoingESPNowQueue, incomingSerialQueue, outgoingSerialQueue;

const int txPin = 1;
const int rxPin = 2;

// ---------- provisioning.h ---------- //

char *deviceId;

char* firmwareVersionEspNow = "0.0.1";
char* espnowmac;

rgb_led_t bootLED = {
    LEDC_CHANNEL_0,
    5,
    LEDC_CHANNEL_1,
    6,
    LEDC_CHANNEL_2,
    7};
 
led_t activityLED1 = {LEDC_CHANNEL_6, 8};

// Unused LEDs
rgb_led_t connectivityLED = {};
led_t activityLED2 = {};