#include "persist/projeto.hpp"
#include "persist.h"

#include <filesystem>
#include <fstream>

using nlohmann::json;
namespace fs = std::filesystem;

// Converte Projeto para JSON
static json projetoToJson(const Projeto& p) {
    json j;
    j["id"] = p.id;
    j["nome"] = p.nome;
    j["materiais"] = json::array();
    for (const auto& m : p.materiais) {
        j["materiais"].push_back({
            {"id_material", m.idMaterial},
            {"quantidade", m.quantidade},
            {"custo_unitario", m.custoUnitario},
            {"medidas", {
                {"largura", m.medidas.largura},
                {"altura", m.medidas.altura},
                {"profundidade", m.medidas.profundidade},
                {"comprimento", m.medidas.comprimento}
            }}
        });
    }
    j["cortes"] = json::array();
    for (const auto& c : p.cortes) {
        j["cortes"].push_back({
            {"id_material", c.idMaterial},
            {"largura", c.largura},
            {"comprimento", c.comprimento},
            {"quantidade", c.quantidade},
            {"custo_unitario", c.custoUnitario}
        });
    }
    return j;
}

static void jsonToProjeto(const json& j, Projeto& p) {
    j.at("id").get_to(p.id);
    if (j.contains("nome")) j.at("nome").get_to(p.nome);
    p.materiais.clear();
    for (const auto& jm : j.value("materiais", json::array())) {
        ProjetoItemMaterial m;
        jm.at("id_material").get_to(m.idMaterial);
        jm.at("quantidade").get_to(m.quantidade);
        jm.at("custo_unitario").get_to(m.custoUnitario);
        auto med = jm.at("medidas");
        med.at("largura").get_to(m.medidas.largura);
        med.at("altura").get_to(m.medidas.altura);
        med.at("profundidade").get_to(m.medidas.profundidade);
        med.at("comprimento").get_to(m.medidas.comprimento);
        p.materiais.push_back(m);
    }
    p.cortes.clear();
    for (const auto& jc : j.value("cortes", json::array())) {
        ProjetoItemCorte c;
        jc.at("id_material").get_to(c.idMaterial);
        jc.at("largura").get_to(c.largura);
        jc.at("comprimento").get_to(c.comprimento);
        jc.at("quantidade").get_to(c.quantidade);
        jc.at("custo_unitario").get_to(c.custoUnitario);
        p.cortes.push_back(c);
    }
}

static fs::path projetoPath(const std::string& id) {
    return fs::path(Persist::dataPath("projetos/" + id + "/projeto.json"));
}

static fs::path indexPath() {
    return fs::path(Persist::dataPath("projetos/index.json"));
}

bool Persist::saveProjetoJSON(const Projeto& projeto) {
    try {
        json j = projetoToJson(projeto);
        if (!Persist::atomicWrite(projetoPath(projeto.id), j.dump(2))) return false;

        json idx;
        if (fs::exists(indexPath())) {
            std::ifstream f(indexPath());
            if (f) { try { f >> idx; } catch (...) { idx = json{}; } }
        }
        if (!idx.is_object()) idx = json::object();
        if (!idx.contains("projetos") || !idx["projetos"].is_array())
            idx["projetos"] = json::array();
        bool found = false;
        for (const auto& idj : idx["projetos"]) {
            if (idj.is_string() && idj.get<std::string>() == projeto.id) {
                found = true; break;
            }
        }
        if (!found) idx["projetos"].push_back(projeto.id);
        return Persist::atomicWrite(indexPath(), idx.dump(2));
    } catch (const std::exception& e) {
        wr::p("PERSIST", std::string("saveProjetoJSON exception: ") + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", "saveProjetoJSON unknown exception", "Red");
        return false;
    }
}

bool Persist::loadProjetoJSON(const std::string& id, Projeto& out) {
    try {
        std::ifstream f(projetoPath(id));
        if (!f) {
            wr::p("PERSIST", "loadProjetoJSON open fail", "Red");
            return false;
        }
        json j; f >> j;
        jsonToProjeto(j, out);
        return true;
    } catch (const std::exception& e) {
        wr::p("PERSIST", std::string("loadProjetoJSON exception: ") + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", "loadProjetoJSON unknown exception", "Red");
        return false;
    }
}

std::vector<std::string> Persist::listarProjetos() {
    std::vector<std::string> ids;
    try {
        if (!fs::exists(indexPath())) return ids;
        std::ifstream f(indexPath());
        if (!f) return ids;
        json j; f >> j;
        for (const auto& idj : j.value("projetos", json::array())) {
            if (idj.is_string()) ids.push_back(idj.get<std::string>());
        }
    } catch (...) {
        // retorna lista vazia em caso de erro
    }
    return ids;
}

bool Persist::deleteProjeto(const std::string& id) {
    bool ok = true;
    try {
        fs::remove_all(fs::path(Persist::dataPath("projetos/" + id)));
        json idx;
        if (fs::exists(indexPath())) {
            std::ifstream f(indexPath());
            if (f) { try { f >> idx; } catch (...) { idx = json{}; } }
        }
        if (idx.is_object() && idx.contains("projetos")) {
            auto& arr = idx["projetos"];
            if (arr.is_array()) {
                arr.erase(std::remove_if(arr.begin(), arr.end(), [&](const json& v){return v.is_string() && v.get<std::string>() == id;}), arr.end());
                ok = Persist::atomicWrite(indexPath(), idx.dump(2));
            }
        }
    } catch (const std::exception& e) {
        wr::p("PERSIST", std::string("deleteProjeto exception: ") + e.what(), "Red");
        ok = false;
    } catch (...) {
        wr::p("PERSIST", "deleteProjeto unknown exception", "Red");
        ok = false;
    }
    return ok;
}

