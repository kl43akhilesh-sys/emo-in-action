#ifndef ALARM_RINGTONE_H
#define ALARM_RINGTONE_H

#include <stdint.h>
#include <string>

class AlarmRingtone {
public:
    AlarmRingtone();
    ~AlarmRingtone();
    
    bool load_from_sd(const std::string& path);
    bool play_through_speaker();
    void stop_playback();
    bool is_playing();
    
    void set_volume(int volume);  // 0-100
    
private:
    uint8_t* audio_buffer;
    size_t audio_size;
    bool playing;
    int volume;
};

#endif // ALARM_RINGTONE_H
