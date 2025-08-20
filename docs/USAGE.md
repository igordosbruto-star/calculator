# Uso via CLI

## Dependências

A CLI utiliza a toolkit [wxWidgets 3](https://www.wxwidgets.org). Certifique-se de que as
bibliotecas estejam instaladas e disponíveis via `wx-config` antes da compilação.

No Debian/Ubuntu, por exemplo, instale com:

```sh
sudo apt install libwxgtk3.2-dev
```

Após a instalação, compile um programa simples para validar o ambiente:

```cpp
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    bool OnInit() override {
        new wxFrame(nullptr, wxID_ANY, "Teste")->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
```

```sh
g++ teste.cpp $(wx-config --cxxflags --libs) -o teste
./teste
```

O DUKE pode ser executado com as seguintes opções:

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

## Menu e Navegação

Estrutura de menus disponível na linha de comando.

### Menu Principal

- **Materiais**
  - Listar
  - Criar
- **Projetos**
  - Abrir
  - Listar
- **Relatórios**
  - Custos
  - Tempos

A navegação é realizada por meio de subcomandos, por exemplo `./app listar` ou `./app comparar --ids=1,2`.

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

Execute `scripts/start.bat` para gerar os arquivos de configuração do VS Code.
Antes da criação desses arquivos, o script verifica se `g++`, `make` e `gdb`
estão instalados. Caso alguma dependência não seja encontrada, a execução é
interrompida com uma mensagem de erro.
