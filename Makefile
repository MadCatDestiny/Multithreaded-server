CC = g++ -std=c++11 -lpthread
all:server,client
b_server:
	$(CC) -o server server.cpp
server:b_server
	./server
b_client:
	$(CC) -o client client.cpp
client:
	./client
