#ifndef ALARM_SYSTEM_H
#define ALARM_SYSTEM_H

#include <stdint.h>
#include <string>
#include <vector>
#include "constants.h"

struct AlarmInstance {
    int id;
    bool enabled;
    int hour;
    int minute;
    std::string label;
    bool repeat_daily;
    std::vector<bool> repeat_days;  // Mon-Sun
    int snooze_interval;  // minutes
};

class AlarmSystem {
public:
    AlarmSystem();
    ~AlarmSystem();
    
    void initialize();
    void update();
    
    void create_alarm(int id, int hour, int minute, const std::string& label);
    void delete_alarm(int id);
    void enable_alarm(int id);
    void disable_alarm(int id);
    void snooze_alarm(int id, int minutes);
    void dismiss_alarm(int id);
    
    AlarmInstance* get_alarm(int id);
    std::vector<AlarmInstance>& get_all_alarms();
    
    bool is_alarm_ringing();
    int get_ringing_alarm_id();
    
private:
    std::vector<AlarmInstance> alarms;
    int ringing_alarm_id;
    uint32_t ringing_start_time;
    
    void check_alarms();
    void trigger_alarm(int id);
};

extern AlarmSystem g_alarm_system;

#endif // ALARM_SYSTEM_H
