#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024
#define BraodcastPort 5678

SOCKET sd;
struct sockaddr_in serv, cli;
int serv_len, cli_len;
int n, channel=1, timeout=50;
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
    int n, i, j, total=0, threadID;

    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    char broadcast='a';
    if( setsockopt(sd, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcast, sizeof(broadcast)) <0 )
        printf("setsockopt() error!\n");

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = 0;
    serv.sin_port = htons(BraodcastPort);

    if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 ){
       printf("bind error!\n");
       system("pause");
       return 0;
    }
    serv_len = sizeof(serv);

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) recvMess, NULL, 0, (LPDWORD) &threadID);
    while(1){
        scanf("%d", &channel);
        printf("Switch to channel %d\n", channel);
        closesocket(sd);
        sd = socket(AF_INET, SOCK_DGRAM, 0);
        BOOL broadcast = TRUE;
        if( setsockopt(sd, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcast, sizeof(broadcast)) <0 )
            printf("setsockopt() error!\n");

        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = 0;

        switch(channel){
            case 1:
                serv.sin_port = htons(BraodcastPort);
                if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 ){
                   printf("bind error!\n");
                   system("pause");
                   return 0;
                }
                break;
            case 2:
                serv.sin_port = htons(BraodcastPort+1);
                if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 ){
                   printf("bind error!\n");
                   system("pause");
                   return 0;
                }
                break;
            case 3:
                serv.sin_port = htons(BraodcastPort+2);
                if( bind(sd, (LPSOCKADDR) &serv, sizeof(serv)) <0 ){
                   printf("bind error!\n");
                   system("pause");
                   return 0;
                }
                break;
        }
    }

    closesocket(sd);
    WSACleanup();

    return 0;
}
