#pragma once

#include <string>
#include <vector>

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

private:
    void showHelp() const;
    void handleListOrders() const;
    void handleStartOrder(const std::vector<std::string>& args);
    void handleFinishOrder(const std::vector<std::string>& args);

    duke::ApplicationCore* core_;
};

