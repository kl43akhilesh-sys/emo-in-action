#include "gemini_api.h"
#include "esp_http_client.h"
#include <cstring>
#include <cstdio>

GeminiAPI g_gemini_api;

GeminiAPI::GeminiAPI() {}

GeminiAPI::~GeminiAPI() {}

bool GeminiAPI::initialize(const std::string& key) {
    api_key = key;
    return true;
}

bool GeminiAPI::generate_response(const std::string& prompt, std::string& response, EmotionState& emotion) {
    // TODO: Implement HTTP request to Gemini API
    // POST to GOOGLE_GEMINI_ENDPOINT
    response = "I am happy to help!";
    emotion = EMO_HAPPY;
    return true;
}

EmotionState GeminiAPI::analyze_sentiment(const std::string& text) {
    // TODO: Analyze text sentiment and map to emotion
    return EMO_NEUTRAL;
}

std::string GeminiAPI::get_last_error() const {
    return last_error;
}
