#include "ApplicationCore.h"
#include <sstream>
#include <stdexcept>
#include "core/Debug.h"
#include "comparison.h"

namespace duke {

std::vector<MaterialDTO> ApplicationCore::criarMateriaisPadrao() const {
    return {
        {"Pinus 20cm", 17.00, 0.20, 3.00, "linear"},
        {"MDF 15mm", 180.00, 1.85, 2.75, "linear"}
    };
}

bool ApplicationCore::carregar(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
    int schemaVersion = 0;
    if (!::Persist::load("materiais.json", base, &schemaVersion) || base.empty()) {
        wr::p("DATA", "Base nao encontrada. Criando materiais padrao...", "Yellow");
        base = criarMateriaisPadrao();
        if (::Persist::save("materiais.json", base, 1)) {
            wr::p("DATA", "materiais.json criado.", "Green");
        } else {
            wr::p("DATA", "Falha ao criar materiais.json", "Red");
        }
    } else {
        std::ostringstream oss;
        oss << "materiais.json carregado (versao " << schemaVersion << ")";
        wr::p("DATA", oss.str(), "Green");
    }

    mats = core::reconstruirMateriais(base);
    if (mats.size() < 2) {
        wr::p("ERRO", "Precisam existir pelo menos 2 materiais para comparar.", "Red");
        return false;
    }
    return true;
}

std::vector<MaterialDTO> ApplicationCore::listarMateriais(const std::vector<MaterialDTO>& base) const {
    return base;
}

std::vector<comparison::MaterialComparado>
ApplicationCore::compararMateriais(const std::vector<Material>& mats,
                                   const std::vector<int>& ids) const {
    auto sel = comparison::selecionarMateriais(ids, mats);
    return comparison::compararMateriais(sel);
}

// ----- APIs do módulo de vendas -----
bool ApplicationCore::carregar() {
    // Carrega materiais reutilizando a função existente
    int schemaVersion = 0;
    if (!::Persist::load("materiais.json", base_, &schemaVersion) || base_.empty()) {
        wr::p("DATA", "Base nao encontrada. Criando materiais padrao...", "Yellow");
        base_ = criarMateriaisPadrao();
        ::Persist::save("materiais.json", base_, 1);
    }
    mats_ = core::reconstruirMateriais(base_);

    // Carrega clientes e pedidos (se inexistentes, mantém vetores vazios)
    ::Persist::loadJSONVec("clientes.json", clientes_, "clientes");
    ::Persist::loadJSONVec("pedidos.json", pedidos_, "pedidos");
    if (!pedidos_.empty()) {
        nextId_ = pedidos_.back().id + 1;
    }
    return true;
}

bool ApplicationCore::criarPedido(const std::string& cliente, const std::string& item, int quantidade) {
    Order o(nextId_++, cliente, item, quantidade);
    pedidos_.push_back(o);
    bool ok = ::Persist::saveJSONVec("pedidos.json", pedidos_, "pedidos");
    if (ok) {
        wr::p("SALES", "Pedido registrado", "Green");
    } else {
        wr::p("SALES", "Falha ao salvar pedido", "Red");
    }
    return ok;
}

std::vector<Customer> ApplicationCore::listarClientes() const { return clientes_; }

std::vector<Order> ApplicationCore::listarPedidos() const { return pedidos_; }

std::vector<MaterialDTO> ApplicationCore::listarEstoque() const { return base_; }

// ----- APIs do módulo financeiro -----
bool ApplicationCore::carregarFinanceiro() { return finRepo_.load(); }

std::string ApplicationCore::proximoIdLancamento() { return finRepo_.nextId(); }

bool ApplicationCore::adicionarLancamento(const finance::Lancamento& l) {
    if (!finRepo_.add(l)) return false;
    return finRepo_.save();
}

std::vector<finance::Lancamento> ApplicationCore::listarLancamentos(const finance::Filtro& f) const {
    return finRepo_.query(f);
}

double ApplicationCore::somarLancamentos(const finance::Filtro& f) const {
    return finRepo_.sum(f);
}

} // namespace duke

