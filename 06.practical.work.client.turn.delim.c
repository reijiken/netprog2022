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
  char message[1000];
  char response[1000];
  char str[1000];

  while(1){
        printf("Enter a message: ");
        fgets(message,sizeof(message),stdin);
        send(sockfd , message , strlen(message) + 1, 0); 

        recv(sockfd, response, sizeof(response), 0);
        int i=0;
        do {
            str[i]= response[i];
        } while (response[i++] != '\0');
        printf("%s\n", str); 
        
        if ((strncmp(response , "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
 return 0;     
}