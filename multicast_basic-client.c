#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv)
{
    SOCKET sd;
    struct sockaddr_in serv, cli;
    int n, serv_len;
    int flag=1, len=sizeof(int);
    char str[MAXLINE];

    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    BOOL broadcast = TRUE;
    if( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, len) <0 )
        printf("setsockopt() failed");

    cli.sin_family = AF_INET;
    cli.sin_addr.s_addr = 0;
    cli.sin_port = htons(5678);

    if( bind(sd, (LPSOCKADDR) &cli, sizeof(cli)) <0 )
       printf("bind error!\n");

    struct ip_mreq multicastRequest; /* Multicast address join structure */
    multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.1"); /* Specify the multicast group */
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY); /* Accept multicast from any interface */

    /* Join the multicast address */
    if( setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char *) &multicastRequest,sizeof(multicastRequest)) <0 )
    	printf("setsockopt() failed");

    serv_len = sizeof(serv);
    while(1){
        n = recvfrom(sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, &serv_len);
        str[n] = '\0';
        printf("client(from:%s):%s\n", inet_ntoa(serv.sin_addr), str);
    }

    closesocket(sd);
    WSACleanup();

    return 0;
}
