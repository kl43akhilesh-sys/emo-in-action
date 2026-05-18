#include "bt_speaker.h"
#include "esp_a2dp_api.h"

BluetoothSpeaker g_bt_speaker;

BluetoothSpeaker::BluetoothSpeaker() : connected(false), volume(8) {}

BluetoothSpeaker::~BluetoothSpeaker() {}

bool BluetoothSpeaker::initialize() {
    // TODO: Initialize A2DP sink profile
    connected = true;
    return true;
}

bool BluetoothSpeaker::is_connected() {
    return connected;
}

bool BluetoothSpeaker::stream_audio(const uint8_t* audio_data, size_t size) {
    // TODO: Stream audio via A2DP
    return true;
}

bool BluetoothSpeaker::play_pcm(const uint8_t* pcm_data, size_t size, int sample_rate) {
    // TODO: Encode PCM and stream via A2DP
    return true;
}

void BluetoothSpeaker::set_volume(int level) {
    volume = level;
    // TODO: Set ESP32 DAC volume
}

int BluetoothSpeaker::get_volume() {
    return volume;
}

void BluetoothSpeaker::pause() {
    // TODO: Pause playback
}

void BluetoothSpeaker::resume() {
    // TODO: Resume playback
}

void BluetoothSpeaker::stop() {
    // TODO: Stop playback
}
