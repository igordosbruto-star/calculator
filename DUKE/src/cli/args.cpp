// ==========================================
// Arquivo: cli.cpp
// Descrição: Tratamento simples de argumentos
// ==========================================

#include "cli/args.h"
#include "core/Debug.h" // para logs coloridos
#include <string>
#include <sstream>
#include <charconv>
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
                            // avisa sobre ID inválido
                            wr::p("CLI", "ID invalido '" + item + "' ignorado", "Yellow");
                        }
                    }
                }
            }
        } else if (opt.comando == Comando::Nenhum && a == "criar") {
            opt.comando = Comando::Criar;
        } else if (opt.comando == Comando::Nenhum && a == "listar") {
            opt.comando = Comando::Listar;
        } else if (opt.comando == Comando::Nenhum && a == "comparar") {
            opt.comando = Comando::Comparar;
        } else {
            // argumento desconhecido
            opt.naoMapeados.push_back(a);
        }
    }
    if (!opt.naoMapeados.empty()) {
        for (const auto& tok : opt.naoMapeados) {
            wr::p("CLI", "Argumento desconhecido: " + tok, "Yellow");
        }
        opt.ok = false; // sinaliza problema para o chamador
    }
    return opt;
}

} // namespace duke
