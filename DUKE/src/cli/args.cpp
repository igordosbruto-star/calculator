// ==========================================
// Arquivo: cli.cpp
// Descrição: Tratamento simples de argumentos
// ==========================================

#include "cli/args.h"
#include <string>
#include <sstream>
#include <charconv>
#include <iostream>
namespace duke {

CliOptions parseArgs(int argc, char* argv[]) {
    CliOptions opt; // guarda opções reconhecidas
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--help" || a == "-h") {
            opt.showHelp = true;
        } else if (a == "--auto") {
            opt.autoMode = true;
        } else if (a == "--projeto" && i + 1 < argc) {
            // consome próximo argumento como caminho do projeto
            opt.projeto = argv[++i];
        } else if (a.rfind("--tipo", 0) == 0) {
            // aceita --tipo=valor ou --tipo valor
            std::string valor;
            if (a == "--tipo" && i + 1 < argc) {
                valor = argv[++i];
            } else if (a.find('=') != std::string::npos) {
                valor = a.substr(a.find('=') + 1);
            }
            if (!valor.empty()) opt.tipo = valor;
        } else if (a.rfind("--ordem", 0) == 0) {
            // aceita --ordem=campo:direcao ou --ordem valor
            std::string valor;
            if (a == "--ordem" && i + 1 < argc) {
                valor = argv[++i];
            } else if (a.find('=') != std::string::npos) {
                valor = a.substr(a.find('=') + 1);
            }
            if (!valor.empty()) opt.ordem = valor;
        } else if (a.rfind("--ids", 0) == 0) {
            // aceita lista separada por vírgula
            std::string valor;
            if (a == "--ids" && i + 1 < argc) {
                valor = argv[++i];
            } else if (a.find('=') != std::string::npos) {
                valor = a.substr(a.find('=') + 1);
            }
            if (!valor.empty()) {
                std::stringstream ss(valor);
                std::string item;
                while (std::getline(ss, item, ',')) {
                    if (!item.empty()) {
                        int id{};
                        auto [ptr, ec] = std::from_chars(item.data(),
                                                      item.data() + item.size(), id);
                        if (ec == std::errc() && ptr == item.data() + item.size()) {
                            opt.ids.push_back(id);
                        } else {
                            std::cerr << "Aviso: ID invalido '" << item
                                      << "' ignorado\n";
                        }
                    }
                }
            }
        } else if (opt.comando == Comando::Nenhum) {
            // registra comando principal
            if (a == "criar") {
                opt.comando = Comando::Criar;
            } else if (a == "listar") {
                opt.comando = Comando::Listar;
            } else if (a == "comparar") {
                opt.comando = Comando::Comparar;
            }
        }
    }
    return opt;
}

} // namespace duke
