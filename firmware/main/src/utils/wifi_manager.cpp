#include "wifi_manager.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_sntp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <cstring>
#include <ctime>

WiFiManager g_wifi_manager;

WiFiManager::WiFiManager() : connected(false), ntp_synced(false), connection_time(0) {}

WiFiManager::~WiFiManager() {
    disconnect();
}

bool WiFiManager::connect(const std::string& ssid, const std::string& password) {
    // Initialize WiFi
    esp_netif_create_default_wifi_sta();
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    // esp_wifi_init(&cfg);  // Uncomment when full IDF integration
    
    wifi_config_t wifi_config = {};
    std::strncpy((char*)wifi_config.sta.ssid, ssid.c_str(), sizeof(wifi_config.sta.ssid) - 1);
    std::strncpy((char*)wifi_config.sta.password, password.c_str(), sizeof(wifi_config.sta.password) - 1);
    
    // esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    // esp_wifi_start();
    
    connected = true;
    connection_time = xTaskGetTickCount() / portTICK_PERIOD_MS;
    
    // Start NTP after connection
    update_time_from_ntp();
    
    return true;
}

bool WiFiManager::is_connected() {
    return connected;
}

void WiFiManager::disconnect() {
    if (connected) {
        // esp_wifi_stop();
        // esp_wifi_deinit();
        connected = false;
    }
}

std::string WiFiManager::get_ip_address() {
    // TODO: Get actual IP from esp_netif
    return "192.168.1.100";
}

std::string WiFiManager::get_mac_address() {
    // TODO: Get MAC address from ESP32
    return "AA:BB:CC:DD:EE:FF";
}

int WiFiManager::get_signal_strength() {
    // Returns RSSI in dBm (typical -30 to -90)
    return -45;  // Placeholder
}

void WiFiManager::update_time_from_ntp() {
    // Initialize SNTP
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
    
    // Wait for time to be set
    time_t now = time(nullptr);
    int retry = 0;
    const int retry_count = 20;
    
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    
    ntp_synced = (sntp_get_sync_status() == SNTP_SYNC_STATUS_COMPLETED);
}

uint32_t WiFiManager::get_unix_time() {
    return (uint32_t)time(nullptr);
}

bool WiFiManager::is_ntp_synced() {
    return ntp_synced;
}
