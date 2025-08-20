#pragma once

#include <string>
#include <vector>

// DesignerApp allows users to create and edit product designs.  It
// provides a canvas for assembling components, associating materials and
// estimating costs.
class DesignerApp {
public:
    DesignerApp();
    ~DesignerApp();
    int run(int argc, char** argv);

private:
    void showHelp() const;
    void handleNewProject(const std::vector<std::string>& args);
    void handleLoadProject(const std::vector<std::string>& args);
    void handleExportBOM(const std::vector<std::string>& args) const;
};

