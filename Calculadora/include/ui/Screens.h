#pragma once

#include <string>

namespace ui {

// Estados possíveis do menu principal
// Exemplo:
// MenuState s = MenuState::Principal;
enum class MenuState { Principal, Criar, Listar, Comparar, Config, Sair };

// Converte o estado para string
// Exemplo:
// std::string nome = toString(MenuState::Config);
inline std::string toString(MenuState s) {
    switch (s) {
        case MenuState::Principal: return "Principal";
        case MenuState::Criar: return "Criar";
        case MenuState::Listar: return "Listar";
        case MenuState::Comparar: return "Comparar";
        case MenuState::Config: return "Config";
        case MenuState::Sair: return "Sair";
    }
    return "";
}

} // namespace ui

