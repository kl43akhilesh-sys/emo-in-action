#ifndef GEMINI_API_H
#define GEMINI_API_H

#include <string>
#include <vector>
#include <stdint.h>
#include "constants.h"

class GeminiAPI {
public:
    GeminiAPI();
    ~GeminiAPI();
    
    bool initialize(const std::string& api_key);
    
    // Generate response from text
    bool generate_response(const std::string& prompt, std::string& response, EmotionState& emotion);
    
    // Get sentiment/emotion from text
    EmotionState analyze_sentiment(const std::string& text);
    
    std::string get_last_error() const;
    
private:
    std::string api_key;
    std::string last_error;
};

extern GeminiAPI g_gemini_api;

#endif // GEMINI_API_H
