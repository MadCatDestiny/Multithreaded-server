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
void listen_ip(size_t ip = htonl(INADDR_LOOPBACK),size_t port = htons(9999))

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

void listen_ip(size_t ip = htonl(INADDR_LOOPBACK),size_t port = htons(9999))
{
    int listener = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sa;
    struct sockaddr cls;
    int * length

    sa.sin_family = AF_INET;
    sa.sin_port = port;
    // inet_pton(AF_INET,'0.0.0.0',&(sa.sin_addr)); 
    sa.sin_addr.s_addr = ip;

    if (bind(listener,(struct sockaddr *)&sa,sizeof(sa)) < 0)
    {
        cout << "bind error" << endl; 
        return 1;
    }

    listen(listener,SOMAXCONN);
    while (1)
    {
        int client = accept(listener,&cls, length)
        add(client,cls);
        send_info(client);
        
    }

}

bool add(int client,struct sockaddr)
{
    //clients.push_back(client);
    data d;
    int pos = clients.size()-1;
    recv(client,&d,sizeof(data),0);
    send(client,client,sizeof(int));
    clients.push_back(map<int,data>(client,d);
}

bool send_info(int client)
{
    send(client,ref(clients),clients.size()*sizeof(data) * sizeof(int));
}
