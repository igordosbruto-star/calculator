# SUGESTÕES DE MELHORIAS (Bate‑papo Guiado)

> Documento vivo para organizar ideias e priorizar a evolução do projeto **Calculator** (C++).
> Foco atual: **tipos de materiais** (unitário/linear/cúbico), **custo de produção** e **UX do CLI**. 

## 1) Visão Geral
- **Objetivo**: tornar o app uma base confiável para orçamento de produção (materiais + tempo + perdas) mantendo CLI simples e evoluindo sem quebrar o core.
- **Princípios**: camadas claras (CLI ↔ App ↔ Domínio ↔ Persist), dados reprodutíveis, testes cobrindo fluxos críticos, docs curtas e úteis.

## 2) Prioridades (propostas)
- [ ] Separar **materiais por tipo** no domínio e na persistência: `unitário`, `linear`, `cúbico`.
- [ ] Implementar **engine de custo** (material + perdas + fator mão de obra + markup). 
- [ ] Refinar **CLI** com menus interativos e submenus (em vez de opções estáticas mais barato/caro).
- [ ] Consolidar **persistência** (schemas estáveis + migrações simples). 
- [ ] Cobrir com **testes** os caminhos felizes e de erro.

## 3) Materiais por Tipo
### 3.1 Domínio (sugestão)
- `include/domain/MaterialBase.h` (classe abstrata com interface comum: `tipo()`, `custo(...)`).
- `include/domain/MaterialUnitario.h`  / `src/domain/MaterialUnitario.cpp`  
- `include/domain/MaterialLinear.h`    / `src/domain/MaterialLinear.cpp`  
- `include/domain/MaterialCubico.h`    / `src/domain/MaterialCubico.cpp`
- **Factory**: `MaterialFactory::fromDTO(MaterialDTO)` para instanciar o tipo correto.

### 3.2 Persistência
- Expandir `MaterialDTO` com campo `tipo` = {`unitario`, `linear`, `cubico`}.
- Validar por tipo:
  - unitário → `preco_unitario`
  - linear   → `preco_m` (+ opcional `perda_percent`)
  - cúbico   → `preco_m3` (+ `densidade` se útil)
- **Migração**: ao carregar `materiais.json` sem `tipo`, assumir `linear` (retrocompatibilidade) e salvar já com `tipo`.

### 3.3 Fórmulas (mínimo viável)
- Unitário: `custo = preco_unitario * qtd`
- Linear: `custo = preco_m * metros * qtd * (1 + perda%)`
- Cúbico: `custo = preco_m3 * (L × A × P) * qtd`

## 4) Engine de Custo de Produção
- `include/custo/CustoParams.h`: perdas padrão, fator mão de obra, markup, casas decimais.
- `include/custo/EstimadorCusto.h` / `src/custo/EstimadorCusto.cpp`:
  - `double custoMaterial(const ItemReq& req, const MaterialBase& m);`
  - `double custoProjeto(const Projeto& p, const CustoParams& cfg);`
- Estruturas auxiliares:
  - `ItemReq { id_material, tipo_material, qtd, medidas }`
  - `ItemCorte { nome, largura, comprimento, profundidade?, qtd, id_material? }`
- Saída consolidada: subtotal por item, total, % perdas aplicadas, markup e total final.

## 4.1) Projetos / Produtos (novo)
**Objetivo:** permitir criar **Projetos** (produtos) compostos por **materiais** e **cortes**, com custo total.

### Domínio
- `include/domain/Projeto.h` / `src/domain/Projeto.cpp`
  - `struct ProjetoItemMaterial { std::string id_material; double qtd; Medidas medidas; }`
  - `struct ProjetoItemCorte    { std::string nome; double largura; double comprimento; double profundidade; double qtd; std::string id_material; }`
  - `class Projeto { std::string id; std::string nome; std::vector<ProjetoItemMaterial> materiais; std::vector<ProjetoItemCorte> cortes; }`
  - Métodos: `adicionarMaterial(...)`, `adicionarCorte(...)`, `removerItem(...)`, `resumoCusto(const CustoParams&)`.

