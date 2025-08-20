#pragma once

#include <string>
#include <vector>
#include <chrono>
#include "core/notifications.h"

namespace finance {
class FinanceRepo;
}

// AdminApp encapsulates the CLI for the Administration/Finance module.  It
// provides commands to manage financial records, suppliers and reports.
class AdminApp {
public:
    AdminApp();
    ~AdminApp();
    int run(int argc, char** argv);

    void addDeliveryDate(const std::string& id,
                         std::chrono::system_clock::time_point due);

private:
    void showHelp() const;
    void handleAddTransaction(const std::vector<std::string>& args);
    void handleListTransactions() const;
    void handleSumTransactions(const std::vector<std::string>& args) const;
    void handleSuppliers() const;

    finance::FinanceRepo* repo_;
    core::NotificationService notifications_;
};

