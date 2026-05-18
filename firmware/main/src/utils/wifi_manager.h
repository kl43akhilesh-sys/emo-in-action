#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <string>
#include <stdint.h>

class WiFiManager {
public:
    WiFiManager();
    ~WiFiManager();
    
    bool connect(const std::string& ssid, const std::string& password);
    bool is_connected();
    void disconnect();
    
    std::string get_ip_address();
    std::string get_mac_address();
    int get_signal_strength();  // RSSI in dBm
    
    void update_time_from_ntp();
    uint32_t get_unix_time();
    
    bool is_ntp_synced();
    
private:
    bool connected;
    uint32_t connection_time;
    bool ntp_synced;
};

extern WiFiManager g_wifi_manager;

#endif // WIFI_MANAGER_H
