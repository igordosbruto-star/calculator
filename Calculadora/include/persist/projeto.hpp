#pragma once

#include <string>
#include <vector>
#include "domain/Projeto.h"

namespace Persist {

// Salva o projeto em JSON dentro de data/projetos/<id>/projeto.json
bool saveProjetoJSON(const Projeto& projeto);

// Carrega projeto pelo identificador
bool loadProjetoJSON(const std::string& id, Projeto& out);

// Lista ids de projetos existentes
std::vector<std::string> listarProjetos();

// Remove o projeto e sua entrada no índice
bool deleteProjeto(const std::string& id);

} // namespace Persist

