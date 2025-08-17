# AGENTS.md — Guia do Projeto

## Estrutura
- Código principal: `/src`
- Headers: `/include`
- Testes unitários: `/tests`

## Estilo de Código
- Linguagem: C++17
- Nome de classes em PascalCase, funções em camelCase
- Sempre inicializar variáveis
- Mensagens de log com `wr:p` (localizado em `/src/utils/logger.cpp`)
- Logs de debug em azul, avisos em amarelo, erros em vermelho no log

## Workflow
- Revisar todos os arquivos antes de fazer as alterações
- Toda modificação deve vir acompanhada de testes em `/tests`
- Adicionar implementações feitas em `Roadmap.md`
- Sempre que possível modularizar: preferir vários `.cpp` pequenos em vez de funções longas
- Verificar `CHECKLIST.md` e marcar entradas
- Rodar `cmake --build .` e `ctest` antes do commit
- Commits no padrão Conventional Commits (`feat:`, `fix:`, `chore:`)

## Documentação
- Use comentários em português, explicando a intenção do código
- Adicione exemplos mínimos em cada função pública

## Pull Requests
- Título no padrão: [<módulo>] feat: descrição curta
- Descrição deve incluir checklist do `CHECKLIST.md`
