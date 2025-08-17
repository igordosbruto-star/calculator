# CHECKLIST.md — Itens obrigatórios antes de commitar/abrir PR

## 🔍 Revisão de Código
- [ ] Revisar todos os arquivos modificados
- [ ] Confirmar que não há código morto ou duplicado
- [ ] Garantir que todas as variáveis estão inicializadas
- [ ] Verificar se modularização foi aplicada (funções curtas, `.cpp` separados)
- [ ] Confirmar que os logs usam `wr:p` corretamente (Debug/Aviso/Erro)

## 🧪 Testes
- [ ] Adicionar testes em `/tests` para cada nova funcionalidade
- [ ] Compilar e rodar testes com:
  ```sh
  g++ -std=c++17 -Wall tests/*.cpp src/*.cpp -Iinclude -o tests/run_tests
  ./tests/run_tests
  ```
- [ ] Garantir que casos de erro também possuem testes cobrindo o log em vermelho

## 📑 Documentação
- [ ] Adicionar comentários em português explicando intenções do código
- [ ] Exemplos mínimos nas funções públicas
- [ ] Atualizar `Roadmap.md` com novas implementações

## 🛠️ Build & Lint
- [ ] Compilar a aplicação com:
  ```sh
  g++ -std=c++17 -Wall src/*.cpp -Iinclude -o app
  ```
- [ ] Garantir que warnings foram tratados ou justificados
- [ ] Verificar se a estrutura de pastas continua organizada (`/src`, `/include`, `/tests`)

## 📦 Git & Commits
- [ ] Commit segue o padrão Conventional Commits (`feat:`, `fix:`, `chore:`)
- [ ] Mensagem de commit curta e descritiva
- [ ] Se for PR: título no padrão `[<módulo>] feat: descrição curta`
- [ ] PR inclui checklist preenchido abaixo

---

### 📝 Exemplo de Checklist em PR
- Revisão de código: ✅  
- Testes adicionados e rodando: ✅  
- Documentação atualizada: ✅  
- Build e lint: ✅  
- Commits padronizados: ✅  
