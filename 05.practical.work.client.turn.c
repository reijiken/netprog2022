#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
  struct sockaddr_in saddr;
  struct hostent *h;
  struct in_addr *address;
  int sockfd;
  unsigned short port = 8784;

  if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Error creating socket\n");
    return 1;
    }
  char input[100];     
  if (argc > 1){
    strcpy(input, argv[1]);
    }
  else{
    printf("Enter a name: ");
    scanf("%s", input);
    }
  printf("The domain is : %s\n",input);
  h=gethostbyname(input);
  address = (struct in_addr*) (h->h_addr);
  printf("%s has address %s\n",input,inet_ntoa(*address));
  if (h == NULL){
    printf("Unknown host !!!\n");
    return 0;
    }

  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  saddr.sin_port = htons(port);
  
  if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
    printf("Cannot connect \n");
    return 1;
    }
  printf("Server connected.\n");
  char buf[1024];
  while(1){
    printf("Enter a command: ");
    fgets(buf, sizeof(buf), stdin);
    if(strncmp(buf, "exit", 4) == 0)
    {
        break;
    }
    if(send(sockfd, buf, strlen(buf), 0) == -1)
    {
        perror("send");
        return 1;
    }
    if(recv(sockfd, buf, sizeof(buf), 0) == -1)
    {
        perror("recv");
        return 1;
    }
    printf("%s", buf);
    }
 return 0;     
}