### Persistência
- `include/persist/projeto.hpp` / `src/persist_projeto.cpp`
  - DTOs: `ProjetoDTO { id, nome, itens_materiais[], itens_cortes[], tempos? }`
  - Funções: `saveProjetoJSON(const ProjetoDTO&)`, `loadProjetoJSON(id)`, `listarProjetos()`, `deleteProjeto(id)`
  - Estrutura em disco: `data/projetos/<id>/projeto.json` + `data/projetos/index.json`

### Cálculo de custo (regra mínima viável)
- **Materiais unitários**: `custo = preco_unitario * qtd`
- **Materiais lineares**: `custo = preco_m * comprimento_total * (1 + perda%)`
- **Materiais cúbicos**: `custo = preco_m3 * (L×A×P * qtd)`
- **Cortes**: se informados com `id_material`, calcular custo usando material associado; se não, apenas gerar relatório de áreas/volumes.
- **Projeto**: somar subtotais + `mão_de_obra` + `overhead%` + `markup%` de `CustoParams`.

### Validações
- IDs de materiais referenciados devem existir na base.
- Quantidades e medidas > 0 (com tolerâncias para zero em campos não usados pelo tipo).
- Limites de segurança (ex.: volume máximo por item, casas decimais).

### Exemplo (JSON) — `data/projetos/<id>/projeto.json`
```json
{
  "id": "PRJ-2025-08-17-2101",
  "nome": "Maca padrão",
  "itens_materiais": [
    { "id_material": "MAT-PES-SOFA-01", "qtd": 4 },
    { "id_material": "MAT-SARRAFO-15", "qtd": 6, "medidas": { "comprimento": 1.2 } }
  ],
  "itens_cortes": [
    { "nome": "Lateral MDF 15mm", "largura": 0.56, "comprimento": 1.85, "qtd": 2, "id_material": "MAT-MDF-15" },
    { "nome": "Tampo MDF 3mm",   "largura": 0.56, "comprimento": 1.85, "qtd": 1, "id_material": "MAT-MDF-3" }
  ],
  "tempos": { /* vide seção 4.2 */ }
}
```

### CLI (menus)
- **Menu Principal > Criar > Projeto**: nome → adicionar itens (Material/Corte) → salvar.
- **Menu Principal > Listar > Projetos**: mostrar tabela (id, nome, itens, custo estimado) → abrir.
- **Menu Principal > Comparar > Projetos**: comparar custos entre projetos selecionados.
- **Menu Principal > Configurações > Custo**: editar `CustoParams` (mão de obra, overhead, markup).

### Critérios de aceite
- Criar, salvar e reabrir projetos com materiais e cortes referenciando a base.
- Cálculo de custo retorna totais coerentes para cada tipo de material.
- Listagem de projetos mostra custo estimado sem erro; comparação destaca menor/maior.

## 4.2) Tempos de Produção por Projeto / Produto (novo)
**Objetivo:** modelar e calcular o **tempo de fabricação** por fases e operações, somando ao custo final de mão de obra.

### Conceitos
- **Fase** (setor): `Marcenaria`, `Estofaria`, `Costura`, `CorteTecido`, `Acabamento`, `Montagem` (extensível).
- **Operação**: unidade de trabalho dentro de uma fase (ex.: "Cortar lateral MDF 15mm", "Furar espuma", "Colar espuma", "Gabaritar tecido").
- **Template de produto**: conjunto de operações pré-definidas por tipo de produto (ex.: **Maca**, **Almofada**), com fases aplicáveis.
- **Modificadores por material**: certos materiais alteram o tempo (ex.: espuma D33 vs D20, tecidos com costura).

### Domínio
- `include/domain/Tempo.h` / `src/domain/Tempo.cpp`
  - `enum class Fase { Marcenaria, Estofaria, Costura, CorteTecido, Acabamento, Montagem };`
  - `struct Operacao { Fase fase; std::string nome; double min_base; double k_area; double k_perimetro; double k_qtd; std::map<std::string,double> fatores_por_material; bool opcional; };`
  - `struct TempoProjeto { std::vector<Operacao> ops; }`
  - **Cálculo por operação**: `min = min_base + k_area*area + k_perimetro*perim + k_qtd*qtd;` aplicar multiplicadores conforme material/densidade/tecido.
  - **Total por fase** e **total geral** (minutos e horas).

