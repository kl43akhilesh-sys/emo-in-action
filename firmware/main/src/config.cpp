#include "config.h"
#include <fstream>
#include <cstring>

DeviceConfig g_device_config;

void config_load_defaults() {
    // Device
    g_device_config.device_name = "EMO";
    g_device_config.device_id = "emo-001";
    
    // WiFi
    g_device_config.wifi_ssid = "";
    g_device_config.wifi_password = "";
    g_device_config.wifi_enabled = true;
    
    // Bluetooth
    g_device_config.bt_device_name = "EMO-Speaker";
    g_device_config.bt_enabled = true;
    
    // API Keys (LOAD FROM ENVIRONMENT!)
    g_device_config.openai_api_key = "";
    g_device_config.gemini_api_key = "";
    g_device_config.elevenlabs_api_key = "";
    g_device_config.openweather_api_key = "";
    
    // Location
    g_device_config.city_name = "New York";
    g_device_config.latitude = 40.7128f;
    g_device_config.longitude = -74.0060f;
    
    // Voice
    g_device_config.voice_gender = "neutral";
    g_device_config.voice_speed = 100;
    g_device_config.voice_pitch = 100;
    g_device_config.voice_chat_enabled = true;
    
    // Display
    g_device_config.oled_brightness = 200;
    g_device_config.lcd_contrast = 200;
    g_device_config.auto_brightness = true;
    
    // Animation
    g_device_config.animation_speed = 100;
    g_device_config.micro_expressions = true;
    g_device_config.glow_effects = true;
    
    // System
    g_device_config.system_volume = 80;
    g_device_config.debug_mode = true;
    g_device_config.timezone_offset = 0;
    g_device_config.use_24h_time = false;
    
    // Features
    g_device_config.enable_weather = true;
    g_device_config.enable_emotion_tracking = true;
    g_device_config.enable_analytics = false;
    
    // Alarms
    for (int i = 0; i < 3; i++) {
        g_device_config.alarms[i].enabled = false;
        g_device_config.alarms[i].hour = 7;
        g_device_config.alarms[i].minute = 0;
        g_device_config.alarms[i].label = "Alarm ";
        g_device_config.alarms[i].label += (char)('1' + i);
        g_device_config.alarms[i].repeat_daily = false;
        g_device_config.alarms[i].snooze_interval = 5;
        for (int j = 0; j < 7; j++) {
            g_device_config.alarms[i].repeat_days.push_back(false);
        }
    }
}

void config_init() {
    config_load_defaults();
    config_load_from_sd();
}

void config_load_from_sd() {
    // TODO: Implement SD card config loading
    // Read config.json from /sd/config/
}

void config_save_to_sd() {
    // TODO: Implement SD card config saving
    // Write config.json to /sd/config/
}
