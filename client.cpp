#include <iostream>
#include <map>
#include <ctime>
#include <thread>
#include <chrono>
#include "data.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
data d;
int main()
{
    int sck = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(9999);
    // inet_pton(af_inet,'0.0.0.0',&(sa.sin_addr)); 
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect (sck,(struct sockaddr*)&sa,sizeof(sa)) < 0)
    {
        cout << "Connect  failed"<<endl;
        return 1;
    }
    int pos;
    recv(sck,&pos,sizeof(int),MSG_NOSIGNAL);
    recv(sck,&d,sizeof(data),MSG_NOSIGNAL);
    srand(time(0));
    while (1)
    {
        d.x = d.x + rand()%10; 
        d.y = d.y + rand()%10;
        d.z = d.z + rand()%10;
        cout <<"client: "<< d.x << " " << d.y << " " << d.z <<endl;
        send(sck,&d,sizeof(data),MSG_NOSIGNAL);
        //this_thread::sleep_for(chrono::second(1));
        char c;
        cin >> c;
        if (c=='q')
            return 0;
    }
    return 0;
}
