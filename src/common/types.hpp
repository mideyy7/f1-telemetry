#pragma once

#include <string>

struct CarProfile {
    std::string car_id;

    // performance characteristics (0.0- 1.0)
    float engine_power;
    float aero_efficienccy;
    float cooling_efficiency;
    float reliability;
};

struct DriverProfile {
    std::string driver_id;

    // behavioural traits (0.0 - 1.0)
    float aggression;
    float consistency;
    float tire_management;
    float risk_tolerance;
};

struct TelemetryFrame {
    int race_position;

    int timestamp_ns;

    int driver_id;
    int lap;
    int sector;

    float speed_kph;
    float throttle;
    float brake;

    float tire_temp_c[4];   //FL, FR, RL, RR
    float tire_wear;
};

struct TrackProfile {
    int track_id;

    int sectors;
    float lap_length_km;

    // Environmental multipliers
    float tire_wear_factor;
    float overtaking_difficulty;
    float safety_car_probability;
};

struct DriverState {
    int lap;
    int sector;
    float tire_wear;
    float distance_in_lap;

    bool is_on_pit;
    bool has_pitted;    // Prevent retrigerring a planned pit
    int pit_stop_start_time_ns;
    int pit_stop_end_time_ns;
};