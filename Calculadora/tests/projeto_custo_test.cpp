#include "domain/Projeto.h"
#include <cassert>

// Testa cálculo detalhado de custos em Projeto
void test_projeto_custo() {
    Projeto prj;
    prj.id = "p1";
    prj.nome = "Projeto 1";

    ProjetoItemMaterial mat;
    mat.idMaterial = "mat1";
    mat.quantidade = 2.0;
    mat.custoUnitario = 10.0;
    mat.medidas.largura = 1.0;
    mat.medidas.comprimento = 1.0;
    assert(prj.adicionarMaterial(mat));

    ProjetoItemCorte ct;
    ct.idMaterial = "mat2";
    ct.largura = 0.5;
    ct.comprimento = 0.5;
    ct.quantidade = 1.0;
    ct.custoUnitario = 2.0;
    assert(prj.adicionarCorte(ct));

    CustoParams cfg;
    cfg.perdaPadrao = 0.0;
    cfg.fatorMaoObra = 0.1;
    cfg.overhead = 0.05;
    cfg.markup = 0.2;
    cfg.casasDecimais = 2;

    auto resumo = prj.calcularCustos(cfg);
    assert(resumo.itens.size() == 2);
    assert(resumo.itens[0].subtotal == 20.0);
    assert(resumo.itens[1].subtotal == 2.0);
    assert(resumo.total == 30.49);
}
