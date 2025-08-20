#include "production/ModeloProducao.h"

namespace production {

ModeloProducao::ModeloProducao(const std::string& id, const std::string& nome)
    : id_(id), nome_(nome) {}

void ModeloProducao::adicionarComponente(const Componente& comp) {
    componentes_.push_back(comp);
}

const std::vector<Componente>& ModeloProducao::componentes() const {
    return componentes_;
}

void ModeloProducao::definirVariavel(const std::string& chave, const std::string& valor) {
    variaveis_.emplace_back(chave, valor);
}

const std::string& ModeloProducao::variavel(const std::string& chave) const {
    for (const auto& kv : variaveis_) {
        if (kv.first == chave) {
            return kv.second;
        }
    }
    static const std::string empty;
    return empty;
}

} // namespace production
