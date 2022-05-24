#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <pthread.h>

#define MAXLINE 1024
#define BraodcastPort 5678

SOCKET sd;
struct sockaddr_in serv, cli;
int serv_len, cli_len;
int n, channel=1, timeout=50;
int flag=1, len=sizeof(int);
char str[MAXLINE];
char str_r[MAXLINE];

void *recvMess(void *argu){
    while(1){
        cli_len = sizeof(cli);
        n = recvfrom(sd, str, MAXLINE, 0, (LPSOCKADDR) &cli, &cli_len );
        if(n > 0)
            printf("client(from:%s):%s, %d\n", inet_ntoa(cli.sin_addr), str, n);
    }
}

int main(void)
{
    int n, i, j, total=0;
    pthread_t thread1;

    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    if( setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, len) <0 )
        printf("setsockopt() failed");

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = 0;
    serv.sin_port = htons(BraodcastPort);

    if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 )
       printf("bind error!\n");

    serv_len = sizeof(serv);

    pthread_create(&thread1, NULL, &recvMess, NULL);

    struct ip_mreq multicastRequest; /* Multicast address join structure */
    multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.1"); /* Specify the multicast group */
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY); /* Accept multicast from any interface */

    /* Join the multicast address */
    while(1){
        scanf("%d", &channel);
        printf("Switch to channel %d\n", channel);
        switch(channel){
            case 1:
                multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.1");
                if( setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char *) &multicastRequest,sizeof(multicastRequest)) <0 )
                    printf("setsockopt() failed");
                break;
            case 2:
                multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.1");
                if( setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char *) &multicastRequest,sizeof(multicastRequest)) <0 )
                    printf("setsockopt() failed");
                break;
            case 3:
                multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.2");
                if( setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char *) &multicastRequest,sizeof(multicastRequest)) <0 )
                    printf("setsockopt() failed");
                break;
            case 4:
                multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.2");
                if( setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char *) &multicastRequest,sizeof(multicastRequest)) <0 )
                    printf("setsockopt() failed");
                break;
            case 5:
                multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.3");
                if( setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char *) &multicastRequest,sizeof(multicastRequest)) <0 )
                    printf("setsockopt() failed");
                break;
            case 6:
                multicastRequest.imr_multiaddr.s_addr = inet_addr("224.1.1.3");
                if( setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char *) &multicastRequest,sizeof(multicastRequest)) <0 )
                    printf("setsockopt() failed");
                break;
        }
    }

    closesocket(sd);
    WSACleanup();

    return 0;
}
