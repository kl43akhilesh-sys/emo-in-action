#ifndef ANIMATION_H
#define ANIMATION_H

#include "constants.h"
#include <stdint.h>
#include <vector>
#include <cmath>

// Easing function types
class Easing {
public:
    static float linear(float t);
    static float easeInQuad(float t);
    static float easeOutQuad(float t);
    static float easeInOutQuad(float t);
    static float easeOutCubic(float t);
    static float easeInOutCubic(float t);
    static float easeOutBounce(float t);
    static float easeOutElastic(float t);
};

// Animation frame structure
struct AnimationFrame {
    EmotionState emotion;
    uint32_t frame_id;
    uint32_t duration_ms;
    
    // Eye parameters
    int eye_x;
    int eye_y;
    int eye_width;
    int eye_height;
    int pupil_offset_x;
    int pupil_offset_y;
    int pupil_size;
    float pupil_glow;
    
    // Mouth parameters
    float mouth_shape;  // -1.0 (sad) to +1.0 (happy)
    float mouth_height;
    bool mouth_open;
    
    // Effects
    float glow_intensity;
    float overlay_intensity;
    uint32_t overlay_color;
    
    // Particles
    std::vector<int> particle_x;
    std::vector<int> particle_y;
};

// Animation sequence
class AnimationSequence {
public:
    AnimationSequence(EmotionState emotion);
    ~AnimationSequence();
    
    void add_frame(const AnimationFrame& frame);
    AnimationFrame* get_frame(uint32_t index);
    uint32_t get_frame_count() const;
    uint32_t get_total_duration() const;
    
    void play();
    void stop();
    void pause();
    bool is_playing() const;
    
    AnimationFrame* get_current_frame();
    AnimationFrame* get_next_frame();
    void advance_frame();
    
private:
    EmotionState emotion;
    std::vector<AnimationFrame> frames;
    uint32_t current_frame;
    uint32_t elapsed_time;
    bool playing;
};

// Main animation controller
class AnimationEngine {
public:
    AnimationEngine();
    ~AnimationEngine();
    
    void initialize();
    void update(uint32_t delta_time);
    
    void play_emotion(EmotionState emotion);
    void stop_animation();
    void pause_animation();
    void resume_animation();
    
    AnimationFrame* get_current_frame();
    EmotionState get_current_emotion() const;
    
    // Preset animations
    void load_happy_animation();
    void load_sad_animation();
    void load_angry_animation();
    void load_excited_animation();
    void load_thinking_animation();
    void load_listening_animation();
    void load_speaking_animation();
    void load_error_animation();
    void load_sleep_animation();
    void load_loading_animation();
    
private:
    AnimationSequence* current_sequence;
    EmotionState current_emotion;
    uint32_t last_update_time;
};

extern AnimationEngine g_animation_engine;

#endif // ANIMATION_H
