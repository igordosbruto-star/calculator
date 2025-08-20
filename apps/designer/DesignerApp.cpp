#include "DesignerApp.h"
#include <iostream>

DesignerApp::DesignerApp() {}

DesignerApp::~DesignerApp() {}

int DesignerApp::run(int argc, char** argv) {
    if (argc < 2) {
        showHelp();
        return 0;
    }
    std::string command = argv[1];
    std::vector<std::string> args(argv + 2, argv + argc);
    if (command == "new") {
        handleNewProject(args);
    } else if (command == "load") {
        handleLoadProject(args);
    } else if (command == "export-bom") {
        handleExportBOM(args);
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        showHelp();
    }
    return 0;
}

void DesignerApp::showHelp() const {
    std::cout << "DUKE Designer App Commands:\n";
    std::cout << "  new <name>                Create a new design project\n";
    std::cout << "  load <file>               Load a design project\n";
    std::cout << "  export-bom <file>         Export Bill of Materials for the current design\n";
}

void DesignerApp::handleNewProject(const std::vector<std::string>& args) {
    std::cout << "Creating new project...\n";
    // TODO: initialize a new design canvas
}

void DesignerApp::handleLoadProject(const std::vector<std::string>& args) {
    std::cout << "Loading project...\n";
    // TODO: load project from file and display in canvas
}

void DesignerApp::handleExportBOM(const std::vector<std::string>& args) const {
    std::cout << "Exporting BOM...\n";
    // TODO: export list of materials for current design
}

