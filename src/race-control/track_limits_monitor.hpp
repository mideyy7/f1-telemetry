#pragma once

#include "../common/types.hpp"
#include <vector>
#include <map>
#include <mutex>
#include "penalty_enforcer.hpp"

struct TrackLimitsState {
    int warnings;
    bool has_penalty;
    std::vector<int> violation_laps;
};

class TrackLimitsMonitor {
    public:
        TrackLimitsMonitor(const TrackProfile &track, const std::vector<DriverProfile> &drivers, std::shared_ptr<PenaltyEnforcer> penalty_enforcer);
        void processFrame(const TelemetryFrame &frame);
        TrackLimitsState getDriverState(int driver_id) const;
    private:
        TrackProfile track_;
        std::vector<DriverProfile> drivers_;
        std::shared_ptr<PenaltyEnforcer> penalty_enforcer_;
        std::map<int, TrackLimitsState> driver_violations_;
        mutable std::mutex mutex_;
};