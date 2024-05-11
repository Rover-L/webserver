#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "util.h"

int main(){

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.235.128");
    serv_addr.sin_port = htons(8888);

    connect(sock_fd, (sockaddr*)&serv_addr, sizeof(sockaddr));

    /* 传输数据 */
    while(true){
        char buffer[1024];
        bzero(&buffer, sizeof(buffer));
        // scanf("Message: %s", buffer);       // 【未解决】""中的字符会影响buffer中的值！
        scanf("%s", buffer);
        ssize_t write_len = write(sock_fd, buffer, sizeof(buffer));
        
        if(write_len == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }

        bzero(&buffer, sizeof(buffer));
        ssize_t read_bytes = read(sock_fd, buffer, sizeof(buffer));
        if(read_bytes > 0){
            printf("message from server: %s\n", buffer);
        }else if(read_bytes == 0){
            printf("server socket disconnected!\n");
            break;
        }else if(read_bytes == -1){
            close(sock_fd);
            errif(true, "socket read error");
        }
    }
    
    close(sock_fd);
    return 0;
}


