#pragma once

#include <string>
#include <vector>

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

private:
    void showHelp() const;
    void handleAddTransaction(const std::vector<std::string>& args);
    void handleListTransactions() const;
    void handleSumTransactions(const std::vector<std::string>& args) const;
    void handleSuppliers() const;
    void handleReport(const std::vector<std::string>& args) const;

    finance::FinanceRepo* repo_;
};

