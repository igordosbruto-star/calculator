#include "DesignerApp.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>
#include "finance/Repo.h"
#include "core/reports.h"

using nlohmann::json;

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
    } else if (command == "report") {
        handleReport(args);
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
    std::cout << "  report <ano> <mes>        Generate consolidated report\n";
}

void DesignerApp::handleNewProject(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "Project name required\n";
        return;
    }
    std::string name = args[0];
    projeto_ = production::ModeloProducao(name, name);
    projetoPath_ = name + ".json";

    json j;
    j["name"] = name;
    j["versions"] = json::array();
    json ver;
    ver["timestamp"] = static_cast<int>(std::time(nullptr));
    ver["components"] = json::array();
    j["versions"].push_back(ver);

    std::ofstream f(projetoPath_);
    if (!f) {
        std::cerr << "Failed to create project file\n";
        return;
    }
    f << j.dump(4);
    std::cout << "Project created: " << projetoPath_ << "\n";
}

void DesignerApp::handleLoadProject(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "Project file required\n";
        return;
    }
    projetoPath_ = args[0];
    std::ifstream f(projetoPath_);
    if (!f) {
        std::cerr << "Cannot open project file: " << projetoPath_ << "\n";
        return;
    }
    json j; f >> j;
    std::string name = j.value("name", "");
    projeto_ = production::ModeloProducao(name, name);
    if (!j["versions"].empty()) {
        const json& ver = j["versions"].back();
        for (const auto& compJ : ver.value("components", json::array())) {
            production::Componente c;
            c.nome = compJ.value("nome", "");
            for (const auto& matJ : compJ.value("materiais", json::array())) {
                production::ItemMaterial im;
                im.nome = matJ.value("nome", "");
                im.unidade = matJ.value("unidade", "");
                im.quantidade = matJ.value("quantidade", 0.0);
                c.materiais.push_back(im);
            }
            projeto_->adicionarComponente(c);
        }
    }
    std::cout << "Project loaded: " << projetoPath_ << "\n";
}

void DesignerApp::handleExportBOM(const std::vector<std::string>& args) const {
    if (!projeto_) {
        std::cerr << "No project loaded\n";
        return;
    }
    if (args.empty()) {
        std::cerr << "Output file required\n";
        return;
    }
    json bom;
    bom["components"] = json::array();
    for (const auto& comp : projeto_->componentes()) {
        json compJ;
        compJ["nome"] = comp.nome;
        compJ["materiais"] = json::array();
        for (const auto& mat : comp.materiais) {
            compJ["materiais"].push_back({
                {"nome", mat.nome},
                {"unidade", mat.unidade},
                {"quantidade", mat.quantidade}
            });
        }
        bom["components"].push_back(compJ);
    }
    std::ofstream f(args[0]);
    if (!f) {
        std::cerr << "Failed to write BOM file\n";
        return;
    }
    f << bom.dump(4);
    std::cout << "BOM exported to " << args[0] << "\n";
}

void DesignerApp::handleReport(const std::vector<std::string>& args) const {
    if (args.size() < 2) {
        std::cerr << "Usage: report <year> <month>\n";
        return;
    }
    int year = std::stoi(args[0]);
    int month = std::stoi(args[1]);
    finance::FinanceRepo repo;
    repo.load();
    auto paths = core::reports::generateMonthlyReport(repo, year, month);
    std::cout << "CSV: " << paths.first << "\nPDF: " << paths.second << "\n";
}

