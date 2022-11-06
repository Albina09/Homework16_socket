/*UDP c AF_INIT*/
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
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1)
        errorExit("soket");

    serv.sin_family = AF_INET;
    serv.sin_port = htons(9003);
    serv.sin_addr.s_addr = htons(INADDR_ANY);

    if (bind(fd, (struct sockaddr *)&serv, sizeof(serv)) == -1)
        errorExit("bind");

    int size = sizeof(client);

    if (recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr *)&client, &size) == -1)
        errorExit("recvfrom");
        
    printf("%s\n",buff);
    strcpy(buff, "Hello, client");

    if(sendto(fd, buff, sizeof(buff), 0, (struct sockaddr *)&client, size) == -1)
        errorExit("sendto");

    close(fd);
    exit(EXIT_SUCCESS);
}