#include "plano_corte.h"
namespace duke {

// Serializa um CorteDTO para JSON
void to_json(json& j, const CorteDTO& c) {
    j = json{
        {"nome", c.nome},
        {"largura_m", c.largura_m},
        {"comprimento_m", c.comprimento_m},
        {"porm2", c.porm2},
        {"area_m2", c.area_m2},
        {"valor", c.valor},
        {"rot90", c.rot90}
    };
}

// Constrói um CorteDTO a partir de JSON
void from_json(const json& j, CorteDTO& c) {
    j.at("nome").get_to(c.nome);
    j.at("largura_m").get_to(c.largura_m);
    j.at("comprimento_m").get_to(c.comprimento_m);
    j.at("porm2").get_to(c.porm2);
    j.at("area_m2").get_to(c.area_m2);
    j.at("valor").get_to(c.valor);
    if (j.contains("rot90")) j.at("rot90").get_to(c.rot90);
}

// Serializa um PlanoCorteDTO para JSON
void to_json(json& j, const PlanoCorteDTO& p) {
    j = json{
        {"id", p.id},
        {"projeto", p.projeto},
        {"gerado_em", p.gerado_em},
        {"algoritmo", p.algoritmo},
        {"porm2_usado", p.porm2_usado},
        {"cortes", p.cortes},
        {"total_area_m2", p.total_area_m2},
        {"total_valor", p.total_valor}
    };
}

// Constrói um PlanoCorteDTO a partir de JSON
void from_json(const json& j, PlanoCorteDTO& p) {
    j.at("id").get_to(p.id);
    if (j.contains("projeto")) j.at("projeto").get_to(p.projeto);
    if (j.contains("gerado_em")) j.at("gerado_em").get_to(p.gerado_em);
    if (j.contains("algoritmo")) j.at("algoritmo").get_to(p.algoritmo);
    if (j.contains("porm2_usado")) j.at("porm2_usado").get_to(p.porm2_usado);
    if (j.contains("cortes")) j.at("cortes").get_to(p.cortes);
    if (j.contains("total_area_m2")) j.at("total_area_m2").get_to(p.total_area_m2);
    if (j.contains("total_valor")) j.at("total_valor").get_to(p.total_valor);
}

} // namespace duke
