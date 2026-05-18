#ifndef BT_SPEAKER_H
#define BT_SPEAKER_H

#include <stdint.h>
#include <string>

class BluetoothSpeaker {
public:
    BluetoothSpeaker();
    ~BluetoothSpeaker();
    
    bool initialize();
    bool is_connected();
    
    // Audio streaming
    bool stream_audio(const uint8_t* audio_data, size_t size);
    bool play_pcm(const uint8_t* pcm_data, size_t size, int sample_rate);
    
    // Volume control
    void set_volume(int level);  // 0-15
    int get_volume();
    
    // Playback control
    void pause();
    void resume();
    void stop();
    
private:
    bool connected;
    int volume;
};

extern BluetoothSpeaker g_bt_speaker;

#endif // BT_SPEAKER_H
