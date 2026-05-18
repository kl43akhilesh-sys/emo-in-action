#include "whisper_api.h"
#include "esp_http_client.h"
#include <cstring>
#include <cstdio>

WhisperAPI g_whisper_api;

WhisperAPI::WhisperAPI() {}

WhisperAPI::~WhisperAPI() {}

bool WhisperAPI::initialize(const std::string& key) {
    api_key = key;
    return true;
}

bool WhisperAPI::transcribe(const uint8_t* audio_data, size_t audio_size, std::string& result) {
    // TODO: Implement HTTP multipart upload to Whisper API
    // POST to OPENAI_WHISPER_ENDPOINT
    // Send audio data with API key
    result = "Transcribed text";
    return true;
}

std::string WhisperAPI::get_last_error() const {
    return last_error;
}
