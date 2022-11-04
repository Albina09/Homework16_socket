/*UDP c AF_LOCAL*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<string.h>
 
#define N 14

#define FILE "local"
void errorExit(char err[]);

void errorExit(char err[]){
    perror(err);
    exit(EXIT_FAILURE);
}
 
int main(){
    int fd;
    char buff[N];
    struct sockaddr_un serv, client;
    strcpy(buff, "Hello, server");
    
    fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(fd == -1)
        errorExit("sock");
        
    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, FILE);
    client.sun_family = AF_LOCAL;
    strcpy(client.sun_path, "local2");
    unlink(client.sun_path);

    if(bind(fd, (struct sockaddr*)&client, sizeof(client)) == -1)
        errorExit("bind");
        
    if(sendto(fd, buff, N, 0, (struct sockaddr*)&serv, sizeof(serv)) == -1)
        errorExit("sendto");
        
    if(recvfrom(fd, buff, N, 0, NULL, NULL) == -1)
        errorExit("recvfrom");
        
    printf("%s\n", buff);
    
    close(fd);
    unlink("local");
    unlink("local2");
    
    exit(EXIT_SUCCESS);
}