#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static bool stop = false;

static void handle_term(int sig){
    stop = true;
}

int main(int argc, char* argv[]){
    signal(SIGTERM, handle_term);

    if(argc <= 3){
        printf("usage: %s ip_address port_number backlog\n",
                basename(argv[0]));
        return 1;
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    /*创建一个IPv4 socket地址*/
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    // inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
    address.sin_port = htons(port);

    int ret = bind(sockfd, (sockaddr*)&address, sizeof(sockaddr));
    assert(ret != -1);

    ret = listen(sockfd, backlog);
    assert(ret != -1);

    /* 循环等待连接，直到有SIGTERM信号将它中断 */
    while(!stop){
        sleep(1);

    }

    /* 关闭socket */
    close(sockfd);
    return 0;

}