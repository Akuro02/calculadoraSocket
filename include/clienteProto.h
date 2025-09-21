#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void showMenu(); // mostra o menu de opcoes
void calculator(int client_socket); // funcao principal da calculadora

//Prototipos de funcoes de socket
int socketCreateAndConnect(char* serverIP, int port); // cria o socket e conecta ao servidor
int sendExpression(int client_socket); // envia a expressao ao servidor
void receiveResult(int client_socket, char buffer[256], int size); // recebe o resultado do servidor