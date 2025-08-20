#include "duke/domain/Projeto.h"
#include "duke/persist/projeto.hpp"
#include <cassert>
#include <filesystem>

void test_projeto() {
    Projeto prj;
    prj.id = "proj_teste";
    prj.nome = "Projeto Teste";

    // Material válido
    ProjetoItemMaterial mat;
    mat.idMaterial = "mat1";
    mat.quantidade = 2;
    mat.custoUnitario = 5.0;
    mat.medidas.largura = 1.0;
    mat.medidas.comprimento = 1.0;
    assert(prj.adicionarMaterial(mat));

    // Material inválido (id vazio)
    ProjetoItemMaterial inval;
    inval.quantidade = 1;
    inval.medidas.largura = 1.0;
    inval.medidas.comprimento = 1.0;
    assert(!prj.adicionarMaterial(inval));

    // Material com dimensões zeradas (válido para materiais unitários)
    ProjetoItemMaterial matZero;
    matZero.idMaterial = "mat_unit";
    matZero.quantidade = 1;
    matZero.custoUnitario = 3.0;
    // Medidas permanecem em 0.0
    assert(prj.adicionarMaterial(matZero));

    // Corte válido
    ProjetoItemCorte ct;
    ct.idMaterial = "mat1";
    ct.largura = 0.5;
    ct.comprimento = 0.5;
    ct.quantidade = 1;
    ct.custoUnitario = 1.0;
    assert(prj.adicionarCorte(ct));

    // Operação válida
    Operacao op{Fase::Producao, 1.0, 1};
    assert(prj.adicionarOperacao(op));

    // Corte inválido (medida <=0)
    ProjetoItemCorte ctInv;
    ctInv.idMaterial = "mat1";
    ctInv.largura = 0.0;
    ctInv.comprimento = 1.0;
    ctInv.quantidade = 1;
    assert(!prj.adicionarCorte(ctInv));

    // Resumo de custo inclui materiais unitários com medidas zeradas
    assert(prj.resumoCusto() == 2*5.0 + 1*1.0 + 1*3.0);

    // Remoção
    assert(prj.removerItem("mat1"));
    assert(prj.removerItem("mat_unit"));
    assert(prj.materiais.empty());
    assert(prj.cortes.empty());

    // Testes de persistência
    prj.adicionarMaterial(mat);
    prj.adicionarCorte(ct);
    prj.operacoes.clear();
    prj.adicionarOperacao(op);
    assert(Persist::saveProjetoJSON(prj));

    Projeto lido;
    assert(Persist::loadProjetoJSON(prj.id, lido));
    assert(lido.materiais.size() == 1);
    assert(lido.cortes.size() == 1);
    assert(lido.operacoes.size() == 1);

    auto ids = Persist::listarProjetos();
    bool encontrado = false;
    for (const auto& id : ids) if (id == prj.id) encontrado = true;
    assert(encontrado);

    assert(Persist::deleteProjeto(prj.id));
    ids = Persist::listarProjetos();
    encontrado = false;
    for (const auto& id : ids) if (id == prj.id) encontrado = true;
    assert(!encontrado);
}

