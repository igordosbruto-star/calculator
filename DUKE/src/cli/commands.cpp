#include <iostream>
#include <limits>
#include <string>
#include "cli/commands.h"
#include "core/Debug.h"
#include "ui/Menu.h"

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
    m.valor = ui::readDouble("Valor: ");
    m.largura = ui::readDouble("Largura: ");
    m.comprimento = ui::readDouble("Comprimento: ");
    base.push_back(m);
    salvarReconstruir(base, mats);
}

void editarMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
    if (base.empty()) return;
    listarMateriais(base);
    size_t idx = 0;
    while (true) {
        int input = ui::readInt("Indice para editar: ");
        if (input >= 1 && static_cast<size_t>(input) <= base.size()) {
            idx = static_cast<size_t>(input);
            break;
        }
        std::cout << "Indice invalido.\n";
    }
    MaterialDTO& m = base[idx - 1];
    std::string nome;
    std::cout << "Nome (" << m.nome << "): ";
    std::getline(std::cin, nome);
    if (!nome.empty()) m.nome = nome;
    m.valor = ui::readDouble("Valor (" + std::to_string(m.valor) + "): ");
    m.largura = ui::readDouble("Largura (" + std::to_string(m.largura) + "): ");
    m.comprimento = ui::readDouble("Comprimento (" + std::to_string(m.comprimento) + "): ");
    salvarReconstruir(base, mats);
}

void removerMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
    if (base.empty()) return;
    listarMateriais(base);
    size_t idx = 0;
    while (true) {
        int input = ui::readInt("Indice para remover: ");
        if (input >= 1 && static_cast<size_t>(input) <= base.size()) {
            idx = static_cast<size_t>(input);
            break;
        }
        std::cout << "Indice invalido.\n";
    }
    base.erase(base.begin() + static_cast<long>(idx - 1));
    salvarReconstruir(base, mats);
}

} // namespace duke::cli

