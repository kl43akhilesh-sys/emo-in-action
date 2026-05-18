#ifndef WHISPER_API_H
#define WHISPER_API_H

#include <string>
#include <vector>
#include <stdint.h>

class WhisperAPI {
public:
    WhisperAPI();
    ~WhisperAPI();
    
    bool initialize(const std::string& api_key);
    
    // Convert audio to text
    bool transcribe(const uint8_t* audio_data, size_t audio_size, std::string& result);
    
    // Get last error
    std::string get_last_error() const;
    
private:
    std::string api_key;
    std::string last_error;
};

extern WhisperAPI g_whisper_api;

#endif // WHISPER_API_H