### Persistência
- Guardar dentro de `projeto.json` em `tempos`, o snapshot dos parâmetros/resultado, ou arquivo separado `data/projetos/<id>/tempos.json`.
- `TempoDTO` com `ops[]` (fase, nome, parâmetros, flags e fatores) e **resumo calculado** (min por fase e total).
- `CustoParams` ganha `taxa_hora_{marcenaria, estofaria, costura, corte_tecido, acabamento, montagem}`.

### Regras e exemplos
- **Maca** (template):
  - *Marcenaria*: cortar laterais (k_area), cortar tampo (k_area), montar estrutura (min_base), acabamento (k_qtd).
  - *Estofaria*: furar espuma (fator por densidade D20/D33), colar espuma (k_area), tapeçar tecido (k_area + fator costura).
  - *CorteTecido*: preparar/gabaritar tecido (k_area), cortes auxiliares (k_qtd).
- **Almofada** (template): ignora Marcenaria; usa *CorteTecido*, *Costura* e *Estofaria*.

### CLI (menus)
- **Projeto > Adicionar tempo**: escolher template (Maca, Almofada, Vazio) → revisar operações → editar parâmetros → salvar.
- **Projeto > Editar tempo**: ligar/desligar operações opcionais (ex.: costura) e ajustar fatores.
- **Projeto > Resumo**: mostrar tempo por fase, custo de mão de obra (= horas × taxa do setor) e total do projeto.

### Cálculo de custo de mão de obra
- `custo_mao_obra = Σ_fases ( minutos_fase/60 × taxa_hora_fase )`.
- Integrar ao `custoProjeto(...)` junto com materiais/markup.

### Critérios de aceite
- É possível criar um projeto **sem Marcenaria** (ex.: Almofada) e o cálculo ignora essa fase.
- Tempos reagem a **materiais diferentes** (ex.: D33 > D20 para "Furar espuma").
- Resumo mostra **tempo por fase** e **total**, além do **custo de mão de obra** integrado ao total do projeto.

## 4.3) Métricas e KPIs de Projeto (custos & tempo) — novo
**Objetivo:** manter **variáveis agregadas** por projeto para relatório e análise.

### Variáveis calculadas por Projeto
- `custo_materiais`  → soma de todos os itens (unitário/linear/cúbico) pós‑perdas.
- `custo_tempo`      → soma por fase: `Σ(min/60 × taxa_hora_fase)`.
- `custo_embalagem`  → valor fixo ou tabela por tipo de produto.
- `custo_total`      → `custo_materiais + custo_tempo + custo_embalagem`.
- `tempo_total_min`  → soma de minutos de todas as fases (também armazenar horas).
- (opcional) `preco_venda`, `margem%`, `markup%` para análise comercial.

### Persistência
- Gravar **snapshot** dessas variáveis em `data/projetos/<id>/projeto.json` ao salvar/recalcular.
- Atualizar `data/projetos/index.json` com índices: `{ id, nome, data, custo_total, custo_materiais, custo_tempo, tempo_total_min }` para consulta rápida.

### Relatórios (CLI)
- `Relatórios > Custos por Projeto`  → tabela (id, nome, custo_materiais, custo_tempo, embalagem, total).
- `Relatórios > Tempo por Projeto`   → tabela (id, nome, tempo_total_min, por_fase).
- Filtros: por período (data), por tipo de produto, por faixa de custo/tempo.
- Exportar CSV/MD com cabeçalhos estáveis para análise externa.

### Regras
- Todos os valores monetários exibidos com `format.h` (moeda/casas decimais).
- Recalcular métricas sempre que itens/tempos forem alterados antes do **Salvar**.
- Tratar ausências: se `custo_embalagem` não informado, assumir 0.

