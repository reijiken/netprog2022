#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    struct hostent *host;
    struct in_addr *address;
    
    char input[100];
        
    strcpy(input,argv[1]);
    printf("The domain is : %s\n",input);
    host=gethostbyname(input);
    address = (struct in_addr*) (host->h_addr);
    printf("%s has address %s\n",input,inet_ntoa(*address));
}