#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string.h>


int main(){
    const char * ip = "192.168.235.128";
    int port = atoi("6666");

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);

    inet_pton(AF_INET, ip, &addr.sin_addr.s_addr);

    std::cout <<"inet_addr(ip): " << inet_addr(ip) << std::endl ;
    std::cout <<"inet_pton(ip): " << addr.sin_addr.s_addr << std::endl;
    std::cout <<"port: " << htons(port) << std::endl ;

}

