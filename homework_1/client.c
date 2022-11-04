/*TCP c AF_LOCAL*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

#define FILE "local"

void errorExit(char err[]);

void errorExit(char err[]){
    perror(err);
    exit(EXIT_FAILURE);
}

int main(){
    struct sockaddr_un serv;
    char buff[14];
    socklen_t len;
    strcpy(buff, "Hello, server");

    int fd = socket(AF_LOCAL,SOCK_STREAM,0);
    if(fd == -1)
        errorExit("soket");
        

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILE);

    len = sizeof(serv);
    if (connect(fd, (struct sockaddr *)&serv, len) == -1) 
        errorExit("accept");
        
    if(send(fd, buff, sizeof(buff), 0) == -1) 
        errorExit("send");
        
    if (recv(fd, buff, sizeof(buff), 0) == -1) 
        errorExit("recv");
        
    printf("%s\n", buff);

    close(fd);

}