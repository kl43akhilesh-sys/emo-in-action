#include "elevenlabs_api.h"
#include "esp_http_client.h"
#include <cstring>
#include <cstdio>

ElevenLabsAPI g_elevenlabs_api;

ElevenLabsAPI::ElevenLabsAPI() : voice_speed(100), voice_pitch(100) {}

ElevenLabsAPI::~ElevenLabsAPI() {}

bool ElevenLabsAPI::initialize(const std::string& key) {
    api_key = key;
    return true;
}

bool ElevenLabsAPI::text_to_speech(const std::string& text, const std::string& voice_id,
                                    uint8_t* audio_buffer, size_t* audio_size) {
    // TODO: Implement HTTP request to ElevenLabs API
    // POST to ELEVENLABS_TTS_ENDPOINT
    // Receive MP3 audio and stream to Bluetooth speaker
    *audio_size = 0;
    return true;
}

void ElevenLabsAPI::set_voice_gender(const std::string& gender) {
    voice_gender = gender;
}

void ElevenLabsAPI::set_voice_speed(int speed) {
    voice_speed = speed;
}

void ElevenLabsAPI::set_voice_pitch(int pitch) {
    voice_pitch = pitch;
}

std::string ElevenLabsAPI::get_last_error() const {
    return last_error;
}
