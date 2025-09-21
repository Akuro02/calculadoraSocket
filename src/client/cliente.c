#include "../../include/clienteProto.h"

#define defaultIP "127.0.0.1"
#define defaultPort 5050



int main(int argc, char* argv[]){
    char serverIP[] = defaultIP; // IP default
    int port = defaultPort; // porta default

    if (argc >= 2){
        port = atoi(argv[1]);
    }
    if (argc >= 3){
        strcpy(serverIP, argv[2]);
    }

    printf("IP: %s\nPorta: %i\n", serverIP, port);

    // Criação do socket
    int client_socket = socketCreateAndConnect(serverIP, port);
    if (client_socket < 0){
        return -1;
    }

    while(1){
        showMenu();
        int option;
        if (scanf("%d", &option) != 1){
            printf("Input invalido\n");
            return -1;
        }
        switch (option){
            case 1:
                calculator(client_socket);
                break;
            case 2:
                exit(0);
            default:
                printf("Expressao invalida, tente novamente\n");
        }
    }
    
    return 0;
}




