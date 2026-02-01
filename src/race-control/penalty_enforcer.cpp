#include "penalty_enforcer.hpp"

PenaltyEnforcer::PenaltyEnforcer(const std::vector<DriverProfile> &drivers) {
    for(int i = 0; i < drivers.size(); i++) {
        penalties_.insert({i, {PenaltyState::NONE, 0, 0ULL, 0ULL}});
    }
}


bool PenaltyEnforcer::isPenaltyComplete(int driver_id, int current_time_ns) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto &info = penalties_[driver_id];

    if (info.state == PenaltyState::NONE) {
        return true;
    }
    if (info.state == PenaltyState::SERVED) {
        return true;
    } 
    if (info.state == PenaltyState::PENDING) {
        return false;
    }
    
    if (current_time_ns >= info.penalty_start_time_ns + info.penalty_duration_ns) {
        info.state = PenaltyState::SERVED;
        return true;
    }
    return false;
}

DriverPenaltyInfo PenaltyEnforcer::getPenaltyInfo(int driver_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return penalties_.at(driver_id);
}

