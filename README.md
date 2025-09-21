# calculadoraSocket
Calculadora simples de computação distribuída utilizando sockets

---

## Requisitos Mínimos
- ✅ **Servidor TCP (IPv4)** funcional na porta indicada; pode ser **single-process/single-thread** (um cliente por vez).
- ✅ **Cliente** de terminal que lê linhas do **stdin**, envia ao servidor e imprime a resposta.
- ✅ **Parsing** robusto (validar quantidade de tokens, tipos numéricos e operação).
- ✅ **Tratamento de erros** (entrada inválida e divisão por zero).
- ✅ **Formatação** do resultado com **ponto decimal** (não depender do *locale*). Sugestão: `printf("%.6f\n", valor)` para `R`.
- ❌ **Makefile** com *targets* `all`, `server`, `client`, `clean`.
- ❌ **README.md** explicando execução, exemplos e decisões de projeto.

### Requisitos Recomendados
- ❌ Logs simples no servidor (conexões, requisições, erros). 
- ✅ Encerramento limpo ao receber `SIGINT` (Ctrl+C). 
- ✅ Parametrização de endereço/porta no cliente (`./client 127.0.0.1 5050`). 

### Bônus (até +10%)
- ❌ **Concorrência**: atender múltiplos clientes (via `fork`, *threads* ou `select/poll`). 
- ❌ **Testes automatizados** (scripts que disparam casos de teste e comparam saídas). 
- ❌ **Protocolo estendido** (ex.: aceitar forma infixa, mensagens `HELP`, `VERSION`). 

---
