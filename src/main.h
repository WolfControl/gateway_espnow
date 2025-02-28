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

// ---------- provisioning.h ---------- //

TaskHandle_t otaReceiveSerialTaskHandle;
esp_ota_handle_t ota_handle;
SemaphoreHandle_t mutex;
EventGroupHandle_t bridge_event_group;
EventGroupHandle_t ota_event_group;


const int txPin = 1;
const int rxPin = 2;

// ---------- provisioning.h ---------- //

char *deviceId;

char* firmwareVersionEspNow = "SETDURINGCOMPILATION";
char* espnowmac;

esp_partition_t *update_partition = NULL;

// ---------- led.h ---------- //


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