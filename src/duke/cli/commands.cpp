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
    size_t idx = readMaterialIndex(base, "Indice para editar: ");
    MaterialDTO& m = base[idx];
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
    size_t idx = readMaterialIndex(base, "Indice para remover: ");
    base.erase(base.begin() + static_cast<long>(idx));
    salvarReconstruir(base, mats);
}

} // namespace duke::cli

