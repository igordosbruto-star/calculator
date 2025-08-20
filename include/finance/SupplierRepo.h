#pragma once

#include <vector>
#include <string>

#include "finance/Supplier.h"

namespace finance {

// Repositório simples de fornecedores
class SupplierRepo {
public:
    bool load(const std::string& path = "data/financeiro/fornecedores.json");
    bool save(const std::string& path = "data/financeiro/fornecedores.json") const;
    const std::vector<Supplier>& all() const { return items; }
    void add(const Supplier& s) { items.push_back(s); }

private:
    int schema_version = 1;
    std::vector<Supplier> items;
};

} // namespace finance

