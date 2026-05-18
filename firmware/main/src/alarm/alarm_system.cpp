#include "alarm_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ctime>
#include <cstdio>

AlarmSystem g_alarm_system;

AlarmSystem::AlarmSystem() : ringing_alarm_id(-1), ringing_start_time(0) {}

AlarmSystem::~AlarmSystem() {}

void AlarmSystem::initialize() {
    // Initialize alarms from config
}

void AlarmSystem::update() {
    check_alarms();
}

void AlarmSystem::create_alarm(int id, int hour, int minute, const std::string& label) {
    AlarmInstance alarm;
    alarm.id = id;
    alarm.enabled = false;
    alarm.hour = hour;
    alarm.minute = minute;
    alarm.label = label;
    alarm.repeat_daily = false;
    alarm.snooze_interval = 5;
    for (int i = 0; i < 7; i++) {
        alarm.repeat_days.push_back(false);
    }
    alarms.push_back(alarm);
}

void AlarmSystem::delete_alarm(int id) {
    for (auto it = alarms.begin(); it != alarms.end(); ++it) {
        if (it->id == id) {
            alarms.erase(it);
            break;
        }
    }
}

void AlarmSystem::enable_alarm(int id) {
    for (auto& alarm : alarms) {
        if (alarm.id == id) {
            alarm.enabled = true;
            break;
        }
    }
}

void AlarmSystem::disable_alarm(int id) {
    for (auto& alarm : alarms) {
        if (alarm.id == id) {
            alarm.enabled = false;
            break;
        }
    }
}

void AlarmSystem::snooze_alarm(int id, int minutes) {
    // Snooze alarm for N minutes
}

void AlarmSystem::dismiss_alarm(int id) {
    ringing_alarm_id = -1;
}

AlarmInstance* AlarmSystem::get_alarm(int id) {
    for (auto& alarm : alarms) {
        if (alarm.id == id) {
            return &alarm;
        }
    }
    return nullptr;
}

std::vector<AlarmInstance>& AlarmSystem::get_all_alarms() {
    return alarms;
}

bool AlarmSystem::is_alarm_ringing() {
    return ringing_alarm_id >= 0;
}

int AlarmSystem::get_ringing_alarm_id() {
    return ringing_alarm_id;
}

void AlarmSystem::check_alarms() {
    time_t now = time(nullptr);
    struct tm* time_info = localtime(&now);
    
    for (const auto& alarm : alarms) {
        if (alarm.enabled && 
            alarm.hour == time_info->tm_hour && 
            alarm.minute == time_info->tm_min) {
            trigger_alarm(alarm.id);
        }
    }
}

void AlarmSystem::trigger_alarm(int id) {
    ringing_alarm_id = id;
    ringing_start_time = xTaskGetTickCount();
}
