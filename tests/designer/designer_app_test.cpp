#include "DesignerApp.h"
#include <cassert>
#include <fstream>
#include <cstdio>
#include <nlohmann/json.hpp>

using nlohmann::json;

static void writeSampleProject(const std::string& path) {
    json j;
    j["name"] = "sample";
    j["versions"] = json::array();
    json v;
    v["timestamp"] = 0;
    v["components"] = json::array({
        {
            {"nome", "Frame"},
            {"materiais", json::array({
                {{"nome", "Wood"}, {"unidade", "m"}, {"quantidade", 2.0}},
                {{"nome", "Screw"}, {"unidade", "pc"}, {"quantidade", 4.0}}
            })}
        }
    });
    j["versions"].push_back(v);
    std::ofstream f(path);
    f << j.dump(4);
}

void test_designer_create_project() {
    std::remove("create_test.json");
    DesignerApp app;
    const char* argv[] = {"designer", "new", "create_test"};
    app.run(3, const_cast<char**>(argv));

    std::ifstream f("create_test.json");
    assert(f.good());
    json j; f >> j;
    assert(j["name"] == "create_test");
    assert(j["versions"].is_array());
    assert(j["versions"].size() == 1);
}

void test_designer_load_project() {
    writeSampleProject("load_test.json");
    DesignerApp app;
    const char* argv[] = {"designer", "load", "load_test.json"};
    app.run(3, const_cast<char**>(argv));
    assert(app.currentProject().has_value());
    assert(app.currentProject()->componentes().size() == 1);
}

void test_designer_export_bom() {
    writeSampleProject("export_test.json");
    DesignerApp app;
    const char* load[] = {"designer", "load", "export_test.json"};
    app.run(3, const_cast<char**>(load));
    std::remove("bom_test.json");
    const char* exp[] = {"designer", "export-bom", "bom_test.json"};
    app.run(3, const_cast<char**>(exp));

    std::ifstream f("bom_test.json");
    assert(f.good());
    json j; f >> j;
    assert(j["components"].size() == 1);
    assert(j["components"][0]["materiais"].size() == 2);
}

