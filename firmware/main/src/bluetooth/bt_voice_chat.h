#ifndef BT_VOICE_CHAT_H
#define BT_VOICE_CHAT_H

#include <string>
#include <stdint.h>

class BluetoothVoiceChat {
public:
    BluetoothVoiceChat();
    ~BluetoothVoiceChat();
    
    bool initialize();
    
    // Microphone (input)
    bool start_recording();
    void stop_recording();
    uint8_t* get_recorded_audio(size_t* size);
    
    // Speaker (output)
    bool start_playback();
    void stop_playback();
    bool send_audio(const uint8_t* audio_data, size_t size);
    
private:
    uint8_t* mic_buffer;
    size_t mic_size;
};

extern BluetoothVoiceChat g_bt_voice_chat;

#endif // BT_VOICE_CHAT_H
