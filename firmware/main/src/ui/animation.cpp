#include "animation.h"
#include <cmath>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Easing functions
float Easing::linear(float t) {
    return t;
}

float Easing::easeInQuad(float t) {
    return t * t;
}

float Easing::easeOutQuad(float t) {
    return 1.0f - (1.0f - t) * (1.0f - t);
}

float Easing::easeInOutQuad(float t) {
    return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
}

float Easing::easeOutCubic(float t) {
    float f = t - 1.0f;
    return f * f * f + 1.0f;
}

float Easing::easeInOutCubic(float t) {
    return t < 0.5f ? 4.0f * t * t * t : 1.0f + (t - 1.0f) * (2.0f * (t - 2.0f)) * (2.0f * (t - 2.0f));
}

float Easing::easeOutBounce(float t) {
    if (t < 0.36363f) return 7.5625f * t * t;
    else if (t < 0.72727f) return 7.5625f * (t -= 0.545454f) * t + 0.75f;
    else if (t < 0.909091f) return 7.5625f * (t -= 0.818181f) * t + 0.9375f;
    else return 7.5625f * (t -= 0.954545f) * t + 0.984375f;
}

float Easing::easeOutElastic(float t) {
    float p = 0.3f;
    float s = p / 4.0f;
    return std::pow(2.0f, -10.0f * t) * std::sin((t - s) * (2.0f * M_PI) / p) + 1.0f;
}

// AnimationSequence implementation
AnimationSequence::AnimationSequence(EmotionState emo) 
    : emotion(emo), current_frame(0), elapsed_time(0), playing(false) {}

AnimationSequence::~AnimationSequence() {}

void AnimationSequence::add_frame(const AnimationFrame& frame) {
    frames.push_back(frame);
}

AnimationFrame* AnimationSequence::get_frame(uint32_t index) {
    if (index >= frames.size()) return nullptr;
    return &frames[index];
}

uint32_t AnimationSequence::get_frame_count() const {
    return frames.size();
}

uint32_t AnimationSequence::get_total_duration() const {
    uint32_t total = 0;
    for (const auto& frame : frames) {
        total += frame.duration_ms;
    }
    return total;
}

void AnimationSequence::play() {
    playing = true;
    current_frame = 0;
    elapsed_time = 0;
}

void AnimationSequence::stop() {
    playing = false;
    current_frame = 0;
    elapsed_time = 0;
}

void AnimationSequence::pause() {
    playing = false;
}

bool AnimationSequence::is_playing() const {
    return playing;
}

AnimationFrame* AnimationSequence::get_current_frame() {
    if (current_frame >= frames.size()) return nullptr;
    return &frames[current_frame];
}

AnimationFrame* AnimationSequence::get_next_frame() {
    if (current_frame + 1 >= frames.size()) return nullptr;
    return &frames[current_frame + 1];
}

void AnimationSequence::advance_frame() {
    if (!playing || frames.empty()) return;
    
    elapsed_time += ANIMATION_FRAME_TIME;
    
    if (current_frame < frames.size() && elapsed_time >= frames[current_frame].duration_ms) {
        elapsed_time = 0;
        current_frame++;
        if (current_frame >= frames.size()) {
            current_frame = 0;  // Loop
        }
    }
}

// AnimationEngine implementation
AnimationEngine g_animation_engine;

AnimationEngine::AnimationEngine() 
    : current_sequence(nullptr), current_emotion(EMO_NEUTRAL), last_update_time(0) {}

AnimationEngine::~AnimationEngine() {
    if (current_sequence) delete current_sequence;
}

void AnimationEngine::initialize() {
    // Pre-load all animations
    load_happy_animation();
    load_sad_animation();
    load_angry_animation();
    load_excited_animation();
    load_thinking_animation();
    load_listening_animation();
    load_speaking_animation();
    load_error_animation();
    load_sleep_animation();
    load_loading_animation();
}

void AnimationEngine::update(uint32_t delta_time) {
    if (!current_sequence) return;
    current_sequence->advance_frame();
}

void AnimationEngine::play_emotion(EmotionState emotion) {
    if (current_sequence) {
        delete current_sequence;
    }
    
    current_sequence = new AnimationSequence(emotion);
    current_emotion = emotion;
    
    // Load appropriate animation based on emotion
    switch (emotion) {
        case EMO_HAPPY:
            load_happy_animation();
            break;
        case EMO_SAD:
            load_sad_animation();
            break;
        case EMO_ANGRY:
            load_angry_animation();
            break;
        case EMO_EXCITED:
            load_excited_animation();
            break;
        case EMO_THINKING:
            load_thinking_animation();
            break;
        case EMO_LISTENING:
            load_listening_animation();
            break;
        case EMO_SPEAKING:
            load_speaking_animation();
            break;
        case EMO_ERROR:
            load_error_animation();
            break;
        case EMO_SLEEP:
            load_sleep_animation();
            break;
        case EMO_PROCESSING:
            load_loading_animation();
            break;
        default:
            break;
    }
    
    current_sequence->play();
}

void AnimationEngine::stop_animation() {
    if (current_sequence) {
        current_sequence->stop();
    }
}

void AnimationEngine::pause_animation() {
    if (current_sequence) {
        current_sequence->pause();
    }
}

void AnimationEngine::resume_animation() {
    if (current_sequence) {
        current_sequence->play();
    }
}

AnimationFrame* AnimationEngine::get_current_frame() {
    if (current_sequence) {
        return current_sequence->get_current_frame();
    }
    return nullptr;
}

EmotionState AnimationEngine::get_current_emotion() const {
    return current_emotion;
}

void AnimationEngine::load_happy_animation() {
    // TODO: Load happy animation frames from SD or generate procedurally
}

void AnimationEngine::load_sad_animation() {
    // TODO: Load sad animation frames
}

void AnimationEngine::load_angry_animation() {
    // TODO: Load angry animation frames
}

void AnimationEngine::load_excited_animation() {
    // TODO: Load excited animation frames
}

void AnimationEngine::load_thinking_animation() {
    // TODO: Load thinking animation frames
}

void AnimationEngine::load_listening_animation() {
    // TODO: Load listening animation frames
}

void AnimationEngine::load_speaking_animation() {
    // TODO: Load speaking animation frames
}

void AnimationEngine::load_error_animation() {
    // TODO: Load error animation frames
}

void AnimationEngine::load_sleep_animation() {
    // TODO: Load sleep animation frames
}

void AnimationEngine::load_loading_animation() {
    // TODO: Load loading animation frames
}
