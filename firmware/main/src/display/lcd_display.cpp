#include "lcd_display.h"
#include "driver/gpio.h"
#include "esp_rom_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "constants.h"
#include <cstdio>
#include <cstring>
#include <ctime>

LCDDisplay g_lcd_display;

// HD44780 LCD commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// Flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// Flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// Flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// Flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

LCDDisplay::LCDDisplay() : initialized(false), display_control(0), display_function(0) {}

LCDDisplay::~LCDDisplay() {
    deinitialize();
}

bool LCDDisplay::initialize() {
    // Configure GPIO pins as outputs
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_LCD_RS) | (1ULL << GPIO_LCD_EN) |
                       (1ULL << GPIO_LCD_D4) | (1ULL << GPIO_LCD_D5) |
                       (1ULL << GPIO_LCD_D6) | (1ULL << GPIO_LCD_D7),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
    
    // Initialize LCD in 4-bit mode
    vTaskDelay(50 / portTICK_PERIOD_MS);  // Wait for LCD power up
    
    display_function = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
    
    // 4-bit initialization sequence
    write_nibble(0x03);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    write_nibble(0x03);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    write_nibble(0x03);
    vTaskDelay(1 / portTICK_PERIOD_MS);
    write_nibble(0x02);  // Select 4-bit mode
    
    send_command(LCD_FUNCTIONSET | display_function);
    
    display_control = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    send_command(LCD_DISPLAYCONTROL | display_control);
    
    clear();
    
    send_command(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
    
    initialized = true;
    return true;
}

void LCDDisplay::deinitialize() {
    if (initialized) {
        display_off();
        initialized = false;
    }
}

bool LCDDisplay::is_initialized() {
    return initialized;
}

void LCDDisplay::clear() {
    send_command(LCD_CLEARDISPLAY);
    vTaskDelay(2 / portTICK_PERIOD_MS);
}

void LCDDisplay::home() {
    send_command(LCD_RETURNHOME);
    vTaskDelay(2 / portTICK_PERIOD_MS);
}

void LCDDisplay::print(const char* text) {
    while (*text) {
        write_char(*text++);
    }
}

void LCDDisplay::print_line(int line, const char* text) {
    if (line > 1) return;
    set_cursor(0, line);
    print(text);
}

void LCDDisplay::set_cursor(int col, int row) {
    int offsets[] = {0x00, 0x40};
    send_command(LCD_SETDDRAMADDR | (col + offsets[row]));
}

void LCDDisplay::write_char(char c) {
    send_data((uint8_t)c);
}

void LCDDisplay::write_byte(uint8_t byte) {
    send_data(byte);
}

void LCDDisplay::display_on() {
    display_control |= LCD_DISPLAYON;
    send_command(LCD_DISPLAYCONTROL | display_control);
}

void LCDDisplay::display_off() {
    display_control &= ~LCD_DISPLAYON;
    send_command(LCD_DISPLAYCONTROL | display_control);
}

void LCDDisplay::cursor_on() {
    display_control |= LCD_CURSORON;
    send_command(LCD_DISPLAYCONTROL | display_control);
}

void LCDDisplay::cursor_off() {
    display_control &= ~LCD_CURSORON;
    send_command(LCD_DISPLAYCONTROL | display_control);
}

void LCDDisplay::blink_on() {
    display_control |= LCD_BLINKON;
    send_command(LCD_DISPLAYCONTROL | display_control);
}

void LCDDisplay::blink_off() {
    display_control &= ~LCD_BLINKON;
    send_command(LCD_DISPLAYCONTROL | display_control);
}

void LCDDisplay::display_time(int hour, int minute, int second, bool is_24h) {
    char time_str[16];
    if (is_24h) {
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", hour, minute, second);
    } else {
        int hour_12 = (hour % 12 == 0) ? 12 : hour % 12;
        const char* ampm = (hour >= 12) ? "PM" : "AM";
        snprintf(time_str, sizeof(time_str), "%02d:%02d %s", hour_12, minute, ampm);
    }
    print_line(0, time_str);
}

void LCDDisplay::display_date(int month, int day, int year) {
    char date_str[16];
    snprintf(date_str, sizeof(date_str), "%02d/%02d/%04d", month, day, year);
    print_line(1, date_str);
}

void LCDDisplay::display_status(bool wifi_connected, bool bt_connected, bool ntp_synced) {
    set_cursor(0, 1);
    print("[");
    print(wifi_connected ? "W" : "w");
    print("] [");
    print(bt_connected ? "B" : "b");
    print("] [");
    print(ntp_synced ? "N" : "n");
    print("]");
}

void LCDDisplay::set_contrast(uint8_t level) {
    // Contrast control via potentiometer on LCD module
    // This would require PWM or DAC output
}

void LCDDisplay::set_backlight(uint8_t level) {
    // Backlight control via PWM
    // TODO: Implement PWM control
}

void LCDDisplay::send_command(uint8_t cmd) {
    gpio_set_level((gpio_num_t)GPIO_LCD_RS, 0);  // RS = 0 for command
    send_data(cmd);
}

void LCDDisplay::send_data(uint8_t data) {
    gpio_set_level((gpio_num_t)GPIO_LCD_RS, 1);  // RS = 1 for data
    
    write_nibble((data >> 4) & 0x0F);  // High nibble
    write_nibble(data & 0x0F);          // Low nibble
}

void LCDDisplay::write_nibble(uint8_t nibble) {
    gpio_set_level((gpio_num_t)GPIO_LCD_D4, (nibble >> 0) & 1);
    gpio_set_level((gpio_num_t)GPIO_LCD_D5, (nibble >> 1) & 1);
    gpio_set_level((gpio_num_t)GPIO_LCD_D6, (nibble >> 2) & 1);
    gpio_set_level((gpio_num_t)GPIO_LCD_D7, (nibble >> 3) & 1);
    
    pulse_enable();
}

void LCDDisplay::pulse_enable() {
    delay_us(1);
    gpio_set_level((gpio_num_t)GPIO_LCD_EN, 1);
    delay_us(1);
    gpio_set_level((gpio_num_t)GPIO_LCD_EN, 0);
    delay_us(100);
}

void LCDDisplay::delay_us(uint32_t us) {
    ets_delay_us(us);
}
