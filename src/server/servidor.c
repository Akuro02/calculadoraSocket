#include "../../include/serverProto.h"

#include <signal.h>

#define defaultIP "127.0.0.1"
#define defaultPort 5050

void handleSignal(int sig){
    printf("\nServidor interrompido\n");
    exit(sig);
}

int main(int argc, char* argv[]) {
    signal(SIGINT, handleSignal);

    int port = defaultPort; // porta padrao
    char IPAddr[] = defaultIP;
    if (argc >= 2){
        port = atoi(argv[1]); // porta alterada pelo cliente
    }
    if (argc >= 3){
        strcpy(IPAddr, argv[2]);
    }
    // Criação do socket
    int server_socket = socketCreateAndConnect(IPAddr, port);
    if (server_socket < 0){
        return -1;
    }
    // Server extrai o primeiro pedido de conexao da fila, cria um novo socket conectado e retorna um novo file descriptor para aquele socket.
    while(1){
        printf("Conectando ao cliente\n");
        int client_socket = accept(server_socket, NULL, NULL);
        printf("Cliente conectado\n");
        while(1){
            printf("Client: %i\n", client_socket);
            char buffer[256];
            int recv_status = receiveMessage(client_socket, buffer, sizeof(buffer));
            if (recv_status < 0){
                break;
            }
            
            
            solveAndRespond(client_socket, buffer);
        }
    }
    printf("Closed\n");
    close(server_socket);
}

