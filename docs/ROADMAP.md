# Roadmap

Esta calculadora evoluirá em etapas para oferecer mais flexibilidade e confiabilidade.

## Módulos planejados

- **Núcleo do aplicativo** (`Calculadora/app.cpp`)
  - Extrair a lógica de comparação e seleção de materiais em funções reutilizáveis.
  - Preparar o arquivo para futura divisão em múltiplos módulos.
- **Persistência de dados** (`Calculadora/persist.h`)
  - Centralizar leitura/escrita em formatos adicionais (ex.: XML).
  - Integrar validação de dados antes de salvar. ✅
  - Suporte a serialização de planos de corte (CorteDTO e PlanoCorteDTO). ✅
  - Funções para salvar PlanoCorteDTO em JSON e CSV. ✅
  - Função para carregar PlanoCorteDTO em JSON (`loadPlanoJSON`). ✅
  - Índice global de planos com atualização atômica (`updateIndex`). ✅
  - Persistência automática de planos gerados com `makeId`, `outPlanosDirFor`, `savePlanoJSON/CSV` e `updateIndex`. ✅
- **Interface de linha de comando** (`Calculadora/main.cpp`)
  - Adicionar opções de ajuda e parâmetros para cálculos automatizados. ✅
  - Melhorar mensagens de erro para entradas inválidas.
  - Suporte inicial a `--projeto` e registro dos comandos `abrir`, `listar` e `comparar`. ✅
- **Testes automatizados** (novo diretório `tests/`)
  - Criar casos de teste unitários para validar comparações e rotinas de persistência.
  - Integrar com execução contínua (CI) para evitar regressões.

## Novas capacidades de persistência

Com a evolução recente, a camada de persistência agora:

- Serializa planos de corte em JSON e CSV.
- Atualiza o índice global de forma atômica por meio de `updateIndex`.
- Salva automaticamente os planos gerados utilizando `makeId`, `outPlanosDirFor`, `savePlanoJSON/CSV` e `updateIndex`.
- Permite reabrir planos salvos com `loadPlanoJSON`.
- Expande `MaterialDTO` com campo `tipo` e migração para arquivos antigos.

## Melhorias propostas

- Documentação expandida em `docs/` para cobrir uso e desenvolvimento.
- Guia de contribuições explicando estilo e práticas de codificação.
- Centralizar constantes de formatação em `format.h` para reutilização.

