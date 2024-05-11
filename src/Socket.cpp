#include "Socket.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "errorIf.h"
#include <fcntl.h>

Socket::Socket(){
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    errorIf(sock_fd == -1, "socket create error!");
}

Socket::~Socket(){
    if(sock_fd != -1){
        close(sock_fd);
        sock_fd = -1;
    }
}

void Socket::listen(){
    int ret = ::listen(sock_fd, SOMAXCONN);
    errorIf(ret == -1, "socket listen error!");
}

void Socket::bind(Inetaddress * sock_addr){
    int ret = ::bind(sock_fd, sock_addr->get_sockaddr(), sock_addr->get_addr_len());
    errorIf(ret == -1, "socket bind error!");
}

int  Socket::accept(Inetaddress * clnt_addr){
    int clnt_fd = ::accept(sock_fd, clnt_addr->get_sockaddr(), (socklen_t *)clnt_addr->get_addr_len());
    errorIf(clnt_fd == -1, "socket accept error!");
    return clnt_fd;
}

void Socket::setNonblock(){
    int flag = fcntl(sock_fd, F_GETFL);
    fcntl(sock_fd, F_SETFL, flag | O_NONBLOCK);
}

int Socket::getFd(){
    return sock_fd;
}