# Revisões Planejadas

1. Separar a lógica do app em módulos
   - Motivação: Facilitar manutenção, testes e reutilização.
   - Arquivos impactados: `DUKE/app.cpp`, `DUKE/include/duke.hpp`, `DUKE/main.cpp`.

2. Validar dados antes de salvar
   - Motivação: Garantir integridade das informações e evitar erros ao persistir dados.
   - Arquivos impactados: `DUKE/app.cpp`, `DUKE/persist.h`, arquivos em `DUKE/data/`.

3. Adicionar opções de CLI
   - Motivação: Permitir que o usuário configure operações e parâmetros do DUKE.
   - Arquivos impactados: `DUKE/main.cpp`, `DUKE/app.cpp`.