### Critérios de aceite
- Ao abrir **Relatórios**, listar corretamente projetos com métricas atualizadas.
- Exportar CSV com colunas: `id,nome,custo_materiais,custo_tempo,custo_embalagem,custo_total,tempo_total_min`.
- Mudanças em um projeto refletem imediatamente nas métricas e no `index.json`. 
- É possível criar um projeto **sem Marcenaria** (ex.: Almofada) e o cálculo ignora essa fase.
- Tempos reagem a **materiais diferentes** (ex.: D33 > D20 para "Furar espuma").
- Resumo mostra **tempo por fase** e **total**, além do **custo de mão de obra** integrado ao total do projeto.

## 4.3) Componentes de Custo e Relatórios (novo)
**Objetivo:** padronizar campos de custo no Projeto e oferecer relatórios por componente (materiais, tempo, embalagem) e total.

### Domínio (Projeto)
Adicionar campos calculados e/ou armazenados em `Projeto`:
- `double custo_materiais`  → soma de itens de materiais e cortes com material associado.
- `double custo_tempo`      → soma por fase (min/60 × taxa_hora_fase).
- `double custo_embalagem`  → fixo ou por item (campo editável por projeto).
- `double custo_total`      → `custo_materiais + custo_tempo + custo_embalagem`.
- `double minutos_total`    → total de minutos do projeto (de `TempoProjeto`).
> Observação: manter também o detalhe (por fase e por item) para relatórios.

### Persistência
- `ProjetoDTO` armazena `custo_embalagem` (opcional) e guarda **último snapshot de custo** após cálculo, além de sempre permitir recalcular.
- Índices: `data/projetos/index.json` com colunas chave: `id, nome, custo_total, custo_materiais, custo_tempo, custo_embalagem, minutos_total, updated_at`.

### Relatórios
- **Por componente**:
  - `report materiais` → tabela de projetos com `custo_materiais` (filtro por período/nome).
  - `report tempo`     → tabela com `minutos_total` e `custo_tempo` (quebrado por fase, opcional).
  - `report total`     → visão geral com `custo_total` e ranking.
- **Export**: CSV (sempre) e MD/JSON (opcional) em `out/reports/AAAA-MM/`.
- **Filtros**: por `tag` do projeto (futuro), por fase, por tipo de produto (template).

### CLI (menus)
- **Menu Principal > Relatórios**
  - `Materiais` · `Tempo` · `Totais` · `Por fase`
  - Perguntar período (ex.: mês atual, último mês, intervalo) e filtros simples.

### Critérios de aceite
- Projetos exibem e salvam `custo_materiais, custo_tempo, custo_embalagem, custo_total, minutos_total`.
- É possível exportar CSV dos três relatórios principais sem erro.
- Recalcular custo reatualiza os campos e o `index.json`.

- É possível criar um projeto **sem Marcenaria** (ex.: Almofada) e o cálculo ignora essa fase.
- Tempos reagem a **materiais diferentes** (ex.: D33 > D20 para "Furar espuma").
- Resumo mostra **tempo por fase** e **total**, além do **custo de mão de obra** integrado ao total do projeto.
- Usuário consegue adicionar/remover etapas de tempo.
- Projetos salvos carregam e mostram tempos.
- Relatórios exibem horas por setor e total junto ao custo.

### Validações
- IDs de materiais referenciados devem existir na base.
- Quantidades e medidas > 0 (com tolerâncias para zero em campos não usados pelo tipo).
- Limites de segurança (ex.: volume máximo por item, casas decimais).

### Exemplo (JSON) — `data/projetos/<id>/projeto.json`
```json
{
  "id": "PRJ-2025-08-17-2101",
  "nome": "Sofá Dublin 3L",
  "itens_materiais": [
    { "id_material": "MAT-PES-SOFA-01", "qtd": 4 },
    { "id_material": "MAT-SARRAFO-15", "qtd": 6, "medidas": { "comprimento": 1.2 } }
  ],
  "itens_cortes": [
    { "nome": "Assento", "largura": 0.60, "comprimento": 1.80, "qtd": 2, "id_material": "MAT-ESPUMA-28D" }
  ]
}
```

