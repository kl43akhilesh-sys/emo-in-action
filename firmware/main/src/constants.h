#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

// ============================================================================
// GPIO PIN DEFINITIONS
// ============================================================================

// Debug Serial
#define GPIO_TX0 1
#define GPIO_RX0 3

// Touch Sensor (TTP223)
#define GPIO_TOUCH_SIS 4

// Buttons
#define GPIO_BTN_MODE 5
#define GPIO_BTN_PLUS 32
#define GPIO_BTN_MINUS 33

// LCD Shield (4-bit mode)
#define GPIO_LCD_RS 25
#define GPIO_LCD_EN 26
#define GPIO_LCD_D4 27
#define GPIO_LCD_D5 14
#define GPIO_LCD_D6 12
#define GPIO_LCD_D7 13

// SD Card (SPI)
#define GPIO_SD_CS 15
#define GPIO_SD_CLK 18
#define GPIO_SD_MISO 19
#define GPIO_SD_MOSI 23

// I2C (OLED + Touch)
#define GPIO_I2C_SDA 21
#define GPIO_I2C_SCL 22

// Audio
#define GPIO_MIC_ADC 35  // ADC1_CH7

// ============================================================================
// DISPLAY CONFIGURATION
// ============================================================================

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_I2C_ADDR 0x3C
#define OLED_I2C_FREQ 400000  // 400 kHz

#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_I2C_FREQ 100000   // 100 kHz for parallel LCD shield

// ============================================================================
// ANIMATION SYSTEM
// ============================================================================

#define ANIMATION_FPS 30
#define ANIMATION_FRAME_TIME (1000 / ANIMATION_FPS)  // ~33ms

// Eye geometry (pixels)
#define EYE_WIDTH 32
#define EYE_HEIGHT 32
#define EYE_LEFT_X 30
#define EYE_RIGHT_X 95
#define EYE_Y 16

// Pupil
#define PUPIL_RADIUS 6
#define PUPIL_GLOW_RADIUS 8

// Mouth
#define MOUTH_X 64
#define MOUTH_Y 48
#define MOUTH_WIDTH 24
#define MOUTH_HEIGHT 12

// ============================================================================
// EMOTION STATES
// ============================================================================

enum EmotionState {
    EMO_NEUTRAL = 0,
    EMO_HAPPY,
    EMO_EXCITED,
    EMO_SAD,
    EMO_TIRED,
    EMO_SLEEP,
    EMO_SURPRISED,
    EMO_SCARED,
    EMO_NERVOUS,
    EMO_CONFUSED,
    EMO_WINK,
    EMO_LOVE,
    EMO_LAUGHING,
    EMO_ANGRY,
    EMO_FRUSTRATED,
    EMO_PROUD,
    EMO_GOODBYE,
    EMO_LISTENING,
    EMO_SPEAKING,
    EMO_PROCESSING,
    EMO_UPDATING,
    EMO_CHARGING,
    EMO_LOW_BATTERY,
    EMO_ERROR,
    EMO_CURIOUS,
    EMO_THINKING,
    EMO_FOCUSED,
    EMO_SERIOUS,
    EMO_BLUSH,
    EMO_ANALYTICAL,
    EMO_SHOCK,
    EMO_AFFECTION,
    EMO_WARY,
    EMO_MAX
};

// ============================================================================
// SYSTEM MODES
// ============================================================================

enum SystemMode {
    MODE_EMOTION_FACE = 0,
    MODE_WEATHER,
    MODE_SETTINGS,
    MODE_VOICE_CHAT,
    MODE_ALARM_CONFIG,
    MODE_MAX
};

// ============================================================================
// AUDIO CONFIGURATION
// ============================================================================

#define AUDIO_SAMPLE_RATE 16000
#define AUDIO_SAMPLE_BITS 16
#define AUDIO_CHANNELS 1
#define AUDIO_BUFFER_SIZE 4096

// ============================================================================
// TIMING CONSTANTS
// ============================================================================

#define BLINK_INTERVAL_MS 3000       // Blink every 3 seconds
#define BLINK_DURATION_MS 150        // Blink lasts 150ms
#define PUPIL_DRIFT_INTERVAL_MS 2000 // Pupil micro-drift every 2s
#define BREATHING_INTERVAL_MS 3000   // Mouth breathing every 3s
#define BOUNCE_ELASTICITY 1.2        // Elastic overshoot factor

// Touch sensor debounce
#define TOUCH_DEBOUNCE_MS 100
#define TOUCH_LONG_PRESS_1S_MS 1000
#define TOUCH_LONG_PRESS_2S_MS 2000
#define TOUCH_LONG_PRESS_3S_MS 3000

// Button debounce
#define BTN_DEBOUNCE_MS 50
#define BTN_HOLD_TIME_MS 1000

// ============================================================================
// COLOR DEFINITIONS (RGB)
// ============================================================================

#define COLOR_OLED_BLUE 0x00AAFF    // Electric blue for OLED
#define COLOR_OLED_GLOW 0x0099DD    // Glow tint
#define COLOR_RED_ALERT 0xFF3333    // Error/angry red
#define COLOR_PURPLE_GLITCH 0xAA00FF // Glitch overlay
#define COLOR_GREEN_GLOW 0x00FF77   // Charging glow
#define COLOR_YELLOW_WARN 0xFFDD00  // Warning yellow

// ============================================================================
// WEATHER CONFIGURATION
// ============================================================================

#define WEATHER_UPDATE_INTERVAL_MS 600000  // 10 minutes
#define WEATHER_GRAPH_POINTS 8              // 4-day forecast

// ============================================================================
// SD CARD PATHS
// ============================================================================

#define SD_MOUNT_POINT "/sd"
#define SD_ANIMATIONS_PATH "/sd/animations"
#define SD_CONFIG_PATH "/sd/config"
#define SD_CACHE_PATH "/sd/cache"
#define SD_LOGS_PATH "/sd/logs"

// ============================================================================
// ALARM SYSTEM
// ============================================================================

#define MAX_ALARMS 3
#define ALARM_SOUND_DURATION_MS 30000  // 30 seconds max

// ============================================================================
// NETWORK
// ============================================================================

#define WIFI_CONNECT_TIMEOUT_MS 30000
#define WEBSOCKET_PORT 8080
#define HTTP_SERVER_PORT 80

// ============================================================================
// API ENDPOINTS
// ============================================================================

#define OPENAI_WHISPER_ENDPOINT "https://api.openai.com/v1/audio/transcriptions"
#define GOOGLE_GEMINI_ENDPOINT "https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent"
#define ELEVENLABS_TTS_ENDPOINT "https://api.elevenlabs.io/v1/text-to-speech"
#define OPENWEATHER_ENDPOINT "https://api.openweathermap.org/data/2.5/forecast"

#endif // CONSTANTS_H
