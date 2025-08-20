#include "core/notifications.h"
#include <cassert>
#include <chrono>

void test_overdue_alert() {
    core::NotificationService service;
    auto now = std::chrono::system_clock::now();
    service.addDelivery("pedido1", now - std::chrono::hours(24));
    auto alerts = service.dueAlerts(now);
    assert(alerts.size() == 1);
    assert(alerts[0] == "pedido1");
}
