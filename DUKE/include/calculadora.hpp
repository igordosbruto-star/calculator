#pragma once

#include "Material.h"

namespace calculadora {

/**
 * @brief Calcula o valor de um corte retangular.
 *
 * O valor é obtido multiplicando a área do corte pelo preço por metro
 * quadrado do material.
 *
 * Exemplo de uso:
 * @code
 * Material m{"Madeira", 100.0, 2.0, 2.0};
 * double valor = calcularValorCorte(m, 1.0, 0.5);
 * @endcode
 *
 * @param material Material base onde será feito o corte.
 * @param largura Largura do corte em metros.
 * @param comprimento Comprimento do corte em metros.
 * @return Valor total em reais do corte solicitado.
 */
double calcularValorCorte(const Material& material,
                          double largura,
                          double comprimento);

} // namespace calculadora

