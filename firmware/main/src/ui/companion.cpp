#include "companion.h"
#include "display/oled_display.h"
#include "display/lcd_display.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

CompanionBrain g_companion_brain;

CompanionBrain::CompanionBrain() 
    : current_emotion(EMO_NEUTRAL), current_mode(MODE_EMOTION_FACE),
      last_blink_time(0), last_update_time(0), current_temperature(25.0f), 
      current_weather("Sunny") {}

CompanionBrain::~CompanionBrain() {}

void CompanionBrain::initialize() {
    g_animation_engine.initialize();
    set_emotion(EMO_NEUTRAL);
    set_mode(MODE_EMOTION_FACE);
}

void CompanionBrain::update(uint32_t delta_time) {
    g_animation_engine.update(delta_time);
    render_to_display();
}

void CompanionBrain::set_emotion(EmotionState emotion) {
    if (emotion != current_emotion) {
        transition_to_emotion(emotion);
    }
}

EmotionState CompanionBrain::get_emotion() const {
    return current_emotion;
}

void CompanionBrain::set_mode(SystemMode mode) {
    if (mode != current_mode) {
        transition_to_mode(mode);
    }
}

SystemMode CompanionBrain::get_mode() const {
    return current_mode;
}

void CompanionBrain::on_voice_detected() {
    set_emotion(EMO_LISTENING);
}

void CompanionBrain::on_listening_complete(const std::string& text) {
    set_emotion(EMO_PROCESSING);
}

void CompanionBrain::on_ai_response(const std::string& response, EmotionState implied_emotion) {
    set_emotion(implied_emotion);
    set_emotion(EMO_SPEAKING);
}

void CompanionBrain::on_tts_complete() {
    set_emotion(EMO_HAPPY);
}

void CompanionBrain::on_touch_tap() {
    set_emotion(EMO_HAPPY);
}

void CompanionBrain::on_touch_double_tap() {
    set_emotion(EMO_ANGRY);
}

void CompanionBrain::on_touch_long_press_1s() {
    set_mode(MODE_WEATHER);
}

void CompanionBrain::on_touch_long_press_2s() {
    set_mode(MODE_SETTINGS);
}

void CompanionBrain::on_touch_long_press_3s() {
    set_emotion(EMO_PROCESSING);
    // Trigger reboot
}

void CompanionBrain::on_mode_button_press() {
    // Cycle through modes
    int next_mode = (current_mode + 1) % MODE_MAX;
    set_mode((SystemMode)next_mode);
}

void CompanionBrain::on_plus_button_press() {
    // Increase something (volume, alarm hour, etc.)
}

void CompanionBrain::on_minus_button_press() {
    // Decrease something
}

void CompanionBrain::on_weather_update(float temp, const std::string& condition) {
    current_temperature = temp;
    current_weather = condition;
}

void CompanionBrain::on_time_update(int hour, int minute) {
    // Update LCD display
}

void CompanionBrain::on_alarm_trigger(int alarm_id) {
    set_emotion(EMO_EXCITED);
}

void CompanionBrain::on_wifi_connected() {
    set_emotion(EMO_HAPPY);
}

void CompanionBrain::on_wifi_disconnected() {
    set_emotion(EMO_NERVOUS);
}

void CompanionBrain::on_bluetooth_connected() {
    set_emotion(EMO_EXCITED);
}

void CompanionBrain::on_bluetooth_disconnected() {
    set_emotion(EMO_CONFUSED);
}

void CompanionBrain::on_low_battery() {
    set_emotion(EMO_LOW_BATTERY);
}

void CompanionBrain::on_error(const std::string& error_msg) {
    set_emotion(EMO_ERROR);
}

void CompanionBrain::render_to_display() {
    // Get current animation frame
    AnimationFrame* frame = g_animation_engine.get_current_frame();
    if (!frame) return;
    
    // Clear OLED buffer
    g_oled_display.clear_buffer();
    
    // Draw left eye
    g_oled_display.draw_eye(EYE_LEFT_X, EYE_Y, EYE_WIDTH, EYE_HEIGHT,
                            frame->pupil_offset_x, frame->pupil_offset_y,
                            frame->pupil_size, frame->pupil_glow);
    
    // Draw right eye
    g_oled_display.draw_eye(EYE_RIGHT_X, EYE_Y, EYE_WIDTH, EYE_HEIGHT,
                            frame->pupil_offset_x, frame->pupil_offset_y,
                            frame->pupil_size, frame->pupil_glow);
    
    // Draw mouth
    g_oled_display.draw_mouth(MOUTH_X, MOUTH_Y, MOUTH_WIDTH, MOUTH_HEIGHT,
                              frame->mouth_shape, frame->mouth_open, true);
    
    // Draw particles if any
    if (!frame->particle_x.empty()) {
        for (size_t i = 0; i < frame->particle_x.size(); i++) {
            g_oled_display.draw_pixel(frame->particle_x[i], frame->particle_y[i], true);
        }
    }
    
    // Apply effects
    if (frame->glow_intensity > 0) {
        g_oled_display.apply_glow(EYE_LEFT_X + EYE_WIDTH/2, EYE_Y + EYE_HEIGHT/2, 
                                  10, frame->glow_intensity);
        g_oled_display.apply_glow(EYE_RIGHT_X + EYE_WIDTH/2, EYE_Y + EYE_HEIGHT/2,
                                  10, frame->glow_intensity);
    }
    
    // Display the buffer
    g_oled_display.display_buffer();
}

void CompanionBrain::transition_to_emotion(EmotionState new_emotion) {
    current_emotion = new_emotion;
    g_animation_engine.play_emotion(new_emotion);
}

void CompanionBrain::transition_to_mode(SystemMode new_mode) {
    current_mode = new_mode;
    
    switch (new_mode) {
        case MODE_EMOTION_FACE:
            set_emotion(EMO_NEUTRAL);
            break;
        case MODE_WEATHER:
            set_emotion(EMO_HAPPY);
            // Display weather on OLED
            break;
        case MODE_SETTINGS:
            set_emotion(EMO_FOCUSED);
            // Display settings menu on LCD
            break;
        case MODE_VOICE_CHAT:
            set_emotion(EMO_LISTENING);
            break;
        case MODE_ALARM_CONFIG:
            set_emotion(EMO_FOCUSED);
            break;
        default:
            break;
    }
}
