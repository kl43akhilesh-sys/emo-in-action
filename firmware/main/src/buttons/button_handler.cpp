#include "button_handler.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

ButtonHandler g_button_handler;

ButtonHandler::ButtonHandler()
    : mode_pressed(false), plus_pressed(false), minus_pressed(false), touch_active(false),
      mode_press_time(0), plus_press_time(0), minus_press_time(0), touch_start_time(0),
      mode_debounce(0), plus_debounce(0), minus_debounce(0), touch_debounce(0) {}

ButtonHandler::~ButtonHandler() {}

void ButtonHandler::initialize() {
    // Configure GPIO pins as inputs with internal pull-ups
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_BTN_MODE) | (1ULL << GPIO_BTN_PLUS) |
                       (1ULL << GPIO_BTN_MINUS) | (1ULL << GPIO_TOUCH_SIS),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void ButtonHandler::update() {
    read_gpio_states();
    process_debounce();
}

void ButtonHandler::on_mode_button(std::function<void()> callback) {
    mode_callback = callback;
}

void ButtonHandler::on_plus_button(std::function<void()> callback) {
    plus_callback = callback;
}

void ButtonHandler::on_minus_button(std::function<void()> callback) {
    minus_callback = callback;
}

void ButtonHandler::on_touch_sensor(std::function<void(uint32_t)> callback) {
    touch_callback = callback;
}

bool ButtonHandler::is_mode_pressed() {
    return mode_pressed;
}

bool ButtonHandler::is_plus_pressed() {
    return plus_pressed;
}

bool ButtonHandler::is_minus_pressed() {
    return minus_pressed;
}

bool ButtonHandler::is_touch_active() {
    return touch_active;
}

uint32_t ButtonHandler::get_touch_duration() {
    return xTaskGetTickCount() - touch_start_time;
}

void ButtonHandler::read_gpio_states() {
    // Read GPIO pins
    int mode_level = gpio_get_level((gpio_num_t)GPIO_BTN_MODE);
    int plus_level = gpio_get_level((gpio_num_t)GPIO_BTN_PLUS);
    int minus_level = gpio_get_level((gpio_num_t)GPIO_BTN_MINUS);
    int touch_level = gpio_get_level((gpio_num_t)GPIO_TOUCH_SIS);
    
    // Debounce and update states
    if (mode_level == 0) mode_debounce++; else mode_debounce = 0;
    if (plus_level == 0) plus_debounce++; else plus_debounce = 0;
    if (minus_level == 0) minus_debounce++; else minus_debounce = 0;
    if (touch_level == 1) touch_debounce++; else touch_debounce = 0;
}

void ButtonHandler::process_debounce() {
    uint32_t now = xTaskGetTickCount();
    
    // Mode button
    if (mode_debounce > (BTN_DEBOUNCE_MS / ANIMATION_FRAME_TIME)) {
        if (!mode_pressed) {
            mode_pressed = true;
            mode_press_time = now;
            if (mode_callback) mode_callback();
        }
    } else if (mode_pressed && mode_debounce == 0) {
        mode_pressed = false;
    }
    
    // Plus button
    if (plus_debounce > (BTN_DEBOUNCE_MS / ANIMATION_FRAME_TIME)) {
        if (!plus_pressed) {
            plus_pressed = true;
            plus_press_time = now;
            if (plus_callback) plus_callback();
        }
    } else if (plus_pressed && plus_debounce == 0) {
        plus_pressed = false;
    }
    
    // Minus button
    if (minus_debounce > (BTN_DEBOUNCE_MS / ANIMATION_FRAME_TIME)) {
        if (!minus_pressed) {
            minus_pressed = true;
            minus_press_time = now;
            if (minus_callback) minus_callback();
        }
    } else if (minus_pressed && minus_debounce == 0) {
        minus_pressed = false;
    }
    
    // Touch sensor
    if (touch_debounce > (TOUCH_DEBOUNCE_MS / ANIMATION_FRAME_TIME)) {
        if (!touch_active) {
            touch_active = true;
            touch_start_time = now;
        }
    } else if (touch_active && touch_debounce == 0) {
        touch_active = false;
        uint32_t duration = now - touch_start_time;
        if (touch_callback) touch_callback(duration);
    }
}
