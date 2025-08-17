# Uso via CLI

A calculadora pode ser executada com as seguintes opções:

```bash
./app --help
```
Exibe instruções de uso e encerra.

```bash
./app --auto
```
Inicia em modo automático, escolhendo o material mais barato.

As opções podem ser combinadas conforme necessário.

## Configuração do VS Code

Execute `start.bat` para gerar os arquivos de configuração do VS Code.
Antes da criação desses arquivos, o script verifica se `g++`, `make` e `gdb`
estão instalados. Caso alguma dependência não seja encontrada, a execução é
interrompida com uma mensagem de erro.