### CLI (menus)
- **Menu Principal > Criar > Projeto**: nome → adicionar itens (Material/Corte) → salvar.
- **Menu Principal > Listar > Projetos**: mostrar tabela (id, nome, itens, custo estimado) → abrir.
- **Menu Principal > Comparar > Projetos**: comparar custos entre projetos selecionados.
- **Menu Principal > Configurações > Custo**: editar `CustoParams` (mão de obra, overhead, markup).

### Critérios de aceite
- Criar, salvar e reabrir projetos com materiais e cortes referenciando a base.
- Cálculo de custo retorna totais coerentes para cada tipo de material.
- Listagem de projetos mostra custo estimado sem erro; comparação destaca menor/maior.


### 5.1 Estrutura de Menus (proposta v0.02)
```
Menu Principal
 ├─ Comparar
 │   ├─ Materiais
 │   ├─ Cortes
 │   └─ Projetos
 ├─ Criar
 │   ├─ Material
 │   ├─ Corte
 │   └─ Projeto
 ├─ Listar
 │   ├─ Materiais
 │   ├─ Cortes (planos salvos)
 │   └─ Projetos
 ├─ Configurações
 │   ├─ Preferências (casas decimais, moeda, idioma)
 │   ├─ Persistência (pastas de data/out)
 │   └─ Materiais (tipo padrão, validações)
 └─ Sair
```

- **Navegação**: números (1–9), setas (↑/↓) opcionais, `Enter` confirma, `Esc`/`0`/`b` volta.
- **Breadcrumbs**: exibir trilha no topo: `Principal > Criar > Material`.
- **Acessibilidade**: atalhos alfabéticos (`C` Criar, `L` Listar, etc.).
- **Ajuda contextual**: `?` mostra ajuda da tela atual.
- **Estado limpo**: limpar tela entre telas (ou separadores) e sempre mostrar opções válidas.

### 5.2 Fluxos essenciais
- **Criar > Material**
  1) Escolher **tipo**: `Unitário | Linear | Cúbico`.
  2) Formular inputs por tipo:
     - Unitário: nome, `preço_unitário`, fornecedor (opc.), estoque (opc.).
     - Linear: nome, `preço_m`, perdas %, unidade (m), observação (opc.).
     - Cúbico: nome, `preço_m3`, L×A×P (defaults 0), densidade (opc.).
  3) Validar e salvar (mostra resumo + opção de editar antes de confirmar).

- **Comparar > Materiais**
  - Selecionar dois ou mais materiais (checkbox via números separados por vírgula) e exibir tabela: nome, tipo, métrica de custo (por unidade/m/m³) e destaque do menor/maior.

- **Listar > Cortes**
  - Ler `out/planos/index.json` e exibir últimas N execuções com totals; opção de **abrir** para ver resumo (sem refazer cálculo).

### 5.3 Remover seleção "mais barato/mais caro"
- Substituir por **Selecionar Material** com filtros e ordenação:
  - Filtros: `tipo` (todos/unitário/linear/cúbico).
  - Ordenação: `nome`, `preço` (asc/desc).
  - Busca rápida por substring.

### 5.4 API interna (C++)
- `MenuState` (enum): `Principal, Comparar, Criar, Listar, Config, Sair` + subestados.
- `struct Screen { std::string title; std::vector<std::string> options; };`
- `int promptMenu(const Screen&, int defaultIdx=0);` retorna índice seguro.
- `void renderBreadcrumb(const std::vector<std::string>&);`
- `void clearScreen();` (portável: imprimir várias quebras) e separadores.
- Helpers de entrada: `readDouble(min,max)`, `readInt(min,max)`, `readString(notEmpty)` com retry automático.

**Arquivos novos**
- `include/ui/Menu.h` / `src/ui/Menu.cpp` (infra de menu e helpers)
- `include/ui/Screens.h` (definições das telas/strings)
- Ajuste em `App.cpp`: loop principal chamando o **state machine** de menus.

### 5.5 Critérios de aceite (UX)
- Nenhuma entrada inválida derruba o app; usuário sempre tem **voltar**.
- Todas as telas mostram breadcrumbs e ajuda `?`.
- É possível **criar material** dos três tipos e salvá-lo; **listar** confirma persistência.
- É possível **comparar** pelo menos 2 materiais com destaque de menor/maior.

