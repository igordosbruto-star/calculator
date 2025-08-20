#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include "apps/production/ProductionApp.h"

// Helper to run app with args and capture output
static std::string runCmd(ProductionApp& app, const std::vector<std::string>& args) {
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>("prod"));
    for (const auto& s : args) argv.push_back(const_cast<char*>(s.c_str()));
    int argc = static_cast<int>(argv.size());
    std::ostringstream buffer;
    auto* oldBuf = std::cout.rdbuf(buffer.rdbuf());
    app.run(argc, argv.data());
    std::cout.rdbuf(oldBuf);
    return buffer.str();
}

void test_order_flow() {
    ProductionApp app;

    // List initial orders
    auto out = runCmd(app, {"list-orders"});
    assert(out.find("A1") != std::string::npos);
    assert(out.find("A2") != std::string::npos);
    assert(out.find("Veludo Rose Gold") != std::string::npos);

    // Start first order
    out = runCmd(app, {"start-order", "A1"});
    assert(out.find("started") != std::string::npos);

    // Attempt to start second order should fail due to lack of material
    out = runCmd(app, {"start-order", "A2"});
    assert(out.find("Insufficient material") != std::string::npos);

    // Finish first order
    out = runCmd(app, {"finish-order", "A1"});
    assert(out.find("finished") != std::string::npos);

    // List orders again: only A2 should appear
    out = runCmd(app, {"list-orders"});
    assert(out.find("A1") == std::string::npos);
    assert(out.find("A2") != std::string::npos);
}
