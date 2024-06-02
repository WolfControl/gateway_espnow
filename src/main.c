#include "main.h"

/* --------------------------- Main Function --------------------------- */
void app_main(void)
{
    static const char *TAG = "MAIN";
    esp_err_t status;

    status = setupWolfESPNowGateway();
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize gateway: %s", esp_err_to_name(status));
        return;
    }

    ESP_LOGI(TAG, "Initialization complete. Waiting for incoming messages...");

}
