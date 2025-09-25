# Calculadora Cliente-Servidor com Sockets em C

## Feito Por:
- Marco Antonio de Camargo - 10418309
- Natan Moreira Passos - 10417916
- Nicolas Henriques de Almeida - 10418357 <br> <br>
Sala 06G - Mackenzie

## Objetivo
Implementar uma aplicação **cliente–servidor** em C, usando **sockets TCP (IPv4)**, na qual o cliente envia **operações matemáticas** e o servidor **executa** e **retorna o resultado**.<br>

---
## Funcionamento
### Cliente
1. Cria um socket e tenta se conectar ao servidor.
2. Após a conexão, entra em um loop de interação com o usuário:
    - Caso o usuário digite 1
        - O programa irá requisitar uma expressão
        - A expressão dada pelo usuário será transmitida ao servidor
        - O cliente aguarda a resposta, que pode ser:
            - Resultado da operação, se a expressão for válida.
            - Mensagem de erro, caso contrário. 
        - A resposta recebida é exibida na tela.
    - Caso o usuário digite 2, o programa se encerra.
### Servidor
1. Cria um socket, associa-o a um endereço e porta, e entra em modo passivo, aguardando um cliente que se conecte a ele.
2. Ao aceitar a conexão, entra em um loop de comunicação:
    - Recebe a expressão matemática enviada pelo cliente.
    - Verifica se a expressão é válida.
        - Se for, calcula o resultado e envia de volta.
        - Caso não seja valida, ou caso seja impossivel de resolver a expressão, envia uma mensagem de erro.
3. Permanece aguardando novas mensagens do cliente.
4. Caso nenhum cliente esteja conectado, permanece no estado de espera até que seja interrompido manualemnte `(Ctrl+C)`.
---
## Compilação e execução
### Compilar o código
- **Usando makefile:** 
```bash 
make all
```
- Isso criará os executáveis `server` e `client`.

- **Usando gcc manualmente:**
``` bash
gcc src/server/servidor.c src/server/serverProto.c -o server
gcc src/client/cliente.c src/client/clientProto.c -o client
```
- Isso criará os executáveis `server` e `client`.

### Execução
- Utilizando a porta padrão (5050) e o IP padrão (127.0.0.1)
``` bash
./server
./client
```
- Utilizando uma porta especifica e o IP padrão (127.0.0.1)
``` bash
./server <PORT>
./client <PORT>
```
- Utilizando uma porta e IP especificos
```bash
./server <PORT> <IP>
./client <PORT> <IP>
```

---
### Testes:
Após a criação dos executáveis `server` e `client`, pode-se usar o arquivo `test.sh`, que contém alguns testes automatizados.
- Usando makefile
``` bash
make test
```
- Manualmente:
``` bash
bash tests/test.sh
```

## Especificação do protocolo
```
OP A B C...\n
```
Onde:
- `OP ∈ {ADD, SUB, MULT, DIV}`
- `A, B, C` são números reais no formato decimal com ponto (ex.: `2`, `-3.5`, `10.0`).

`ADD A B ... X` : Soma todos os operandos `(A + B + ... + X)` <br>
`SUB A B ... X` : Subtrai todos os operandos `(A - B - ... - X)` <br>
`MULT A B ... X` : Multiplica todos os operandos `(A * B * ... * X)` <br>
`DIV A B ... X` : Divide todos os operandos `(A / B / ... / X)` <br>

### Exemplos
Requisição → Resposta
```
ADD 10 2\n      ->  OK 12\n
SUB 7 9\n      ->  OK -2\n
MULT -3 3.5\n    ->  OK -10.5\n
DIV 5  0\n      ->  ERR divisao_por_zero\n
```

## Exemplo de uso
```
---------------------- MENU -------------------
1. Inserir e enviar operacao ao servidor
2. Sair
------------------------------------------------
Escolha: 1
Digite a expressao que deseja resolver:
ADD 20 10
Resultado: OK 30.000000
---------------------- MENU -------------------
1. Inserir e enviar operacao ao servidor
2. Sair
------------------------------------------------
Escolha: 1
Digite a expressao que deseja resolver:
DIV 5 0
Resultado: ERR divisao_por_zero
```
