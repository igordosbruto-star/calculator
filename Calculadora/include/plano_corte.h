#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using nlohmann::json;

// Representa um corte individual para persistência
struct CorteDTO {
    std::string nome;             // etiqueta do corte
    double largura_m = 0.0;       // largura em metros
    double comprimento_m = 0.0;   // comprimento em metros
    double porm2 = 0.0;           // preço por metro quadrado
    double area_m2 = 0.0;         // área resultante em m²
    double valor = 0.0;           // valor calculado (area_m2 * porm2)
    bool rot90 = false;           // indica rotação de 90°
};

// Agrupa os cortes realizados em uma execução
struct PlanoCorteDTO {
    std::string id;               // identificador único do plano
    std::string projeto;          // nome opcional do projeto
    std::string gerado_em;        // data/hora em ISO-8601
    std::string algoritmo;        // algoritmo utilizado
    double porm2_usado = 0.0;     // preço/m² aplicado
    std::vector<CorteDTO> cortes; // lista de cortes
    double total_area_m2 = 0.0;   // soma das áreas
    double total_valor = 0.0;     // soma dos valores
};

// Serialização JSON
void to_json(json& j, const CorteDTO& c);
void from_json(const json& j, CorteDTO& c);

void to_json(json& j, const PlanoCorteDTO& p);
void from_json(const json& j, PlanoCorteDTO& p);

