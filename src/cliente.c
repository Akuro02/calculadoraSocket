#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define defaultIP "127.0.0.1"
#define defaultPort 5050

void showMenu();
int sendExpression(int client_socket);

int main(int argc, char* argv[]){
    char serverIP[] = defaultIP; // IP default
    int port = defaultPort; // porta default

    if (argc >= 2){
        port = atoi(argv[1]);
    }
    if (argc >= 3){
        strcpy(serverIP, argv[2]);
    }

    printf("%s\n%i\n", serverIP, port);

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

    if(connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        printf("Erro ao conectar com servidor. Verifique se ele esta ligado ou se os dados de socket internet de ambos se correspodem\n");
        return -1;
    }

    printf("Conectado ao servidor no IP %s, na porta %i\n", serverIP, port);

    while(1){
        showMenu();
        int option;
        if (scanf("%d", &option) != 1){
            printf("Input invalido\n");
            return -1;
        }
        switch (option){
            case 1:
                char solved[256];
                memset(solved, 0, sizeof(solved));
                getchar(); // Tratando o /n que sobra do scanf
                sendExpression(client_socket);
                recv(client_socket, solved, sizeof(solved), 0);
                printf("%s\n", solved);
                break;
            case 2:
                exit(0);
            default:
                printf("Expressao invalida, tente novamente\n");
        }
    }
    
    return 0;
}


int sendExpression(int client_socket){
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    printf("Digite a expressao que deseja resolver:\n");
    if (fgets(buffer, 256, stdin) == NULL){
        printf("Erro ao ler expressao\n");
        return -1;
    }
    send(client_socket, buffer, sizeof(buffer), 0);
}


void showMenu(){
    printf("---------------------- MENU -------------------\n"
            "1. Inserir e enviar operacao ao servidor\n"
            "2. Sair\n"
            "------------------------------------------------\n"
            "Escolha: ");
}
