#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "finance/Lancamento.h"
#include "finance/Tipos.h"

namespace finance {

using nlohmann::json;

std::string to_string(Tipo t);
Tipo tipo_from_string(const std::string& s);

void to_json(json& j, const Lancamento& l);
void from_json(const json& j, Lancamento& l);

} // namespace finance

