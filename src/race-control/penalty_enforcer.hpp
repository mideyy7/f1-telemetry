#pragma once

#include "../common/types.hpp"
#include <map>
#include <mutex>

enum class PenaltyState {
    NONE,
    SERVING, 
    SERVED,
    PENDING
};

struct DriverPenaltyInfo {
    PenaltyState state;
    int penalty_seconds;
    int penalty_start_time_ns;
    int penalty_duration_ns;
};

class PenaltyEnforcer {
    public:
        PenaltyEnforcer(const std::vector<DriverProfile> &drivers);

        void issuePenalty(int driver_id, int seconds);
        bool shouldServePenalty(int driver_id, int current_time_ns);
        bool isPenaltyComplete(int driver_id, int current_time_ns);
        DriverPenaltyInfo getPenaltyInfo(int driver_id) const;
    private:
        mutable std::mutex mutex_;
        std::map<int, DriverPenaltyInfo> penalties_;
};