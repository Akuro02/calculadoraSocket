#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

typedef enum Stat{
    OK,
    DIV_ZERO,
    INVALID_OP,
    MISSING_VAl
} Status;

typedef struct {
    double result;
    Status status;
} ExpressionResult;

ExpressionResult solveExpression(char *buffer);
ExpressionResult add(char* tokens);
ExpressionResult sub(char* tokens);
ExpressionResult mult(char* tokens);
ExpressionResult divi(char* tokens);
void sendMessage(ExpressionResult result, int client_socket);

int socketCreateAndConnect(char serverIP[], int port);

int receiveMessage(int client_socket, char* buffer, ssize_t buffer_size);

void solveAndRespond(int client_socket, char* buffer);

