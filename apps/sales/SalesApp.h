#pragma once

#include <string>
#include <vector>

// Forward declarations to avoid heavy includes.  The implementation will
// include the necessary headers from the existing DUKE codebase (such as
// ApplicationCore, Material, etc.).
namespace duke {
class ApplicationCore;
}

// SalesApp encapsulates the CLI for the Sales module.  It handles
// customer management, order entry and stock checks for finished products.
class SalesApp {
public:
    SalesApp();
    ~SalesApp();

    // Entry point.  Pass the command‑line arguments and dispatch the
    // appropriate subcommands.
    int run(int argc, char** argv);

private:
    // Implementation helpers
    void showHelp() const;
    void handleNewOrder(const std::vector<std::string>& args);
    void handleListCustomers() const;
    void handleInventory() const;
    void handleReport(const std::vector<std::string>& args) const;

    // Pointer to core application logic.  This object will be used to
    // load materials, customers and persist changes.
    duke::ApplicationCore* core_;
};

