#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
int sockfd, clen, clientfd;
struct sockaddr_in saddr, caddr;
unsigned short port = 8784;
if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
printf(“Error creating socket\n”);
}
memset(&saddr, 0, sizeof(saddr));
saddr.sin_family = AF_INET;
saddr.sin_addr.s_addr = htonl(INADDR_ANY);
saddr.sin_port = htons(port);
if ((bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
printf(“Error binding\n”);
}
if (listen(sockfd, 5) < 0) {
printf(“Error listening\n”);
}
else {
    printf("listen to port : %d\n", port);
}
clen=sizeof(caddr);
if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
printf(“Error accepting connection\n”);
}
Socket P