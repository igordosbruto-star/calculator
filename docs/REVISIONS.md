# Revisões Planejadas

1. Separar a lógica do app em módulos
   - Motivação: Facilitar manutenção, testes e reutilização.
    - Arquivos impactados: `src/duke/ApplicationCore.cpp`, `include/duke/duke.hpp`, `src/duke/main.cpp`.

2. Validar dados antes de salvar
   - Motivação: Garantir integridade das informações e evitar erros ao persistir dados.
    - Arquivos impactados: `src/duke/ApplicationCore.cpp`, `include/duke/persist.hpp`.

3. Adicionar opções de CLI
   - Motivação: Permitir que o usuário configure operações e parâmetros do DUKE.
    - Arquivos impactados: `src/duke/main.cpp`, `src/duke/cli/app.cpp`.
