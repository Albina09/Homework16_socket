/*TCP c AF_INIT*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

void errorExit(char err[]);

void errorExit(char err[]){
    perror(err);
    exit(EXIT_FAILURE);
}

int main(){
    int fd, new_fd;
    struct sockaddr_in serv, client;
    char buff[14];
    socklen_t len;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
        errorExit("soket");
        
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9002);
    serv.sin_addr.s_addr = htons(INADDR_ANY);

    if (bind(fd, (struct sockaddr *)&serv, sizeof(serv)) == -1) 
        errorExit("bind");
        
    if (listen(fd, 5) == -1) 
        errorExit("listen");
    
    len = sizeof(client);
    new_fd = accept(fd,(struct sockaddr *)&client, &len);

    if (recv(new_fd, buff, sizeof(buff), 0) == -1) 
        errorExit("recv");
    printf("%s\n", buff);
    strcpy(buff, "Hello, client");

    if(send(new_fd, buff, sizeof(buff), 0) == -1)
        errorExit("send");

    close(new_fd);
    close(fd);

    exit(EXIT_SUCCESS);
}