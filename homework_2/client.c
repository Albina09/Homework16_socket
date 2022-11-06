/*TCP c AF_INIT*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>



int main(){
    struct sockaddr_in serv;
    char buff[14];
    socklen_t len;
    strcpy(buff, "Hello, server");

    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("soket");
        exit(EXIT_FAILURE);
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(9002);
    serv.sin_addr.s_addr = htons(INADDR_ANY);

    len = sizeof(serv);
    if (connect(fd, (struct sockaddr *)&serv, len) == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    if(send(fd, buff, sizeof(buff), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    if (recv(fd, buff, sizeof(buff), 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    printf("%s\n",buff);

    close(fd);
    exit(EXIT_SUCCESS);
}
