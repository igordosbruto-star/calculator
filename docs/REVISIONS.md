# Revisões Planejadas

1. Separar a lógica do app em módulos
   - Motivação: Facilitar manutenção, testes e reutilização.
   - Arquivos impactados: `third_party/DUKE/app.cpp`, `third_party/DUKE/include/duke.hpp`, `third_party/DUKE/main.cpp`.

2. Validar dados antes de salvar
   - Motivação: Garantir integridade das informações e evitar erros ao persistir dados.
   - Arquivos impactados: `third_party/DUKE/app.cpp`, `third_party/DUKE/persist.h`, arquivos em `third_party/DUKE/data/`.

3. Adicionar opções de CLI
   - Motivação: Permitir que o usuário configure operações e parâmetros do DUKE.
   - Arquivos impactados: `third_party/DUKE/main.cpp`, `third_party/DUKE/app.cpp`.
