all: server client

server: src/server/servidor.c src/server/serverProto.c
	gcc src/server/servidor.c src/server/serverProto.c -o server 

client: src/client/cliente.c src/client/clientProto.c
	gcc src/client/cliente.c src/client/clientProto.c -o client

clean:
	rm -f server client