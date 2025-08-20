# Roadmap

O DUKE evoluirá em etapas para oferecer mais flexibilidade e confiabilidade.

## v1.0

- [ ] [P1] Separar a lógica do app em módulos (`src/duke/ApplicationCore.cpp`, `include/duke/duke.hpp`, `src/duke/main.cpp`).
- [ ] [P1] Extrair a lógica de comparação e seleção de materiais em funções reutilizáveis.
- [ ] [P1] Centralizar leitura/escrita em formatos adicionais (ex.: XML).
- [ ] [P2] Melhorar mensagens de erro para entradas inválidas.
- [ ] [P1] Criar casos de teste unitários para validar comparações e rotinas de persistência.
- [ ] [P2] Integrar com execução contínua (CI) para evitar regressões.

## v1.1

- [ ] [P2] Documentação expandida em `docs/` para cobrir uso e desenvolvimento.
- [ ] [P3] Guia de contribuições explicando estilo e práticas de codificação.
- [ ] [P2] Centralizar constantes de formatação em `format.h` para reutilização.

## v1.2

- [ ] [P2] Implementar módulo Designer (canvas de montagem, associação de materiais, histórico).

## Concluído

### Persistência de dados

- [x] [P1] Integrar validação de dados antes de salvar. ([d80557b](https://github.com/igordosbruto/calculator/commit/d80557b))
- [x] [P1] Suporte a serialização de planos de corte (CorteDTO e PlanoCorteDTO). ([cde9655](https://github.com/igordosbruto/calculator/commit/cde9655))
- [x] [P1] Funções para salvar `PlanoCorteDTO` em JSON e CSV. ([cde9655](https://github.com/igordosbruto/calculator/commit/cde9655))
- [x] [P1] Função para carregar `PlanoCorteDTO` em JSON (`loadPlanoJSON`). ([3b6680c](https://github.com/igordosbruto/calculator/commit/3b6680c))
- [x] [P1] Índice global de planos com atualização atômica (`updateIndex`). ([cde9655](https://github.com/igordosbruto/calculator/commit/cde9655))
- [x] [P1] Persistência automática de planos gerados com `makeId`, `outPlanosDirFor`, `savePlanoJSON/CSV` e `updateIndex`. ([cde9655](https://github.com/igordosbruto/calculator/commit/cde9655))
- [x] [P1] Tratamento de falhas na gravação de planos, abortando o fluxo e avisando o usuário. ([cde9655](https://github.com/igordosbruto/calculator/commit/cde9655))

### Interface de linha de comando

- [x] [P2] Adicionar opções de ajuda e parâmetros para cálculos automatizados. ([f8b4824](https://github.com/igordosbruto/calculator/commit/f8b4824))
- [x] [P2] Suporte inicial a `--projeto` e registro dos comandos `abrir`, `listar` e `comparar`. ([f173bed](https://github.com/igordosbruto/calculator/commit/f173bed))
- [x] [P2] Modularizar CLI em `parser`, `commands` e utilitários. ([adc0100](https://github.com/igordosbruto/calculator/commit/adc0100))

### Interface gráfica

- [x] [P3] Janela principal com botão para selecionar material. ([ab3505f](https://github.com/igordosbruto/calculator/commit/ab3505f))

### Financeiro

- [x] [P2] CLI para registrar, listar e somar lançamentos com filtros. ([0c69d4d](https://github.com/igordosbruto/calculator/commit/0c69d4d))
- [x] [P2] Relatório mensal com `fin report mes --ano=<AAAA> --mes=<MM>` exportando CSV. ([9359cce](https://github.com/igordosbruto/calculator/commit/9359cce))
- [x] [P2] Validações de lançamentos (valor >0, data ISO, tipo obrigatório). ([a9f87c8](https://github.com/igordosbruto/calculator/commit/a9f87c8))

### Domínio de Materiais

- [x] [P2] Implementadas classes específicas para materiais `unitário`, `linear` e `cúbico`. ([0449975](https://github.com/igordosbruto/calculator/commit/0449975))
- [x] [P2] Adicionada `MaterialFactory::fromDTO` para instanciar o tipo correto a partir de `MaterialDTO`. ([a089912](https://github.com/igordosbruto/calculator/commit/a089912))
- [x] [P2] Expande `MaterialDTO` com campo `tipo` e migração para arquivos antigos.

### Outros

- [x] [P3] API pública simplificada via `duke.hpp`. ([7892e10](https://github.com/igordosbruto/calculator/commit/7892e10))


