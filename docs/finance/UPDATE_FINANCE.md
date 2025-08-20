from pathlib import Path

# Conteúdo do UPDATE_FINANCE.md criado na resposta anterior
content = """# UPDATE_FINANCE.md — Módulo Financeiro (v0.01)

## 0) Objetivo (MVP – foco em caixa)
Registrar e consultar **lançamentos financeiros** (saídas/entradas), filtrando por **tipo** e **subtipo**, com somatórios por período. Sem conciliação bancária ainda. Persistência em JSON.

**Tipos principais**  
- **Compra** (insumos, matéria-prima, ferramenta)  
- **Vendas** (recebíveis)  
- **Outros** (manutenção, dívidas)  
- **Contas** (salário, básico: energia elétrica, internet)  
- **Investimento**  
- **Cofrinho** (fundo emergencial, expansões)

> Regime: **Caixa** (entrada/saída na data do pagamento/recebimento).

---

## 1) Tarefas Prioritárias (Do Now)

### A) Domínio & DTOs
- [ ] Criar enums e structs
  - `include/finance/Tipos.h`
    ```cpp
    enum class Tipo { Compra, Vendas, Outros, Contas, Investimento, Cofrinho };
    // Subtipo livre (string) nesta versão
    ```
  - `include/finance/Lancamento.h`
    ```cpp
    struct Lancamento {
      std::string id;           // "FIN-2025-08-18-0001"
      Tipo tipo;                // enum
      std::string subtipo;      // "insumos", "ferramenta", "salario", etc.
      std::string descricao;    // opcional
      double valor;             // >0
      std::string moeda;        // "BRL"
      std::string data;         // ISO "2025-08-18"
      bool entrada;             // true=recebível/entrada, false=saída
      std::string projeto_id;   // opcional (integração futura)
      std::string conta;        // opcional ("caixa", "carteira", "banco")
      std::vector<std::string> tags; // ["maca","cliente_x"]
    };
    ```
  - `include/finance/Filters.h`
    ```cpp
    struct Filtro {
      std::optional<Tipo> tipo;
      std::optional<std::string> subtipo;
      std::optional<std::string> conta;
      std::optional<std::string> dt_ini, dt_fim; // ISO inclusive
      std::optional<bool> entrada;
      std::vector<std::string> tags_all; // AND
    };
    ```

- [ ] Conversões JSON
  - `include/finance/Serialize.h` / `src/finance/Serialize.cpp`  
    - `to_json(const Lancamento&)`, `from_json(Lancamento&)`
    - `to_string(Tipo)`, `tipo_from_string(std::string)`

### B) Persistência (JSON)
- [ ] Repositório
  - `include/finance/Repo.h` / `src/finance/Repo.cpp`
    ```cpp
    class FinanceRepo {
    public:
      bool load(const std::string& path="docs/financeiro/lancamentos.json");
      bool save(const std::string& path="docs/financeiro/lancamentos.json") const;
      std::string nextId() const;
      void add(const Lancamento&);
      bool remove(const std::string& id);
      std::vector<Lancamento> query(const Filtro&) const;
      double sum(const Filtro&) const; // entradas positivas, saídas negativas
    private:
      int schema_version = 1;
      std::vector<Lancamento> items;
    };
    ```
- [ ] Estrutura de arquivo
  - `docs/financeiro/lancamentos.json` com `schema_version` e array `items`

### C) CLI (MVP)
- [ ] Comandos
  - `calculator fin add --tipo=Compra --subtipo=insumos --valor=129.90 --data=2025-08-18 --desc="TNT rolo" --saida`
  - `calculator fin add --tipo=Vendas --subtipo=recebiveis --valor=850.00 --data=2025-08-18 --entrada`
  - `calculator fin list --tipo=Contas --dt-ini=2025-08-01 --dt-fim=2025-08-31`
  - `calculator fin sum  --tipo=Compra --dt-ini=2025-08-01 --dt-fim=2025-08-31`
- [ ] Integração de menu (se já houver menu geral)
  - `Principal > Financeiro > Adicionar | Listar | Soma por filtro`

### D) Relatórios rápidos (texto/CSV)
- [x] `fin report mes --ano=2025 --mes=08` → imprime tabela: Data | Tipo | Subtipo | Descrição | ±Valor | Conta
- [x] Exportar CSV em `out/finance/2025-08-report.csv`

### E) Validações & Regras
- [ ] `valor > 0`
- [ ] `data` em ISO válida  
- [ ] `entrada` define o sinal: `sum()` considera **+valor** se entrada, **-valor** se saída
- [ ] `tipo` obrigatório; `subtipo` livre mas recomendado (sugestões via help)

---

## 2) Schema de Dados (JSON)

### 2.1 `docs/financeiro/lancamentos.json`
```json
{
  "schema_version": 1,
  "items": [
    {
      "id": "FIN-2025-08-18-0001",
      "tipo": "Compra",
      "subtipo": "insumos",
      "descricao": "TNT rolo 1,6m",
      "valor": 129.9,
      "moeda": "BRL",
      "data": "2025-08-18",
      "entrada": false,
      "projeto_id": "",
      "conta": "caixa",
      "tags": ["maca","ducaly"]
    },
    {
      "id": "FIN-2025-08-18-0002",
      "tipo": "Vendas",
      "subtipo": "recebiveis",
      "descricao": "Venda maca padrão",
      "valor": 850.0,
      "moeda": "BRL",
      "data": "2025-08-18",
      "entrada": true,
      "projeto_id": "PRJ-2025-08-17-2101",
      "conta": "banco",
      "tags": ["cliente_x"]
    }
  ]
}
