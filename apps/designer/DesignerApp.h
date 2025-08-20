#pragma once

#include <string>
#include <vector>
#include <optional>
#include "production/ModeloProducao.h"

// DesignerApp allows users to create and edit product designs.  It
// provides a canvas for assembling components, associating materials and
// estimating costs.
class DesignerApp {
public:
    DesignerApp();
    ~DesignerApp();
    int run(int argc, char** argv);

    // Helpers used by tests
    const std::optional<production::ModeloProducao>& currentProject() const { return projeto_; }
    const std::string& currentProjectFile() const { return projetoPath_; }

private:
    void showHelp() const;
    void handleNewProject(const std::vector<std::string>& args);
    void handleLoadProject(const std::vector<std::string>& args);
    void handleExportBOM(const std::vector<std::string>& args) const;
    void handleReport(const std::vector<std::string>& args) const;

    std::optional<production::ModeloProducao> projeto_;
    std::string projetoPath_;
};

