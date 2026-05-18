#include "alarm_ringtone.h"
#include "utils/sd_manager.h"

AlarmRingtone::AlarmRingtone() : audio_buffer(nullptr), audio_size(0), playing(false), volume(80) {}

AlarmRingtone::~AlarmRingtone() {
    if (audio_buffer) {
        delete[] audio_buffer;
    }
}

bool AlarmRingtone::load_from_sd(const std::string& path) {
    if (audio_buffer) delete[] audio_buffer;
    
    audio_buffer = new uint8_t[1024 * 1024];  // 1MB buffer
    size_t size = 0;
    
    if (g_sd_manager.read_file(path, audio_buffer, &size)) {
        audio_size = size;
        return true;
    }
    return false;
}

bool AlarmRingtone::play_through_speaker() {
    // TODO: Play audio through Bluetooth A2DP
    playing = true;
    return true;
}

void AlarmRingtone::stop_playback() {
    playing = false;
}

bool AlarmRingtone::is_playing() {
    return playing;
}

void AlarmRingtone::set_volume(int vol) {
    volume = vol;
}
