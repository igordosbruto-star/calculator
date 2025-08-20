#include "finance/SupplierRepo.h"
#include "core/paths.h"
#include "core/atomic_write.h"

#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

namespace finance {

using nlohmann::json;

// Conversões JSON para Supplier
void to_json(json& j, const Supplier& s) {
    j = json{{"id", s.id}, {"nome", s.nome}, {"contato", s.contato}};
}

void from_json(const json& j, Supplier& s) {
    j.at("id").get_to(s.id);
    j.at("nome").get_to(s.nome);
    if (j.contains("contato"))
        j.at("contato").get_to(s.contato);
    else
        s.contato.clear();
}

bool SupplierRepo::load(const std::string& path) {
    std::string p = ::Persist::dataPath(path);
    std::ifstream f(p);
    if (!f.is_open())
        return false;
    json j;
    try {
        f >> j;
    } catch (...) {
        return false;
    }
    schema_version = j.value("schema_version", 1);
    items.clear();
    if (j.contains("items"))
        j.at("items").get_to(items);
    return true;
}

bool SupplierRepo::save(const std::string& path) const {
    std::string p = ::Persist::dataPath(path);
    try {
        json j;
        j["schema_version"] = schema_version;
        j["items"] = items;
        return ::Persist::atomicWrite(std::filesystem::path(p), j.dump(2));
    } catch (...) {
        return false;
    }
}

} // namespace finance

