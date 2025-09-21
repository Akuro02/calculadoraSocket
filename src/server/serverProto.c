#include "../../include/serverProto.h"


// FUNCOES DE CALCULADORA

ExpressionResult solveExpression(char *buffer){
    char *tokens = strtok(buffer, " ");
    char* operator = tokens;
    if (operator == NULL){
        return (ExpressionResult){0, INVALID_OP};
    }
    if (strcmp(operator, "ADD") == 0){return add(strtok(NULL, " "));}
    else if (strcmp(operator, "SUB") == 0){return sub(strtok(NULL, " "));}
    else if (strcmp(operator, "MULT") == 0){return mult(strtok(NULL, " "));}
    else if (strcmp(operator, "DIV") == 0){return divi(strtok(NULL, " "));}
    else{return (ExpressionResult){0, INVALID_OP};}
}

ExpressionResult add(char* tokens){
    printf("SOMA\n");
    ExpressionResult result = {0, MISSING_VAl};
    while(tokens != NULL){
        result.result += atof(tokens);
        result.status = OK;
        tokens = strtok(NULL, " ");
    }
    return result;
}


ExpressionResult sub(char* tokens){
    printf("SUBTRACAO\n");
    ExpressionResult result = {0, MISSING_VAl};
    if (tokens == NULL){
        return result;
    }
    result.status = OK;
    result.result = atof(tokens);
    tokens = strtok(NULL, " ");
    while(tokens != NULL){
        result.result -= atof(tokens);
        tokens = strtok(NULL, " ");
    }
    return result;
}

ExpressionResult mult(char* tokens){
    printf("MULTIPLICACAO\n");
    ExpressionResult result = {0, MISSING_VAl};
    if (tokens == NULL){
        return result;
    }
    result.status = OK;
    result.result = atof(tokens);
    tokens = strtok(NULL, " ");
    while(tokens != NULL){
        result.result *= atof(tokens);
        tokens = strtok(NULL, " ");
    }
    return result;
}

ExpressionResult divi(char* tokens){
    printf("DIVISAO\n");
    ExpressionResult result = {0, MISSING_VAl};
    if (tokens == NULL){
        return result;
    }
    result.status = OK;
    result.result = atof(tokens);
    tokens = strtok(NULL, " ");
    while(tokens != NULL){
        double divisor = atof(tokens);
        if (divisor == 0){
            result.status = DIV_ZERO;
            return result;
        }
        result.result /= divisor;
        tokens = strtok(NULL, " ");
    }
    return result;
}

// FUNCOES DE SOCKET

int socketCreateAndConnect(char serverIP[], int port){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0); // Socket -> AF_INET = IPv4 | SOCK_STREAM = TCP | 0 = protocolo padrao para TCP
    if (server_socket < 0) {
        perror("Erro ao criar o socket");
        return -1;  
    }

    printf("%s\n%i\n", serverIP, port);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = port;
    server_address.sin_addr.s_addr = inet_addr(serverIP);

    // ligar o socket ao endereco e porta especificada.
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Colocar o socket de servidor em modo passivo, ou seja, ele espera o cliente fazer a conexao
    listen(server_socket, 5);

    return server_socket;
}

int receiveMessage(int client_socket, char buffer[], ssize_t buffer_size){
    memset(buffer, 0, buffer_size);
    ssize_t message = recv(client_socket, buffer, buffer_size, 0);
    if (message <= 0){
        printf("Cliente desconectou\n");
        close(client_socket);
        return -1;
    }
    printf("Mensagem recebida: %s\n", buffer);
}

void solveAndRespond(int client_socket, char* buffer){
    ExpressionResult result = solveExpression(buffer);
    sendMessage(result, client_socket);
}

void sendMessage(ExpressionResult result, int client_socket){
    printf("ENVIANDO MENSAGEM\n");
    char message[256];
    memset(message, 0, sizeof(message));
    switch (result.status){
        case OK:
            sprintf(message, "OK %.6f", result.result);
            break;
        case DIV_ZERO:
            strcpy(message, "ERR divisao_por_zero");
            break;
        case INVALID_OP:
            strcpy(message, "ERR operador_invalido");
            break;
        case MISSING_VAl:
            strcpy(message, "ERR falta_operadores");
        default:
            strcpy(message, "ERR");
    }
    send(client_socket, message, strlen(message), 0);
}