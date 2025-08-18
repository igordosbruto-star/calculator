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

```bash
./app --projeto caminho/do/projeto.json
```
Carrega o projeto informado para uso na sessão (em desenvolvimento).

As opções podem ser combinadas conforme necessário.

## Subcomandos

Além das opções, é possível utilizar subcomandos para manipular dados persistidos:

```bash
./app criar
```
Cria um novo recurso (em desenvolvimento).

```bash
./app listar --tipo=linear --ordem=preco:asc
```
Lista materiais filtrando por tipo e ordenação.

```bash
./app comparar --ids=1,2,3
```
Compara materiais pelos IDs informados.

## Configuração do VS Code

Execute `start.bat` para gerar os arquivos de configuração do VS Code.
Antes da criação desses arquivos, o script verifica se `g++`, `make` e `gdb`
estão instalados. Caso alguma dependência não seja encontrada, a execução é
interrompida com uma mensagem de erro.
