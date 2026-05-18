#include "oled_display.h"
#include "esp_i2c.h"
#include "driver/i2c.h"
#include "constants.h"
#include <cstring>
#include <cmath>

OLEDDisplay g_oled_display;

// SSD1306 I2C commands
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR 0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA1
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_CHARGEPUMP 0x8D

OLEDDisplay::OLEDDisplay() : initialized(false), brightness(200), contrast(200) {
    std::memset(framebuffer, 0, sizeof(framebuffer));
}

OLEDDisplay::~OLEDDisplay() {
    deinitialize();
}

bool OLEDDisplay::initialize() {
    // Initialize I2C
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_I2C_SDA,
        .scl_io_num = GPIO_I2C_SCL,
        .master = {.clk_speed = OLED_I2C_FREQ},
    };
    
    // i2c_param_config(I2C_NUM_0, &conf);
    // i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    
    // Initialize SSD1306
    // Send initialization sequence
    // ...
    
    initialized = true;
    clear_buffer();
    display_buffer();
    
    return true;
}

void OLEDDisplay::deinitialize() {
    if (initialized) {
        // i2c_driver_delete(I2C_NUM_0);
        initialized = false;
    }
}

bool OLEDDisplay::is_initialized() {
    return initialized;
}

void OLEDDisplay::clear_buffer() {
    std::memset(framebuffer, 0, sizeof(framebuffer));
}

void OLEDDisplay::fill_buffer() {
    std::memset(framebuffer, 0xFF, sizeof(framebuffer));
}

void OLEDDisplay::display_buffer() {
    if (!initialized) return;
    write_buffer_to_display();
}

void OLEDDisplay::draw_pixel(int x, int y, bool on) {
    if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT) return;
    
    int byte_index = (y / 8) * OLED_WIDTH + x;
    int bit_index = y % 8;
    
    if (on) {
        framebuffer[byte_index] |= (1 << bit_index);
    } else {
        framebuffer[byte_index] &= ~(1 << bit_index);
    }
}

