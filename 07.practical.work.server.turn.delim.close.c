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
    while(1){

            recv(clientfd, message , sizeof(message),0); //from client
            int i=0;
            do {
                str[i]= message[i]; 
            } while(str[i++] != '\0');

            printf("%s\n", str); //to STDOUT 

            printf("Enter a message:");
            fgets(response, sizeof(response),stdin);  //from STDIN
            if (strncmp("/dc\n", response , 4) == 0) {
                printf("Client is disconnected.\n");
                return 0;
            }
            send(clientfd, response , strlen(response) + 1, 0); //to client
        }
    return 0;
}
