#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024
#define BraodcastPort 5678

int main(int argc, char** argv)
{
    SOCKET sd;
    struct sockaddr_in cli;
    int n, channel, cli_len;
    char str[MAXLINE];

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
    cli_len = sizeof(cli);

    while(1){
        printf("Channel(1~3): ");
        scanf("%d", &channel);
        printf("\n");
        for(int i=0; i<30; i++){
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

    closesocket(sd);
    WSACleanup();

    return 0;
}
