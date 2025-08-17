# CHECKLIST.md — Itens obrigatórios antes de commitar/abrir PR

## 🔍 Revisão de Código
- [x] Revisar todos os arquivos modificados
- [x] Confirmar que não há código morto ou duplicado
- [x] Garantir que todas as variáveis estão inicializadas
- [x] Verificar se modularização foi aplicada (funções curtas, `.cpp` separados)
- [x] Confirmar que os logs usam `wr:p` corretamente (Debug/Aviso/Erro)

## 🧪 Testes
- [x] Adicionar testes em `/tests` para cada nova funcionalidade
- [x] Compilar e rodar testes com:
  ```sh
  g++ -std=c++17 -Wall tests/*.cpp src/*.cpp -Iinclude -o tests/run_tests
  ./tests/run_tests
  ```
- [ ] Garantir que casos de erro também possuem testes cobrindo o log em vermelho

## 📑 Documentação
- [x] Adicionar comentários em português explicando intenções do código
- [x] Exemplos mínimos nas funções públicas
- [x] Atualizar `Roadmap.md` com novas implementações

## 🛠️ Build & Lint
- [x] Compilar a aplicação com:
  ```sh
  g++ -std=c++17 -Wall src/*.cpp -Iinclude -o app
  ```
- [x] Garantir que warnings foram tratados ou justificados
- [x] Verificar se a estrutura de pastas continua organizada (`/src`, `/include`, `/tests`)

## 📦 Git & Commits
- [x] Commit segue o padrão Conventional Commits (`feat:`, `fix:`, `chore:`)
- [x] Mensagem de commit curta e descritiva
- [x] Se for PR: título no padrão `[<módulo>] feat: descrição curta`
- [x] PR inclui checklist preenchido abaixo

---

### 📝 Exemplo de Checklist em PR
- Revisão de código: ✅  
- Testes adicionados e rodando: ✅  
- Documentação atualizada: ✅  
- Build e lint: ✅  
- Commits padronizados: ✅  
