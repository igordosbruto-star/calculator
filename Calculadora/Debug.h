// ==========================================
// Arquivo: Debug.h
// Autor: Wesley
// Título: Sistema de Logs e Depuração
// Descrição:
//     Utilitário para imprimir mensagens de depuração com cores,
//     nome de módulos e categorização de mensagens em tempo de execução.
// ==========================================
#pragma once

// Bibliotecas de sistema
#include <iostream>     // Entrada e saída (ex: cout)
#include <string>       // Manipulação de texto
#include <map>          // Mapa ordenado chave-valor

namespace wr {

    inline const std::map<std::string, std::string> colorMap = {
        {"Black", "\033[30m"},
        {"Red", "\033[31m"},
        {"Green", "\033[32m"},
        {"Yellow", "\033[33m"},
        {"Blue", "\033[34m"},
        {"Magenta", "\033[35m"},
        {"Cyan", "\033[36m"},
        {"White", "\033[37m"},
        {"Reset", "\033[0m"}
    };

    inline void p(const std::string& mensagem) {

        // Caso a mensagem for um numero
        
        // printa no terminal a mensagem
        std::cout << "[DEBUG] " << mensagem << colorMap.at("Reset") << "\n";
    }

    inline void p(const std::string& modulo, const std::string& mensagem) {
        std::cout << "[" << modulo << "] " << mensagem << colorMap.at("Reset") << "\n";
    }

    inline void p(const std::string& modulo, const std::string& mensagem, const std::string& cor) {
        auto it = colorMap.find(cor);
        std::string corANSI = (it != colorMap.end()) ? it->second : colorMap.at("White");

        std::cout << corANSI << "[" << modulo << "]" << colorMap.at("Reset") << " " << mensagem << "\n";
    }

}
