#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

int main(){

    int lisfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.235.128");
    serv_addr.sin_port = htons(7777);

    bind(lisfd, (sockaddr*)&serv_addr, sizeof(sockaddr));

    listen(lisfd, SOMAXCONN);

    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    
    socklen_t clisock_len = sizeof(client_addr);

    int client_fd = accept(lisfd, (sockaddr*)&client_addr, &clisock_len);
    errif(client_fd == -1, "accept error!");

    /* 输出客户端IP地址以及端口号 */
    printf("client ip: %s, port: %d; \n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    while(true){
        char buffer[1024];
        bzero(&buffer, sizeof(buffer));
        ssize_t read_len = read(client_fd, buffer, sizeof(buffer));
        if(read_len > 0){
            printf("message  form client with ip: %s, port: %d :%s\n", 
                    inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
            // /*  ***【未解决】*******两次写会产生错误！！******** */
            // const char * mas = "Server receved message! ";
            // sleep(1);
            // write(client_fd, &mas, sizeof(mas));
            write(client_fd, buffer, sizeof(buffer));
        }else if(read_len == 0){
            printf("client fd %d disconnected!", client_fd);
            close(client_fd);
            break;
        }else if(read_len == -1){
            close(client_fd);
            errif(1, "socket read error!");
        }
    } 

    close(lisfd);

    return 0;

}


