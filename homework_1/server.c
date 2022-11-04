/*TCP c AF_LOCAL*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define FILE "local"

void errorExit(char err[]);

void errorExit(char err[]){
    perror(err);
    exit(EXIT_FAILURE);
}

int main(){
    struct sockaddr_un serv, client;
    char buff[14]; 
    socklen_t len;
    int fd, new_fd;

    fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(fd == -1)
        errorExit("soket");
        

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILE);

    if (bind(fd, (struct sockaddr *)&serv, sizeof(serv)) == -1) 
        errorExit("bind");
        
    if (listen(fd, 5) == -1) 
        errorExit("listen");
        
    len = sizeof(client);

    new_fd = accept(fd, (struct sockaddr *)&client, &len);
    if (new_fd == -1)
        errorExit("accept");
        
    if (recv(new_fd, buff, sizeof(buff), 0) == -1)
        errorExit("recv");
    printf("%s\n",buff);
    strcpy(buff, "Hello, client");

    if(send(new_fd, buff, sizeof(buff), 0) == -1)
        errorExit("send");
    
    close(new_fd);
    close(fd);
    exit(EXIT_SUCCESS);
}