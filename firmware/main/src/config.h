#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include "constants.h"

// ============================================================================
// DEVICE CONFIGURATION STRUCTURE
// ============================================================================

struct DeviceConfig {
    // Device Identity
    std::string device_name;
    std::string device_id;
    
    // WiFi
    std::string wifi_ssid;
    std::string wifi_password;
    bool wifi_enabled;
    
    // Bluetooth
    std::string bt_device_name;
    bool bt_enabled;
    
    // API Keys
    std::string openai_api_key;
    std::string gemini_api_key;
    std::string elevenlabs_api_key;
    std::string openweather_api_key;
    
    // Location
    std::string city_name;
    float latitude;
    float longitude;
    
    // Voice Settings
    std::string voice_gender;  // "male", "female", "neutral"
    int voice_speed;           // 50-200 (%))
    int voice_pitch;           // 50-200 (%)
    bool voice_chat_enabled;
    
    // Display Settings
    int oled_brightness;       // 0-255
    int lcd_contrast;          // 0-255
    bool auto_brightness;
    
    // Animation Settings
    int animation_speed;       // 50-200 (%)
    bool micro_expressions;    // Enable subtle movements
    bool glow_effects;         // Enable OLED glow
    
    // Alarm Settings
    struct AlarmConfig {
        bool enabled;
        int hour;
        int minute;
        std::string label;
        bool repeat_daily;
        std::vector<bool> repeat_days;  // Mon-Sun
        int snooze_interval;  // minutes
    } alarms[3];
    
    // System
    int system_volume;         // 0-100
    bool debug_mode;
    int timezone_offset;       // hours from UTC
    bool use_24h_time;
    
    // Features
    bool enable_weather;
    bool enable_emotion_tracking;
    bool enable_analytics;
};

// ============================================================================
// EMOTION ANIMATION CONFIG
// ============================================================================

struct EmotionAnimConfig {
    EmotionState emotion;
    float eye_scale;            // 0.5 - 1.5
    float eye_brightness;       // 0.5 - 1.5
    int eye_width;              // pixels
    int eye_height;             // pixels
    float pupil_size;           // 0.5 - 1.5
    float mouth_width;          // 0.5 - 2.0
    float mouth_height;         // 0.5 - 2.0
    int mouth_y_offset;         // pixels from center
    bool mouth_open;            // true/false
    float glow_intensity;       // 0.0 - 1.0
    float animation_speed;      // 0.5 - 2.0
    int blink_rate;             // per minute
    bool has_tears;             // animate tears
    bool has_sparkles;          // animate sparkles
    bool has_particle_effect;   // general particles
    uint32_t overlay_color;     // for anger/error overlay
    float overlay_intensity;    // 0.0 - 1.0
    bool use_red_glitch;        // for errors
};

// ============================================================================
// GLOBAL CONFIG INSTANCE
// ============================================================================

extern DeviceConfig g_device_config;

void config_init();
void config_load_from_sd();
void config_save_to_sd();
void config_load_defaults();

#endif // CONFIG_H
