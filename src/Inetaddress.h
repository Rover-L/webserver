#pragma once
#include <arpa/inet.h>

class Inetaddress{
public:
    struct sockaddr_in addr;
    socklen_t len;
    

public:
    Inetaddress();
    Inetaddress(const char*, uint16_t);
    ~Inetaddress();
    sockaddr * get_sockaddr();
    // sockaddr_in * get_sockaddr_in();
    // socklen_t get_addr_len();

};