void OLEDDisplay::draw_line(int x0, int y0, int x1, int y1, bool on) {
    // Bresenham line algorithm
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    int x = x0, y = y0;
    while (true) {
        draw_pixel(x, y, on);
        if (x == x1 && y == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void OLEDDisplay::draw_rect(int x, int y, int w, int h, bool fill, bool on) {
    if (fill) {
        for (int yy = y; yy < y + h; yy++) {
            for (int xx = x; xx < x + w; xx++) {
                draw_pixel(xx, yy, on);
            }
        }
    } else {
        draw_line(x, y, x + w - 1, y, on);
        draw_line(x + w - 1, y, x + w - 1, y + h - 1, on);
        draw_line(x + w - 1, y + h - 1, x, y + h - 1, on);
        draw_line(x, y + h - 1, x, y, on);
    }
}

void OLEDDisplay::draw_circle(int x, int y, int r, bool fill, bool on) {
    // Midpoint circle algorithm
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int cx = 0;
    int cy = r;
    
    draw_pixel(x, y + r, on);
    draw_pixel(x, y - r, on);
    draw_pixel(x + r, y, on);
    draw_pixel(x - r, y, on);
    
    while (cx < cy) {
        if (f >= 0) {
            cy--;
            ddF_y += 2;
            f += ddF_y;
        }
        cx++;
        ddF_x += 2;
        f += ddF_x;
        
        if (fill) {
            draw_line(x - cx, y + cy, x + cx, y + cy, on);
            draw_line(x - cy, y + cx, x + cy, y + cx, on);
            draw_line(x - cx, y - cy, x + cx, y - cy, on);
            draw_line(x - cy, y - cx, x + cy, y - cx, on);
        } else {
            draw_pixel(x + cx, y + cy, on);
            draw_pixel(x - cx, y + cy, on);
            draw_pixel(x + cx, y - cy, on);
            draw_pixel(x - cx, y - cy, on);
            draw_pixel(x + cy, y + cx, on);
            draw_pixel(x - cy, y + cx, on);
            draw_pixel(x + cy, y - cx, on);
            draw_pixel(x - cy, y - cx, on);
        }
    }
}

void OLEDDisplay::draw_rounded_rect(int x, int y, int w, int h, int radius, bool on) {
    // Draw rounded rectangle (simplified)
    draw_rect(x + radius, y, w - 2 * radius, h, true, on);
    draw_rect(x, y + radius, w, h - 2 * radius, true, on);
    draw_circle(x + radius, y + radius, radius, true, on);
    draw_circle(x + w - radius - 1, y + radius, radius, true, on);
    draw_circle(x + radius, y + h - radius - 1, radius, true, on);
    draw_circle(x + w - radius - 1, y + h - radius - 1, radius, true, on);
}

void OLEDDisplay::draw_text(int x, int y, const char* text, bool on) {
    // TODO: Implement font rendering
}

void OLEDDisplay::draw_eye(int x, int y, int width, int height, 
                            int pupil_x, int pupil_y, int pupil_size, 
                            float glow_intensity) {
    // Draw eye white (curved rectangle)
    draw_rounded_rect(x, y, width, height, width / 8, true);
    
    // Draw pupil
    draw_circle(x + pupil_x, y + pupil_y, pupil_size, true, true);
    
    // Draw glow effect (outer rim)
    if (glow_intensity > 0) {
        for (int i = 0; i < 2; i++) {
            draw_rounded_rect(x - i, y - i, width + 2 * i, height + 2 * i, width / 8, false);
        }
    }
}

void OLEDDisplay::draw_mouth(int x, int y, int width, int height, 
                             float mouth_shape, bool open, bool on) {
    // mouth_shape: -1.0 (sad) to +1.0 (happy)
    // Draw mouth as a curve
    int center_y = y + (open ? height : height / 2);
    int offset = (int)(height * mouth_shape / 2);
    
    for (int i = 0; i < width; i++) {
        int px = x - width / 2 + i;
        float t = (float)i / width;
        float curve = 4.0f * t * (1.0f - t);  // Parabolic curve
        int py = center_y + (int)(offset * curve);
        draw_pixel(px, py, on);
    }
}

void OLEDDisplay::draw_sparkles(int count, uint8_t pattern) {
    // Draw random sparkle particles
    for (int i = 0; i < count; i++) {
        int x = (pattern + i * 17) % OLED_WIDTH;
        int y = (pattern * 13 + i * 23) % OLED_HEIGHT;
        draw_pixel(x, y, true);
    }
}

void OLEDDisplay::draw_tears(int x, int y, int count) {
    // Draw tear drops
    for (int i = 0; i < count; i++) {
        int tear_y = y + i * 4;
        draw_line(x, tear_y, x, tear_y + 3, true);
    }
}

void OLEDDisplay::draw_hearts(int count) {
    // Draw floating hearts
    // TODO: Implement heart shape drawing
}

void OLEDDisplay::apply_glow(int x, int y, int radius, float intensity) {
    // Draw glow halo around point
    int steps = (int)(radius * intensity);
    for (int i = 1; i < steps; i++) {
        draw_circle(x, y, i, false, true);
    }
}

void OLEDDisplay::apply_glitch_overlay(uint8_t pattern) {
    // Apply glitch effect by XORing pattern
    for (int i = 0; i < sizeof(framebuffer); i++) {
        if (pattern & (1 << (i % 8))) {
            framebuffer[i] ^= 0xFF;
        }
    }
}

void OLEDDisplay::apply_red_overlay(float intensity) {
    // For OLED, simulate red by flickering/dimming
    uint8_t dim_factor = (uint8_t)(255 * (1.0f - intensity));
    for (int i = 0; i < sizeof(framebuffer); i++) {
        framebuffer[i] = (framebuffer[i] * dim_factor) / 255;
    }
}

void OLEDDisplay::set_brightness(uint8_t level) {
    brightness = level;
    // Send to SSD1306 via I2C command
    // TODO: Send SSD1306_SETCONTRAST + level
}

uint8_t OLEDDisplay::get_brightness() {
    return brightness;
}

void OLEDDisplay::set_contrast(uint8_t level) {
    contrast = level;
}

uint8_t OLEDDisplay::get_contrast() {
    return contrast;
}

void OLEDDisplay::write_buffer_to_display() {
    // Write framebuffer to SSD1306 via I2C
    // TODO: Send data in 8-byte chunks
}
