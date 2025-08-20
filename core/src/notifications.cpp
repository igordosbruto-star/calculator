#include "core/notifications.h"

namespace core {

void NotificationService::addDelivery(const std::string& id,
                                      const std::chrono::system_clock::time_point& due) {
    deliveries_.push_back({id, due, false});
}

std::vector<std::string> NotificationService::dueAlerts(
        const std::chrono::system_clock::time_point& now) {
    std::vector<std::string> alerts;
    for (auto& d : deliveries_) {
        if (!d.alerted && d.due <= now) {
            alerts.push_back(d.id);
            d.alerted = true;
        }
    }
    return alerts;
}

} // namespace core

