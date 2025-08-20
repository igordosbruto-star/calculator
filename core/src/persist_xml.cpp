#include "core/persist.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace Persist {

bool saveXML(const std::string& path, const std::vector<MaterialDTO>& items,
             const std::string& baseDir) {
    for (const auto& m : items) {
        auto err = validar(m);
        if (err.code != duke::ErrorCode::Ok) {
            wr::p("PERSIST", duke::errorMessage(err.code, err.field) + ": " + m.nome, "Red");
            return false;
        }
    }
    XMLDocument doc;
    auto* decl = doc.NewDeclaration();
    doc.InsertFirstChild(decl);
    auto* root = doc.NewElement("materiais");
    root->SetAttribute("schema_version", 1);
    for (const auto& m : items) {
        auto* el = doc.NewElement("material");
        el->SetAttribute("nome", m.nome.c_str());
        el->SetAttribute("tipo", m.tipo.c_str());
        el->SetAttribute("valor", m.valor);
        el->SetAttribute("largura", m.largura);
        el->SetAttribute("comprimento", m.comprimento);
        root->InsertEndChild(el);
    }
    doc.InsertEndChild(root);
    const std::string p = dataPath(path, baseDir);
    if (doc.SaveFile(p.c_str()) != XML_SUCCESS) {
        wr::p("PERSIST", p + " write fail", "Red");
        return false;
    }
    return true;
}

bool loadXML(const std::string& path, std::vector<MaterialDTO>& out,
             const std::string& baseDir) {
    const std::string p = dataPath(path, baseDir);
    XMLDocument doc;
    if (doc.LoadFile(p.c_str()) != XML_SUCCESS) {
        wr::p("PERSIST", p + " open fail", "Red");
        return false;
    }
    auto* root = doc.FirstChildElement("materiais");
    if (!root) {
        wr::p("PERSIST", p + " missing 'materiais'", "Red");
        return false;
    }
    out.clear();
    int invalid = 0;
    for (auto* el = root->FirstChildElement("material"); el; el = el->NextSiblingElement("material")) {
        MaterialDTO m;
        const char* nome = el->Attribute("nome");
        const char* tipo = el->Attribute("tipo");
        if (!nome) { ++invalid; continue; }
        m.nome = nome;
        m.tipo = tipo ? tipo : "linear";
        el->QueryDoubleAttribute("valor", &m.valor);
        el->QueryDoubleAttribute("largura", &m.largura);
        el->QueryDoubleAttribute("comprimento", &m.comprimento);
        auto err = validar(m);
        if (err.code != duke::ErrorCode::Ok) { ++invalid; continue; }
        out.push_back(std::move(m));
    }
    if (out.empty() && invalid > 0) return false;
    return !out.empty();
}

} // namespace Persist

