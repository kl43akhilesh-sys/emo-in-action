#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "constants.h"
#include <stdint.h>
#include <functional>

class ButtonHandler {
public:
    ButtonHandler();
    ~ButtonHandler();
    
    void initialize();
    void update();
    
    // Callback registration
    void on_mode_button(std::function<void()> callback);
    void on_plus_button(std::function<void()> callback);
    void on_minus_button(std::function<void()> callback);
    void on_touch_sensor(std::function<void(uint32_t duration)> callback);
    
    // Button states
    bool is_mode_pressed();
    bool is_plus_pressed();
    bool is_minus_pressed();
    bool is_touch_active();
    uint32_t get_touch_duration();
    
private:
    // Button state tracking
    bool mode_pressed;
    bool plus_pressed;
    bool minus_pressed;
    bool touch_active;
    
    uint32_t mode_press_time;
    uint32_t plus_press_time;
    uint32_t minus_press_time;
    uint32_t touch_start_time;
    
    // Debounce counters
    int mode_debounce;
    int plus_debounce;
    int minus_debounce;
    int touch_debounce;
    
    // Callbacks
    std::function<void()> mode_callback;
    std::function<void()> plus_callback;
    std::function<void()> minus_callback;
    std::function<void(uint32_t)> touch_callback;
    
    void read_gpio_states();
    void process_debounce();
};

extern ButtonHandler g_button_handler;

#endif // BUTTON_HANDLER_H
