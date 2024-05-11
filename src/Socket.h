#pragma once
#include "Inetaddress.h"

class Socket{
private:
    int sock_fd;

public:
    Socket();
    ~Socket();

    void listen();
    void bind(Inetaddress *);
    void setNonblock();
    int accept(Inetaddress *);
    int getFd();
};