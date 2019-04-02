#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <map>
#include <vector>
#include "data.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

bool add(int client);
//bool send_info(int client);
void listen_ip(size_t ip ,size_t port );
void client_handler(int client);

map<int,data> clients;
vector <int> clients_id;
mutex cl_m;

int main(int argc,char ** argv)
{
    thread t(listen_ip,INADDR_LOOPBACK,9999);
    t.detach();
    while (1)
    {
        char c;
        cin >> c;
        if (c=='q')
            return 0;
    }

    return 0;
}

void listen_ip(size_t ip ,size_t port )
{
    
    int listener = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sa;
    struct sockaddr cls;
    unsigned int * length;

    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    // inet_pton(af_inet,'0.0.0.0',&(sa.sin_addr)); 
    sa.sin_addr.s_addr = htonl(ip);

    if (bind(listener,(struct sockaddr *)&sa,sizeof(sa)) < 0)
    {
        cout << "bind error" << endl; 
        return;
    }

    listen(listener,SOMAXCONN);
    cout << "Server listen" << endl;

    while (1)
    {
        int client = accept(listener,&cls, length);
        cout << "New client" <<endl;
        unique_lock<mutex> lock(cl_m);
        add(client);
        send(client,&clients,clients.size()*sizeof(data) * sizeof(int),MSG_NOSIGNAL);
        thread t(client_handler,client);    
        t.detach();        
    }

}

bool add(int client)
{
    //clients.push_back(client);
    data d;
    recv(client,&d,sizeof(data),MSG_NOSIGNAL);
    send(client,&client,sizeof(int),MSG_NOSIGNAL);
    unique_lock<mutex> lock(cl_m);
    clients.insert(pair<int,data>(client,d));
    clients_id.push_back(client);
}

/*bool send_info(int client)
{
    unique_lock<mutex> lock(cl_m);
    send(client,&clients,clients.size()*sizeof(data) * sizeof(int),MSG_NOSIGNAL);
}*/

void client_handler(int client)
{
    data d;
    while (1)
    {
        unique_lock<mutex> lock(cl_m);
        recv(client,&d,sizeof(data),MSG_NOSIGNAL);
        clients[client] = d;
        cout <<"client-" << client << " : "<< d.x << " " << d.y << " " << d.z <<endl;
        send(client,&clients,clients.size()*sizeof(data) * sizeof(int),MSG_NOSIGNAL);

    }
}
