#include "../../include/clienteProto.h"


void showMenu(){
    printf("---------------------- MENU -------------------\n"
            "1. Inserir e enviar operacao ao servidor\n"
            "2. Sair\n"
            "------------------------------------------------\n"
            "Escolha: ");
}

void calculator(int client_socket){
    char solved[256];
    getchar(); // Tratando o /n que sobra do scanf
    sendExpression(client_socket);
    receiveResult(client_socket, solved, sizeof(solved));
    printf("%s\n", solved);
}

// FUNCOES DE SOCKET

int socketCreateAndConnect(char* serverIP, int port){
    // Criação do socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Erro ao criar o socket");
        return -1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // Definindo a família do socket -> AF_INET sao endereços IPv4
    server_address.sin_port = port; // Definindo a porta do servidor
    server_address.sin_addr.s_addr = inet_addr(serverIP); // definindo o endereço IP do servidor || 127.0.0.1 é o endereço de loopback (localhost)

    // conectando ao servidor

    if(connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        printf("Erro ao conectar com servidor. Verifique se ele esta ligado ou se os dados de socket internet de ambos se correspodem\n");
        return -1;
    }

    printf("Conectado ao servidor no IP %s, na porta %i\n", serverIP, port);

    return client_socket;
}

int sendExpression(int client_socket){ // FUNCAO QUE ENVIA A EXPRESSAO AO SERVIDOR
    // Criando o buffer e lendo a expressao
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    printf("Digite a expressao que deseja resolver:\n");
    if (fgets(buffer, 256, stdin) == NULL){
        printf("Erro ao ler expressao\n");
        return -1;
    }
    // Enviando a expressao ao servidor
    send(client_socket, buffer, sizeof(buffer), 0);
}

void receiveResult(int client_socket, char buffer[256], int size){ // FUNCAO QUE RECEBE O RESULTADO DO SERVIDOR
    memset(buffer, 0, size);
    recv(client_socket, buffer, size, 0); // Recebendo o resultado do servidor
    printf("Resultado: ");
} 



