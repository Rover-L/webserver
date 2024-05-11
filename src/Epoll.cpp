#include "Epoll.h"
#include "errorIf.h"
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>

Epoll::Epoll(){
    epfd = epoll_create(1);
    errorIf(epfd == -1, "epoll create error!");
}

Epoll::~Epoll(){
    if(epfd != -1){
        close(epfd);
    }
}