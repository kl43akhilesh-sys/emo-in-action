#ifndef COMPANION_H
#define COMPANION_H

#include "constants.h"
#include "animation.h"
#include <stdint.h>
#include <string>

// Companion main state machine
class CompanionBrain {
public:
    CompanionBrain();
    ~CompanionBrain();
    
    void initialize();
    void update(uint32_t delta_time);
    
    // Emotion control
    void set_emotion(EmotionState emotion);
    EmotionState get_emotion() const;
    
    // Mode control
    void set_mode(SystemMode mode);
    SystemMode get_mode() const;
    
    // Voice interaction
    void on_voice_detected();
    void on_listening_complete(const std::string& text);
    void on_ai_response(const std::string& response, EmotionState implied_emotion);
    void on_tts_complete();
    
    // Touch interactions
    void on_touch_tap();
    void on_touch_double_tap();
    void on_touch_long_press_1s();
    void on_touch_long_press_2s();
    void on_touch_long_press_3s();
    
    // Button interactions
    void on_mode_button_press();
    void on_plus_button_press();
    void on_minus_button_press();
    
    // Environmental awareness
    void on_weather_update(float temp, const std::string& condition);
    void on_time_update(int hour, int minute);
    void on_alarm_trigger(int alarm_id);
    
    // System events
    void on_wifi_connected();
    void on_wifi_disconnected();
    void on_bluetooth_connected();
    void on_bluetooth_disconnected();
    void on_low_battery();
    void on_error(const std::string& error_msg);
    
    // Rendering
    void render_to_display();
    
private:
    EmotionState current_emotion;
    SystemMode current_mode;
    uint32_t last_blink_time;
    uint32_t last_update_time;
    float current_temperature;
    std::string current_weather;
    
    void transition_to_emotion(EmotionState new_emotion);
    void transition_to_mode(SystemMode new_mode);
};

extern CompanionBrain g_companion_brain;

#endif // COMPANION_H
