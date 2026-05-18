#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <stdint.h>
#include <string>
#include "constants.h"

class LCDDisplay {
public:
    LCDDisplay();
    ~LCDDisplay();
    
    bool initialize();
    void deinitialize();
    bool is_initialized();
    
    // Text operations
    void clear();
    void home();
    void print(const char* text);
    void print_line(int line, const char* text);
    void set_cursor(int col, int row);
    
    // Character operations
    void write_char(char c);
    void write_byte(uint8_t byte);
    
    // Display control
    void display_on();
    void display_off();
    void cursor_on();
    void cursor_off();
    void blink_on();
    void blink_off();
    
    // Time display
    void display_time(int hour, int minute, int second, bool is_24h);
    void display_date(int month, int day, int year);
    void display_status(bool wifi_connected, bool bt_connected, bool ntp_synced);
    
    // Brightness/Contrast
    void set_contrast(uint8_t level);   // 0-255
    void set_backlight(uint8_t level);  // 0-255
    
private:
    bool initialized;
    uint8_t display_control;
    uint8_t display_function;
    
    // Low-level I/O
    void send_command(uint8_t cmd);
    void send_data(uint8_t data);
    void write_nibble(uint8_t nibble);
    void pulse_enable();
    void delay_us(uint32_t us);
};

extern LCDDisplay g_lcd_display;

#endif // LCD_DISPLAY_H
