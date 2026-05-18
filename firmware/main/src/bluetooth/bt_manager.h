#ifndef BT_MANAGER_H
#define BT_MANAGER_H

#include <string>
#include <stdint.h>

class BluetoothManager {
public:
    BluetoothManager();
    ~BluetoothManager();
    
    bool initialize();
    void deinitialize();
    bool is_initialized();
    
    bool start_scanning();
    void stop_scanning();
    bool is_scanning();
    
    bool connect_to_device(const std::string& mac_address);
    bool disconnect();
    bool is_connected();
    
    std::string get_connected_device_name();
    std::string get_connected_device_mac();
    
    // A2DP speaker
    bool is_a2dp_connected();
    
private:
    bool initialized;
    bool connected;
    bool a2dp_connected;
    std::string connected_device_mac;
    std::string connected_device_name;
};

extern BluetoothManager g_bt_manager;

#endif // BT_MANAGER_H
