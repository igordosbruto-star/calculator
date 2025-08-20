# Módulos

Visão geral dos principais componentes do DUKE.

## Núcleo do aplicativo
Responsável pela lógica de comparação e pelos cálculos de cortes e materiais.
 Principais arquivos:
 - `src/duke/ApplicationCore.cpp`
 - `include/duke/duke.hpp`

## Persistência de dados
Centraliza leitura e escrita de informações em JSON, CSV ou XML,
além das configurações de execução. Antes de salvar, cada `MaterialDTO`
é validado: o nome não pode ser vazio e nenhum valor numérico pode ser
negativo. Caso algum item seja inválido, a operação é abortada e um
aviso em vermelho é emitido. A API `Persist::save`/`load` seleciona o
formato de acordo com a extensão do arquivo.
 Principais arquivos:
 - `include/duke/persist.hpp`

## Interface de linha de comando
Ponto de entrada do programa e interação com o usuário via terminal.
 Principais arquivos:
 - `src/duke/main.cpp`

## Testes automatizados
Previsto para reunir casos de teste que validem comparações e rotinas de
persistência. Estrutura sugerida:
- `tests/` (a ser criado)
