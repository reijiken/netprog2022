#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>

int main(){
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;//server addr, client addr 
    unsigned short port = 8784;

    if ((sockfd =  socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        return 1;
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0){
        printf("Error binding\n");  
        return 1;
    }
    if (listen(sockfd, 5) < 0){
        printf("Error listening\n");  
        return 1;
    }
    clen = sizeof(caddr);
    if ((clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error accepting connection\n"); 
        return 1;
    }
    printf("Client is connected.\n");
       char buf[1024];
    while(1)
    {
        if(recv(clientfd, buf, sizeof(buf), 0) == -1)
        {
            perror("recv");
            return 1;
        }      
        printf("%s", buf);
        printf("Enter a command: ");
        fgets(buf, sizeof(buf), stdin);
        if(strncmp(buf, "exit", 4) == 0)
        {
            break;
        }
        if(send(clientfd, buf, strlen(buf), 0) == -1)
        {
            perror("send");
            return 1;
        }
    }
    return 0;
}