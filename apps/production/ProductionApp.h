#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "production/ModeloProducao.h"
#include "core/notifications.h"

namespace duke {
class ApplicationCore;
}

// ProductionApp encapsulates the CLI for the Production module.  It will
// manage work orders, consume materials and register time spent.
class ProductionApp {
public:
    ProductionApp();
    ~ProductionApp();
    int run(int argc, char** argv);

    void addDeliveryDate(const std::string& id,
                         std::chrono::system_clock::time_point due);

private:
    void showHelp() const;
    void handleListOrders() const;
    void handleStartOrder(const std::vector<std::string>& args);
    void handleFinishOrder(const std::vector<std::string>& args);

    duke::ApplicationCore* core_;

    struct ProductionOrder {
        std::string id;
        const production::ModeloProducao* modelo;
        bool started = false;
        bool finished = false;
    };

    std::vector<production::ModeloProducao> modelos_;
    std::vector<ProductionOrder> orders_;
    std::map<std::string, double> estoque_;
    core::NotificationService notifications_;
};

