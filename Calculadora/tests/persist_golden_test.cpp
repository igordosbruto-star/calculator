#include "core/persist.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

// Lê arquivo inteiro em string
static std::string readFile(const std::string& path) {
    std::ifstream f(path);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

// Compara saídas de CSV/JSON com arquivos golden
void testPersistGolden() {
    std::vector<MaterialDTO> itens{{"Madeira", 10.0, 2.0, 3.0, "linear"}};

    // JSON estável
    assert(Persist::saveJSON("gold.json", itens));
    std::string outJson = readFile("data/gold.json");
    std::string goldenJson = readFile("tests/data/ok.json");
    assert(outJson == goldenJson);

    // CSV estável
    assert(Persist::saveCSV("gold.csv", itens));
    std::string outCsv = readFile("data/gold.csv");
    std::string goldenCsv = readFile("tests/data/ok.csv");
    assert(outCsv == goldenCsv);

    std::filesystem::remove("data/gold.json");
    std::filesystem::remove("data/gold.csv");
}
