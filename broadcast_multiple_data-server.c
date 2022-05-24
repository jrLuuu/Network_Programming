#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 20
#define BraodcastPort 5678

int main()
{
    SOCKET	serv_sd;
  	struct 	sockaddr_in serv, cli;
  	int cli_len, n, i=1;
  	char str[MAXLINE];

  	WSADATA wsadata;
  	WSAStartup(0x101, &wsadata);
   	serv_sd = socket(AF_INET, SOCK_DGRAM, 0);

  	BOOL broadcast = TRUE;
  	setsockopt(serv_sd, SOL_SOCKET, SO_BROADCAST, ( const char* )&broadcast, sizeof(broadcast));

  	cli_len = sizeof(cli);
   	printf("server start broadcasting on port:%d\n", BraodcastPort);

  	cli.sin_family = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("255.255.255.255");
   	cli.sin_port = htons(BraodcastPort);

    while(1){
        memset(str, i%10 +'0', sizeof(str));
        sendto(serv_sd, str, strlen(str), 0, (LPSOCKADDR)&cli, cli_len);
        printf("server broadcast: %s\n",str);

        memset(str, (i-1)%26 +'a', sizeof(str));
        sendto(serv_sd, str, strlen(str), 0, (LPSOCKADDR)&cli, cli_len);
        printf("server broadcast: %s\n",str);

        memset(str, (i-1)%26 +'A', sizeof(str));
        sendto(serv_sd, str, strlen(str), 0, (LPSOCKADDR)&cli, cli_len);
        printf("server broadcast: %s\n",str);
        Sleep(1000);
        i++;
    }

    closesocket(serv_sd);
    WSACleanup();
}
