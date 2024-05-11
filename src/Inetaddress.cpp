#include "Inetaddress.h"
#include <stdio.h>
#include <string.h>


Inetaddress::Inetaddress():len(sizeof(addr)){
    bzero(&addr, sizeof(addr));
}

Inetaddress::Inetaddress(const char * ip, uint16_t port):len(sizeof(addr)){
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_family = AF_INET;      // 默认IPv4
    addr.sin_port = htons(port);
}

Inetaddress::~Inetaddress(){
}

sockaddr * get_sockaddr(){
    return (sockaddr *) &addr;
}

sockaddr_in * get_sockaddr_in(){
    return &addr;
}

socklen_t Inetaddress::get_addr_len(){
    return sizeof(addr);
}

