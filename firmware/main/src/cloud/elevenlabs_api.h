#ifndef ELEVENLABS_API_H
#define ELEVENLABS_API_H

#include <string>
#include <stdint.h>

class ElevenLabsAPI {
public:
    ElevenLabsAPI();
    ~ElevenLabsAPI();
    
    bool initialize(const std::string& api_key);
    
    // Convert text to speech
    bool text_to_speech(const std::string& text, const std::string& voice_id, 
                        uint8_t* audio_buffer, size_t* audio_size);
    
    // Set voice properties
    void set_voice_gender(const std::string& gender);
    void set_voice_speed(int speed);  // 50-200%
    void set_voice_pitch(int pitch);  // 50-200%
    
    std::string get_last_error() const;
    
private:
    std::string api_key;
    std::string voice_gender;
    int voice_speed;
    int voice_pitch;
    std::string last_error;
};

extern ElevenLabsAPI g_elevenlabs_api;

#endif // ELEVENLABS_API_H
