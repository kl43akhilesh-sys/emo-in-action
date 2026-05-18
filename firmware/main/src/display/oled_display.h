#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <stdint.h>
#include <vector>
#include "constants.h"

class OLEDDisplay {
public:
    OLEDDisplay();
    ~OLEDDisplay();
    
    bool initialize();
    void deinitialize();
    bool is_initialized();
    
    // Framebuffer operations
    void clear_buffer();
    void fill_buffer();
    void display_buffer();
    
    // Drawing primitives
    void draw_pixel(int x, int y, bool on);
    void draw_line(int x0, int y0, int x1, int y1, bool on);
    void draw_rect(int x, int y, int w, int h, bool fill, bool on);
    void draw_circle(int x, int y, int r, bool fill, bool on);
    void draw_rounded_rect(int x, int y, int w, int h, int radius, bool on);
    
    // Text rendering
    void draw_text(int x, int y, const char* text, bool on);
    
    // Eye rendering (core animation)
    void draw_eye(int x, int y, int width, int height, 
                  int pupil_x, int pupil_y, int pupil_size, 
                  float glow_intensity);
    
    // Mouth rendering
    void draw_mouth(int x, int y, int width, int height, 
                    float mouth_shape, bool open, bool on);
    
    // Particle effects
    void draw_sparkles(int count, uint8_t pattern);
    void draw_tears(int x, int y, int count);
    void draw_hearts(int count);
    
    // Advanced effects
    void apply_glow(int x, int y, int radius, float intensity);
    void apply_glitch_overlay(uint8_t pattern);
    void apply_red_overlay(float intensity);
    
    // Brightness control
    void set_brightness(uint8_t level);  // 0-255
    uint8_t get_brightness();
    
    // Contrast control
    void set_contrast(uint8_t level);    // 0-255
    uint8_t get_contrast();
    
private:
    uint8_t framebuffer[128 * 64 / 8];  // 1024 bytes
    bool initialized;
    uint8_t brightness;
    uint8_t contrast;
    
    void write_buffer_to_display();
};

extern OLEDDisplay g_oled_display;

#endif // OLED_DISPLAY_H
