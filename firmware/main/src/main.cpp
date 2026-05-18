#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_wifi.h"

#include "utils/constants.h"
#include "utils/config.h"
#include "utils/wifi_manager.h"
#include "utils/sd_manager.h"
#include "display/oled_display.h"
#include "display/lcd_display.h"
#include "ui/animation.h"
#include "ui/companion.h"
#include "buttons/button_handler.h"
#include "cloud/whisper_api.h"
#include "cloud/gemini_api.h"
#include "cloud/elevenlabs_api.h"
#include "alarm/alarm_system.h"
#include "bluetooth/bt_manager.h"
#include "bluetooth/bt_speaker.h"
#include "bluetooth/bt_voice_chat.h"

static const char* TAG = "EMO-ON-ACTION";

// Main task
void main_loop_task(void* param) {
    const int FRAME_TIME_MS = 33;  // 30 FPS
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    ESP_LOGI(TAG, "Main loop started");
    
    while (true) {
        // Update all systems
        g_button_handler.update();
        g_companion_brain.update(FRAME_TIME_MS);
        g_alarm_system.update();
        
        // Maintain frame rate
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(FRAME_TIME_MS));
    }
}

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "EMO-ON-ACTION Starting...");
    
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    // Initialize configuration
    config_init();
    ESP_LOGI(TAG, "Configuration loaded");
    
    // Initialize displays
    g_oled_display.initialize();
    ESP_LOGI(TAG, "OLED display initialized");
    
    g_lcd_display.initialize();
    ESP_LOGI(TAG, "LCD display initialized");
    
    // Initialize SD card
    g_sd_manager.initialize();
    ESP_LOGI(TAG, "SD card initialized");
    
    // Initialize WiFi
    g_wifi_manager.connect(g_device_config.wifi_ssid, g_device_config.wifi_password);
    ESP_LOGI(TAG, "WiFi initialized");
    
    // Initialize Bluetooth
    g_bt_manager.initialize();
    g_bt_speaker.initialize();
    g_bt_voice_chat.initialize();
    ESP_LOGI(TAG, "Bluetooth initialized");
    
    // Initialize APIs
    g_whisper_api.initialize(g_device_config.openai_api_key);
    g_gemini_api.initialize(g_device_config.gemini_api_key);
    g_elevenlabs_api.initialize(g_device_config.elevenlabs_api_key);
    ESP_LOGI(TAG, "Cloud APIs initialized");
    
    // Initialize companion
    g_button_handler.initialize();
    g_companion_brain.initialize();
    g_alarm_system.initialize();
    ESP_LOGI(TAG, "Companion brain initialized");
    
    // Register button callbacks
    g_button_handler.on_mode_button([]() {
        ESP_LOGI(TAG, "MODE button pressed");
        g_companion_brain.on_mode_button_press();
    });
    
    g_button_handler.on_plus_button([]() {
        ESP_LOGI(TAG, "PLUS button pressed");
        g_companion_brain.on_plus_button_press();
    });
    
    g_button_handler.on_minus_button([]() {
        ESP_LOGI(TAG, "MINUS button pressed");
        g_companion_brain.on_minus_button_press();
    });
    
    g_button_handler.on_touch_sensor([](uint32_t duration) {
        ESP_LOGI(TAG, "Touch sensor activated for %lu ms", duration);
        if (duration < 200) {
            g_companion_brain.on_touch_tap();
        } else if (duration < 400) {
            g_companion_brain.on_touch_double_tap();
        } else if (duration < 1000) {
            g_companion_brain.on_touch_long_press_1s();
        } else if (duration < 2000) {
            g_companion_brain.on_touch_long_press_2s();
        } else if (duration >= 3000) {
            g_companion_brain.on_touch_long_press_3s();
        }
    });
    
    // Create main loop task
    xTaskCreatePinnedToCore(main_loop_task, "main_loop", 8192, nullptr, 5, nullptr, 1);
    
    ESP_LOGI(TAG, "EMO-ON-ACTION initialization complete!");
}
