#include <iostream>
#include <limits>
#include <string>
#include "cli/commands.h"
#include "core/Debug.h"

namespace duke::cli {

void adicionarMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
    MaterialDTO m;
    std::cout << "Nome: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, m.nome);
    std::cout << "Tipo (unitario/linear/cubico) [linear]: ";
    std::string tipo;
    std::getline(std::cin, tipo);
    if (!tipo.empty()) {
        if (tipo == "unitario" || tipo == "linear" || tipo == "cubico") {
            m.tipo = tipo;
        } else {
            wr::p("APP", "Tipo invalido. Usando 'linear'.", "Yellow");
        }
    }
    std::cout << "Valor: ";
    std::cin >> m.valor;
    std::cout << "Largura: ";
    std::cin >> m.largura;
    std::cout << "Comprimento: ";
    std::cin >> m.comprimento;
    base.push_back(m);
    salvarReconstruir(base, mats);
}

void editarMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
    if (base.empty()) return;
    listarMateriais(base);
    std::cout << "Indice para editar: ";
    size_t idx = 0;
    if (!(std::cin >> idx) || idx < 1 || idx > base.size()) {
        std::cout << "Indice invalido.\n";
        return;
    }
    MaterialDTO& m = base[idx - 1];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string nome;
    std::cout << "Nome (" << m.nome << "): ";
    std::getline(std::cin, nome);
    if (!nome.empty()) m.nome = nome;
    std::cout << "Valor (" << m.valor << "): ";
    std::cin >> m.valor;
    std::cout << "Largura (" << m.largura << "): ";
    std::cin >> m.largura;
    std::cout << "Comprimento (" << m.comprimento << "): ";
    std::cin >> m.comprimento;
    salvarReconstruir(base, mats);
}

void removerMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
    if (base.empty()) return;
    listarMateriais(base);
    std::cout << "Indice para remover: ";
    size_t idx = 0;
    if (!(std::cin >> idx) || idx < 1 || idx > base.size()) {
        std::cout << "Indice invalido.\n";
        return;
    }
    base.erase(base.begin() + static_cast<long>(idx - 1));
    salvarReconstruir(base, mats);
}

} // namespace duke::cli

