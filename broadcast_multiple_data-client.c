#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024
#define BraodcastPort 5678

int main(int argc, char** argv)
{
    SOCKET sd;
    struct sockaddr_in serv, cli;
    int n, serv_len;
    char str[1024];

    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    BOOL broadcast = TRUE;
    if( setsockopt(sd, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcast, sizeof(broadcast)) <0 )
        printf("setsockopt() error!\n");

    cli.sin_family = AF_INET;
    cli.sin_addr.s_addr = 0;
    cli.sin_port = htons(BraodcastPort);

    if( bind(sd, (LPSOCKADDR) &cli, sizeof(cli)) <0 ){
       printf("bind error!\n");
       system("pause");
       return 0;
    }
    serv_len = sizeof(serv);

    while(1){
        n = recvfrom(sd, str, MAXLINE, 0, (LPSOCKADDR) &serv, &serv_len );
        printf("client(from:%s):%s\n", inet_ntoa(serv.sin_addr), str);
    }

    closesocket(sd);
    WSACleanup();

    return 0;
}
