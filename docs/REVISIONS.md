# Revisões Planejadas

1. Separar a lógica do app em módulos
   - Motivação: Facilitar manutenção, testes e reutilização.
   - Arquivos impactados: `Calculadora/app.cpp`, `Calculadora/include/calculadora.hpp`, `Calculadora/main.cpp`.

2. Validar dados antes de salvar
   - Motivação: Garantir integridade das informações e evitar erros ao persistir dados.
   - Arquivos impactados: `Calculadora/app.cpp`, `Calculadora/persist.h`, arquivos em `Calculadora/data/`.

3. Adicionar opções de CLI
   - Motivação: Permitir que o usuário configure operações e parâmetros da calculadora.
   - Arquivos impactados: `Calculadora/main.cpp`, `Calculadora/app.cpp`.
