/*UDP c AF_LOCAL*/
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/un.h>
#include<stdlib.h>
#include <stdio.h>
#define N 14

#define FILE "local"

void errorExit(char err[]);

void errorExit(char err[]){
    perror(err);
    exit(EXIT_FAILURE);
}

int main(){
    int fd;
    struct sockaddr_un serv, client;
    char buff[N];
    socklen_t len;
 
    fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(fd == -1)
        errorExit("sock");
        

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILE);

    if(bind(fd, (struct sockaddr*)&serv, sizeof(serv)) == -1)
        errorExit("bind");
       
    len = sizeof(client);
    if(recvfrom(fd, buff, N, 0, (struct sockaddr*)&client, &len) == -1)
        errorExit("recvfrom");
        

    printf("%s\n", buff);
    strcpy(buff, "Hello, client");
    
    if(sendto(fd, buff, N, 0, (struct sockaddr*)&client, sizeof(client)) == -1)
        errorExit("sendto");
        
    close(fd);
    exit(EXIT_SUCCESS);
}