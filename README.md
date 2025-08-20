# ERP DUKE

ERP DUKE é um sistema ERP modular voltado para o planejamento de cortes de materiais e gestão de projetos.

## Requisitos

O sistema depende da toolkit [Qt 6](https://www.qt.io/qt-6).
Instale as bibliotecas de desenvolvimento e garanta que `pkg-config`
as encontre antes de compilar.

## Compilação

O projeto é dividido em módulos compilados separadamente.

### Script de compilação

Para compilar todos os módulos de uma só vez, utilize o script `build.sh`:

```sh
./build.sh
```

Ele executa `make` no núcleo `core`, compila a interface gráfica e a CLI do módulo `src/duke` e roda os testes.

### Núcleo `core`

```sh
cd core
make
```

### Módulo principal `DUKE`

```sh
cd src/duke
make
# opcional: gerar CLI
make cli
# executar CLI
./app
```

### Interface gráfica

Para compilar e executar a interface gráfica:

```sh
cd src/duke
make gui        # gera app_gui
./app_gui       # executa
```

Certifique-se de que o Qt 6 esteja instalado e que `pkg-config` consiga encontrá-lo.

## Documentação

A documentação detalhada está disponível na pasta [`docs/`](docs/):

- [Visão geral de uso](docs/USAGE.md)
- [Descrição dos módulos](docs/MODULES.md)
- [Roadmap](docs/ROADMAP.md)
- [Changelog](docs/CHANGELOG.md)

## Módulos

Os principais módulos atuais do ERP são:

- **core** – biblioteca compartilhada com tipos e utilitários básicos.
- **DUKE** – motor de cálculo e interface de linha de comando.
- **Financeiro** – funcionalidades relacionadas a custos e fluxo financeiro.

## Roadmap

O desenvolvimento do DUKE segue um roteiro público. Entre os próximos passos estão a modularização adicional do núcleo, aprimoramentos na persistência de dados, evolução da CLI e inclusão de testes automatizados.

Para detalhes completos consulte o arquivo [docs/ROADMAP.md](docs/ROADMAP.md).

