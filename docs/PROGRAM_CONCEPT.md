# Programa DUKE: Conceito para Estofaria

## 1. Visão geral do Programa

**Nome:** DUKE ERP – Sistema de Gestão para Estofaria

**Descrição resumida:**  
O DUKE é um sistema integrado de gestão (ERP) voltado para estofarias. Sua missão principal é facilitar o controle de pedidos, a gestão de clientes, a organização de materiais e a precificação, com foco na usabilidade para usuários de perfis diversos. O programa deve tornar o processo de produção e atendimento ao cliente mais eficiente, além de auxiliar na análise de custos e lucros de cada produto ou serviço.

**Adaptação para a realidade da estofaria:**  
O DUKE será dividido logicamente em três grandes módulos (ou programas) dentro de uma suíte: **Vendas**, **Produção** e **Administração**. Cada módulo é um app independente, mas todos compartilham uma base de dados e um núcleo comum, tornando o sistema escalável e flexível.

**Objetivos:**
- **Facilidade de uso:** Interface simples, menus claros e processos guiados.
- **Controle de materiais e fornecedores:** Consolidar informações para cruzamento de custos e melhor preço.
- **Gestão de vendas e clientes:** Registrar vendas, dados de clientes e histórico.
- **Cálculos financeiros:** Visualizar custos, lucros e relatórios claros.
- **Notificações:** Alertas de prazos, reposição de materiais e pendências.

---

## 2. Usuários e Personas

- **Costureira/Confeccionador(a):** Usa o módulo de produção para registrar etapas e tempo gasto.
- **Gerente/Responsável Administrativo:** Usa relatórios para decisões e controle total.
- **Atendente/Recepcionista:** Cadastra clientes, pedidos e pagamentos.
- **Fornecedor (perfil indireto):** Informações para comparação de custos.

---

## 3. Principais Módulos e Funcionalidades

### 3.1 Módulo de Vendas (Comercial)
- Cadastro e gestão de clientes
- Gestão de orçamentos e pedidos
- Controle de estoque de produtos finalizados
- Notificação de status de produção

### 3.2 Módulo de Produção (Operacional)
- Pedidos de produção e ordens de produção
- Controle de estoque de matérias-primas
- Planejamento de compras
- Registro de produção e tempo gasto
- Avisos para vendas
- Definição de lista de materiais (BOM) e variantes

### 3.3 Módulo de Administração (Financeiro e Compras)
- Controle financeiro (receitas e despesas)
- Cotações de fornecedores
- Otimização de custos
- Relatórios administrativos

### 3.4 Controle de Prazos e Notificações (Transversal)
- Registro de datas de entrega
- Alertas automáticos
- Comunicação intermodular

### 3.5 Relatórios
- Materiais vs. fornecedores
- Vendas e faturamento
- Produtividade
- Custos e lucros

### 3.6 Módulo de Designer de Projetos
- Canvas de montagem visual
- Associação de materiais e dimensões
- Simulações de custo
- Histórico e versões de projetos

---

## 4. Navegação e Interface do Usuário

### 4.1 Menu Principal
- **Clientes:** Cadastro, consulta e edição
- **Vendas:** Orçamentos, pedidos, estoque
- **Produção:** Ordens de produção, materiais, etapas
- **Administração/Financeiro:** Lançamentos, cotações, relatórios
- **Relatórios:** Filtros personalizáveis
- **Configurações:** Preferências, usuários, permissões

### 4.2 Usabilidade
- Navegação por ícones e textos simples
- Campos obrigatórios destacados
- Ajuda contextual (tooltips)
- Busca e filtros rápidos

---

## 5. Requisitos Técnicos

- **Plataforma/Frameworks:** Qt 6 (GUI e CLI), C++ (lógica)
- **Persistência de dados:** JSON e CSV; integração futura com banco de dados (ex.: SQLite)
- **Arquitetura:** Modular (Core, DUKE, Financeiro), API pública
- **Internacionalização:** Suporte a múltiplos idiomas (inicialmente português)
- **Backup e segurança:** Gravação atômica, permissões, backup automático

---

## 6. Arquitetura de Apps e Extensibilidade

- **Core unificado:** Persistência, autenticação, permissões, configuração global
- **Apps modulares:** Vendas, Produção, Administração, Designer
- **Integração transparente:** Compartilhamento de dados e eventos internos
- **Extensibilidade:** Novos módulos podem ser adicionados facilmente

---

## 7. Roadmap Proposto

- **Protótipo Básico:** Cadastro de clientes, materiais, lançamentos financeiros, orçamentos e vendas simples, interface CLI
- **Módulo de Cálculo e Produção:** Algoritmos de consumo/custo, relatórios de custos e lucro
- **Relatórios e Visualizações:** Dashboards, exportação CSV/PDF
- **Integração com Fornecedores:** Importação de listas de preços, comparação
- **Melhorias na Usabilidade:** Interface gráfica, notificações
- **Testes Automatizados:** Testes unitários/integrados, CI/CD

---

## 8. Conclusão

Este documento serve como guia inicial para o desenvolvimento do DUKE ERP, alinhando objetivos, funcionalidades e arquitetura modular baseada em apps. O sistema será flexível, escalável e adaptado à realidade da estofaria, facilitando a gestão, produção e comercialização, além de permitir expansão futura conforme as necessidades do negócio.