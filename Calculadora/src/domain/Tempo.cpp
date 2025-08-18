#include "domain/Tempo.h"

using nlohmann::json;

namespace Tempo {

double tempoItem(const Operacao& op) {
    return op.tempoPorUnidade * static_cast<double>(op.quantidade);
}

double tempoProjeto(const std::vector<Operacao>& ops) {
    double total = 0.0;
    for (const auto& op : ops) {
        total += tempoItem(op);
    }
    return total;
}

std::string faseToString(Fase f) {
    switch (f) {
        case Fase::Preparo: return "preparo";
        case Fase::Producao: return "producao";
        case Fase::Finalizacao: return "finalizacao";
    }
    return "preparo";
}

Fase faseFromString(const std::string& s) {
    if (s == "producao") return Fase::Producao;
    if (s == "finalizacao") return Fase::Finalizacao;
    return Fase::Preparo;
}

} // namespace Tempo

void to_json(json& j, const Operacao& o) {
    j = json{{"fase", Tempo::faseToString(o.fase)},
             {"tempo_por_unidade", o.tempoPorUnidade},
             {"quantidade", o.quantidade}};
}

void from_json(const json& j, Operacao& o) {
    std::string faseStr;
    j.at("fase").get_to(faseStr);
    o.fase = Tempo::faseFromString(faseStr);
    j.at("tempo_por_unidade").get_to(o.tempoPorUnidade);
    j.at("quantidade").get_to(o.quantidade);
}

