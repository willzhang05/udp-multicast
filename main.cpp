#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using std::cout;
using std::endl;
using std::memset;

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("error creating socket");
        return 1;
    }
    struct hostent *hp;
    struct sockaddr_in servaddr;
    char *message = "ayy lmao";

    memset((char *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(0);
    
    char *host = "localhost";
    hp = gethostbyname(host);
    if (!hp) {
        fprintf(stderr, "couldn't get the address of %s\n", host);
        return 1;
    }
    memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

    /*int b = bind(s, (struct sockaddr *)&addr, sizeof(servaddr));
    if (b < 0) {
        perror("error binding");
        return 1;
    }*/

    int st = sendto(s, message, strlen(message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (st < 0) {
        perror("sendto failed");
        return 1;
    }
    
    return 0;
}
