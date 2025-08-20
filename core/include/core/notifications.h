#pragma once

#include <string>
#include <vector>
#include <chrono>

namespace core {

struct DeliveryInfo {
    std::string id;
    std::chrono::system_clock::time_point due;
    bool alerted = false;
};

class NotificationService {
public:
    void addDelivery(const std::string& id,
                     const std::chrono::system_clock::time_point& due);
    std::vector<std::string> dueAlerts(const std::chrono::system_clock::time_point& now);

private:
    std::vector<DeliveryInfo> deliveries_;
};

} // namespace core

