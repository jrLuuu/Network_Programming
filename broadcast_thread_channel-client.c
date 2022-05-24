#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024
#define BraodcastPort 5678

SOCKET sd;
struct sockaddr_in cli;
int n, channel, cli_len;
char str[MAXLINE];

void *recvMess(void *argu){
    while(1){
        cli_len = sizeof(cli);
        n = recvfrom(sd, str, MAXLINE, 0, (LPSOCKADDR) &cli, &cli_len );
        switch(channel){
            case 1:
                if(str[0]>='0' && str[0]<='9')
                    printf("client(from:%s):%s\n", inet_ntoa(cli.sin_addr), str);
                break;

            case 2:
                if(str[0]>='a' && str[0]<='z')
                    printf("client(from:%s):%s\n", inet_ntoa(cli.sin_addr), str);
                break;

            case 3:
                if(str[0]>='A' && str[0]<='Z')
                    printf("client(from:%s):%s\n", inet_ntoa(cli.sin_addr), str);
                break;
        }
    }
}

int main(void)
{
    struct sockaddr_in serv;
    int serv_len, threadID;
    int n, i, j, total=0;
    char str[1024];

    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    BOOL broadcast = TRUE;
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
    }

    closesocket(sd);
    WSACleanup();

    return 0;
}
