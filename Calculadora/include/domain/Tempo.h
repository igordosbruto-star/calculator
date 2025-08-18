#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
namespace calculadora {

// Fases básicas de uma operação
enum class Fase {
    Preparo,
    Producao,
    Finalizacao
};

// Descreve uma operação com tempo por unidade
struct Operacao {
    Fase fase = Fase::Preparo;  // fase da operação
    double tempoPorUnidade = 0.0; // em horas
    int quantidade = 0;          // número de unidades
};

namespace Tempo {

// Calcula tempo total de uma operação (tempoPorUnidade * quantidade)
double tempoItem(const Operacao& op);

// Soma tempos de todas as operações do projeto
double tempoProjeto(const std::vector<Operacao>& ops);

// Converte Fase para string
std::string faseToString(Fase f);

// Converte string para Fase (default Preparo)
Fase faseFromString(const std::string& s);

} // namespace Tempo

// Serialização para JSON de Operacao
void to_json(nlohmann::json& j, const Operacao& o);
void from_json(const nlohmann::json& j, Operacao& o);

} // namespace calculadora
