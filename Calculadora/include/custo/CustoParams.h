#pragma once

// Parâmetros globais para cálculo de custo
struct CustoParams {
    double perdaPadrao = 0.0;   // percentual de perda aplicado a todos os itens
    double fatorMaoObra = 0.0;  // fator multiplicador de mão de obra
    double overhead = 0.0;      // percentual de overhead administrativo
    double markup = 0.0;        // percentual de markup/lucro
    int casasDecimais = 2;      // casas decimais do resultado
};

// Exemplo de uso:
// CustoParams cfg{0.05, 0.1, 0.05, 0.2, 2};
