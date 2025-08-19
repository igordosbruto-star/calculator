// ==========================================
// Arquivo: cli.cpp
// Descrição: Tratamento simples de argumentos
// ==========================================

#include "cli/args.h"
#include "core/Debug.h" // para logs coloridos
#include <string>
#include <sstream>
#include <charconv>
#include "finance/Serialize.h"
namespace duke {

CliOptions parseArgs(int argc, char* argv[]) {
    CliOptions opt; // guarda opções reconhecidas
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (opt.finCmd == FinCmd::None && a == "fin" && i + 1 < argc) {
            std::string sub = argv[++i];
            if (sub == "add") opt.finCmd = FinCmd::Add;
            else if (sub == "list") opt.finCmd = FinCmd::List;
            else if (sub == "sum") opt.finCmd = FinCmd::Sum;
            else opt.naoMapeados.push_back(sub);
        } else if (opt.finCmd != FinCmd::None) {
            if (a == "--help" || a == "-h") {
                opt.showHelp = true;
            } else if (a.rfind("--tipo", 0) == 0) {
                std::string valor;
                if (a == "--tipo" && i + 1 < argc) {
                    valor = argv[++i];
                } else if (a.find('=') != std::string::npos) {
                    valor = a.substr(a.find('=') + 1);
                }
                if (!valor.empty()) opt.finTipo = finance::tipo_from_string(valor);
            } else if (a.rfind("--subtipo", 0) == 0) {
                std::string valor;
                if (a == "--subtipo" && i + 1 < argc) {
                    valor = argv[++i];
                } else if (a.find('=') != std::string::npos) {
                    valor = a.substr(a.find('=') + 1);
                }
                opt.finSubtipo = valor;
            } else if (a.rfind("--valor", 0) == 0) {
                std::string valor;
                if (a == "--valor" && i + 1 < argc) {
                    valor = argv[++i];
                } else if (a.find('=') != std::string::npos) {
                    valor = a.substr(a.find('=') + 1);
                }
                if (!valor.empty()) {
                    double val{};
                    auto [ptr, ec] = std::from_chars(valor.data(),
                                                    valor.data() + valor.size(), val);
                    if (ec == std::errc() && ptr == valor.data() + valor.size()) {
                        opt.finValor = val;
                    } else {
                        wr::p("CLI", "Valor invalido '" + valor + "'", "Yellow");
                        opt.ok = false;
                    }
                }
            } else if (a.rfind("--data", 0) == 0) {
                std::string valor;
                if (a == "--data" && i + 1 < argc) {
                    valor = argv[++i];
                } else if (a.find('=') != std::string::npos) {
                    valor = a.substr(a.find('=') + 1);
                }
                opt.finData = valor;
            } else if (a.rfind("--desc", 0) == 0) {
                std::string valor;
                if (a == "--desc" && i + 1 < argc) {
                    valor = argv[++i];
                } else if (a.find('=') != std::string::npos) {
                    valor = a.substr(a.find('=') + 1);
                }
                opt.finDesc = valor;
            } else if (a == "--entrada") {
                opt.finEntrada = true;
            } else if (a == "--saida") {
                opt.finEntrada = false;
            } else if (a.rfind("--dt-ini", 0) == 0) {
                std::string valor;
                if (a == "--dt-ini" && i + 1 < argc) {
                    valor = argv[++i];
                } else if (a.find('=') != std::string::npos) {
                    valor = a.substr(a.find('=') + 1);
                }
                opt.finDtIni = valor;
            } else if (a.rfind("--dt-fim", 0) == 0) {
                std::string valor;
                if (a == "--dt-fim" && i + 1 < argc) {
                    valor = argv[++i];
                } else if (a.find('=') != std::string::npos) {
                    valor = a.substr(a.find('=') + 1);
                }
                opt.finDtFim = valor;
            } else {
                opt.naoMapeados.push_back(a);
            }
        } else if (a == "--help" || a == "-h") {
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
