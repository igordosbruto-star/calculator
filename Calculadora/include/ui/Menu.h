#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace ui {

// Limpa a tela do terminal
// Exemplo:
// clearScreen();
void clearScreen(std::ostream& out = std::cout);

// Renderiza o caminho atual do menu como "A > B"
// Exemplo:
// renderBreadcrumb({"Principal", "Config"});
void renderBreadcrumb(const std::vector<std::string>& trail,
                      std::ostream& out = std::cout);

// Exibe um menu enumerado e retorna a opção escolhida (1..n)
// Exemplo:
// int escolha = promptMenu({"Opcao A", "Opcao B"});
int promptMenu(const std::vector<std::string>& options,
               std::istream& in = std::cin,
               std::ostream& out = std::cout);

// Lê um inteiro do usuário
// Exemplo:
// int v = readInt("Quantos? ");
int readInt(const std::string& prompt,
            std::istream& in = std::cin,
            std::ostream& out = std::cout);

// Lê um número real do usuário
// Exemplo:
// double d = readDouble("Valor: ");
double readDouble(const std::string& prompt,
                  std::istream& in = std::cin,
                  std::ostream& out = std::cout);

// Lê uma linha do usuário
// Exemplo:
// std::string nome = readString("Nome: ");
std::string readString(const std::string& prompt,
                       std::istream& in = std::cin,
                       std::ostream& out = std::cout);

} // namespace ui