### 5.6 CLI (compatível)
- Manter execução via argumentos para automação, mas alinhar com menus:
  - `calculator criar material --tipo=linear --nome="MDF 15mm" --preco-m=179.9` 
  - `calculator listar materiais --tipo=linear --ordem=preco:asc`
  - `calculator comparar materiais --ids 1,3,5`

## 6) Persistência & Dados
- Schemas versionados: `schema_version` em `materiais.json` e `settings.json`.
- **Migrações** simples: função `upgradeIfNeeded(json&)` por arquivo.
- Backups automáticos `.bak` (já existe para escrita atômica — manter).
- Índices úteis (histórico de simulações em `out/`), nomeados por timestamp.

## 7) Testes & Qualidade
- Unitários por tipo de material (caminhos de sucesso e erro). 
- Testes da engine de custo (casos: unitário, linear com perda, cúbico com volume 0, arredondamento).
- Golden tests para CSV/JSON (comparar saída estável).
- Pipeline CI (GitHub Actions): build, testes e artefatos.

## 8) Documentação
- `docs/MATERIAIS.md`: explicar tipos, campos e exemplos de JSON.
- `docs/CUSTO.md`: fórmulas e exemplos de simulação.
- `docs/MENU.md`: descrever fluxo do menu principal e submenus.
- Atualizar `USAGE.md` com novos subcomandos.

## 9) Roadmap Sugerido
**Curto prazo (v0.02)**
- [ ] Adicionar `tipo` a `MaterialDTO` + migração on‑load.
- [ ] Implementar classes `Unitario/Linear/Cubico` + factory.
- [ ] Ajustar CLI para cadastro/listagem por tipo.
- [ ] Implementar menu principal com navegação básica.
- [ ] Testes unitários para validação por tipo.

**Médio prazo (v0.03)**
- [ ] Engine de custo com `EstimadorCusto` e `CustoParams`.
- [ ] Subcomando `custo simular` (entrada interativa e via arquivo).
- [ ] Relatório CSV/MD por simulação.
- [ ] Menus de comparação mais ricos (escolher critérios).

**Depois (v0.04+)**
- [ ] Integração de sobras (catálogo) no cálculo de custo.
- [ ] Exportações adicionais (PDF, planilha). 

---

## 10) Suas Ideias (vamos preencher juntos)
> Liste aqui suas ideias brutas; eu transformo em tarefas claras.
- [ ] Menu Principal interativo com submenus.
- [ ] Substituir opção "mais barato/caro" por menus de comparação com múltiplos critérios.
- [ ] Fluxo mais limpo e intuitivo, sem depender apenas de flags no CLI.

## 11) Tarefas Derivadas do Bate‑papo (to‑do dinâmico)
- [ ] **UI Infra**: `Menu.h/cpp` com `promptMenu`, helpers e breadcrumbs.
- [ ] **State Machine**: loop de menus no `App` com subestados.
- [ ] **Projeto (domínio)**: `Projeto.h/.cpp` (materiais, cortes) + `Tempo.h/.cpp` (fases/ops) + agregados.
- [ ] **Persistência de projeto**: `persist_projeto.cpp` + DTOs + `data/projetos/index.json` (com métricas agregadas).
- [ ] **Custo**: `EstimadorCusto` soma materiais + `custo_mao_obra` + embalagem + overhead/markup → `custo_total`.
- [ ] **Relatórios (CLI)**: custos por projeto e tempo por projeto (filtros + export CSV).
- [ ] **Templates de tempo**: *Maca* e *Almofada* (JSON em `data/templates/tempos/`).
- [ ] **Validação**: permitir produtos sem certas fases; tratar `custo_embalagem` opcional.
- [ ] **Docs**: `docs/TEMPOS.md`, `docs/PROJETOS.md`, `docs/RELATORIOS.md` com exemplos.
- [ ] **Testes**: métricas persistidas corretas; CSV com colunas estáveis; filtros de relatório.

---

Se quiser, eu já gero os **stubs C++** e um exemplo de **CSV de relatório**.

