#include "bt_voice_chat.h"

BluetoothVoiceChat g_bt_voice_chat;

BluetoothVoiceChat::BluetoothVoiceChat() : mic_buffer(nullptr), mic_size(0) {}

BluetoothVoiceChat::~BluetoothVoiceChat() {
    if (mic_buffer) delete[] mic_buffer;
}

bool BluetoothVoiceChat::initialize() {
    mic_buffer = new uint8_t[1024 * 1024];  // 1MB buffer
    return true;
}

bool BluetoothVoiceChat::start_recording() {
    // TODO: Start recording from microphone via ADC
    return true;
}

void BluetoothVoiceChat::stop_recording() {
    // TODO: Stop recording
}

uint8_t* BluetoothVoiceChat::get_recorded_audio(size_t* size) {
    *size = mic_size;
    return mic_buffer;
}

bool BluetoothVoiceChat::start_playback() {
    // TODO: Start playback
    return true;
}

void BluetoothVoiceChat::stop_playback() {
    // TODO: Stop playback
}

bool BluetoothVoiceChat::send_audio(const uint8_t* audio_data, size_t size) {
    // TODO: Send audio via Bluetooth speaker
    return true;
}
