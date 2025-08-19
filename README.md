# ERP DUKE

ERP DUKE é um sistema ERP modular voltado para o planejamento de cortes de materiais e gestão de projetos.

## Compilação

O projeto é dividido em módulos compilados separadamente.

### Núcleo `core`

```sh
cd core
make
```

### Módulo principal `DUKE`

```sh
cd DUKE
make
# opcional: gerar CLI
make cli
```

## Documentação

A documentação detalhada está disponível na pasta [`docs/`](docs/):

- [Visão geral de uso](docs/USAGE.md)
- [Descrição dos módulos](docs/MODULES.md)
- [Roadmap](docs/ROADMAP.md)

## Módulos

Os principais módulos atuais do ERP são:

- **core** – biblioteca compartilhada com tipos e utilitários básicos.
- **DUKE** – motor de cálculo e interface de linha de comando.
- **Financeiro** – funcionalidades relacionadas a custos e fluxo financeiro.

## Roadmap

O desenvolvimento do DUKE segue um roteiro público. Entre os próximos passos estão a modularização adicional do núcleo, aprimoramentos na persistência de dados, evolução da CLI e inclusão de testes automatizados.

Para detalhes completos consulte o arquivo [docs/ROADMAP.md](docs/ROADMAP.md).

