# Módulos

Visão geral dos principais componentes do DUKE.

## Núcleo do aplicativo
Responsável pela lógica de comparação e pelos cálculos de cortes e materiais.
Principais arquivos:
- `DUKE/app.cpp`
- `DUKE/include/calculadora.hpp`

## Persistência de dados
Centraliza leitura e escrita de informações em JSON ou CSV, além das
configurações de execução. Antes de salvar, cada `MaterialDTO` é
validado: o nome não pode ser vazio e nenhum valor numérico pode ser
negativo. Caso algum item seja inválido, a operação é abortada e um
aviso em vermelho é emitido.
Principais arquivos:
- `DUKE/persist.h`

## Interface de linha de comando
Ponto de entrada do programa e interação com o usuário via terminal.
Principais arquivos:
- `DUKE/main.cpp`

## Testes automatizados
Previsto para reunir casos de teste que validem comparações e rotinas de
persistência. Estrutura sugerida:
- `tests/` (a ser criado)
