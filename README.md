# ERP DUKE

[![CI](https://github.com/OWNER/calculator/actions/workflows/ci.yml/badge.svg)](https://github.com/OWNER/calculator/actions/workflows/ci.yml)

ERP DUKE é um sistema ERP modular voltado para o planejamento de cortes de materiais e gestão de projetos.

## Requisitos

O sistema depende da toolkit [wxWidgets 3](https://www.wxwidgets.org).
Instale as bibliotecas de desenvolvimento e garanta que `wx-config`
esteja disponível antes de compilar.

## Instalação

Antes de compilar, verifique se as dependências básicas estão presentes.
Para Linux e macOS, o script `check_deps.sh` detecta o sistema e checa
ferramentas como `g++`, `make` e bibliotecas do wxWidgets, oferecendo a opção de
instalá-las automaticamente. No Windows há uma versão equivalente em
PowerShell (`check_deps.ps1`) que usa `winget` ou `choco` para instalar
pacotes faltantes.

Caso prefira instalar manualmente, utilize o gerenciador de pacotes do seu sistema:

```sh
# Debian/Ubuntu
sudo apt install libwxgtk3.2-dev

# macOS (Homebrew)
brew install wxwidgets
```

Linux/macOS:

```sh
./scripts/check_deps.sh
```

Windows (PowerShell):

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\check_deps.ps1
```

Execute o script apropriado sempre que configurar um novo ambiente de
desenvolvimento.

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

Certifique-se de que o wxWidgets esteja instalado e que `wx-config` esteja acessível.

Para compilar manualmente um exemplo mínimo com `wx-config`:

```cpp
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    bool OnInit() override {
        auto *frame = new wxFrame(nullptr, wxID_ANY, "Demo");
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
```

```sh
g++ exemplo.cpp $(wx-config --cxxflags --libs) -o exemplo
./exemplo
```

## Testes

O status das execuções automatizadas está disponível no badge de CI acima.

Para rodar todos os testes localmente:

```sh
make -C tests
```

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

