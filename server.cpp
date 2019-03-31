#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

bool add(int client,struct sockaddr);
bool send_info(int client);
void listen_ip(size_t ip ,size_t port );

struct data
{
    int x,y,z;
    unsigned int health;
    unsigned dest;
};

map<int,data> clients;

int main(int argc,char ** argv)
{
        
    return 0;
}

void listen_ip(size_t ip = INADDR_LOOPBACK,size_t port = 9999)
{
    
    int listener = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sa;
    struct sockaddr cls;
    unsigned int * length;

    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    // inet_pton(AF_INET,'0.0.0.0',&(sa.sin_addr)); 
    sa.sin_addr.s_addr = htonl(ip);

    if (bind(listener,(struct sockaddr *)&sa,sizeof(sa)) < 0)
    {
        cout << "bind error" << endl; 
        return;
    }

    listen(listener,SOMAXCONN);
    while (1)
    {
        int client = accept(listener,&cls, length);
        add(client,cls);
        send_info(client);
        
    }

}

bool add(int client,struct sockaddr)
{
    //clients.push_back(client);
    data d;
    int pos = clients.size()-1;
    recv(client,&d,sizeof(data),MSG_NOSIGNAL);
    send(client,&client,sizeof(int),MSG_NOSIGNAL);
    clients.insert(pair<int,data>(client,d));
}

bool send_info(int client)
{
    send(client,&clients,clients.size()*sizeof(data) * sizeof(int),MSG_NOSIGNAL);
}
