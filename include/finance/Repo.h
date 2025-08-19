#pragma once

#include <string>
#include <vector>

#include "finance/Lancamento.h"
#include "finance/Filters.h"

namespace finance {

// Repositório de lançamentos financeiros
class FinanceRepo {
public:
    // Carrega lançamentos de um arquivo JSON
    bool load(const std::string& path = "data/financeiro/lancamentos.json");

    // Salva lançamentos em um arquivo JSON
    bool save(const std::string& path = "data/financeiro/lancamentos.json") const;

    // Gera próximo identificador "FIN-YYYY-MM-DD-XXXX"
    std::string nextId() const;

    // Adiciona um novo lançamento. Retorna false se inválido
    bool add(const Lancamento& l);

    // Remove lançamento pelo id. Retorna true se removido
    bool remove(const std::string& id);

    // Consulta lançamentos de acordo com filtros
    std::vector<Lancamento> query(const Filtro& f) const;

    // Soma valores dos lançamentos filtrados
    double sum(const Filtro& f) const;

private:
    int schema_version = 1;
    std::vector<Lancamento> items;
};

} // namespace finance

