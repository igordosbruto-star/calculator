# Formatos de Dados

Exemplos unificados de estruturas para **Projetos**, **Relatórios** e **Tempos** utilizados no sistema. Os formatos
suportados são JSON, CSV e XML. A API `Persist::save`/`load` escolhe o
formato conforme a extensão do arquivo.

## Projetos
Estrutura básica para armazenar projetos de corte.

### Exemplo JSON
```json
{
  "id": "p1",
  "nome": "protótipo",
  "materiais": [
    {"id": "m1", "quantidade": 2}
  ]
}
```

### Exemplo CSV
```
id,nome,material,quantidade
p1,protótipo,m1,2
```

### Exemplo XML
```xml
<projeto id="p1" nome="protótipo">
  <material id="m1" quantidade="2"/>
</projeto>
```

## Relatórios
Dados consolidados com informações de projetos e execuções.

### Exemplo JSON
```json
{
  "projeto": "p1",
  "custo_total": 100.0,
  "itens": 3
}
```

### Exemplo CSV
```
projeto,custo_total,itens
p1,100.0,3
```

## Tempos
Exemplos de registro de durações de execução.

### Exemplo JSON
```json
{
  "etapa": "corte",
  "duracao_ms": 1200
}
```

### Exemplo CSV
```
etapa,duracao_ms
corte,1200
```
