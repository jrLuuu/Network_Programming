#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 20

int main()
{
    SOCKET	serv_sd;
  	struct 	sockaddr_in serv, cli;
  	int cli_len, n, i=1;
  	char str[MAXLINE];

  	WSADATA wsadata;
  	WSAStartup(0x101, &wsadata);
   	serv_sd = socket(AF_INET, SOCK_DGRAM, 0);

  	/* Set TTL of multicast packet */
   	int multicastTTL=1;
    if (setsockopt(serv_sd, IPPROTO_IP, IP_MULTICAST_TTL, (char *) &multicastTTL, sizeof(multicastTTL)) == SOCKET_ERROR)
        printf("setsockopt() failed");

  	cli_len = sizeof(cli);
   	printf("server will multicastcast.\n");

  	cli.sin_family = AF_INET;
   	cli.sin_addr.s_addr = inet_addr("224.1.1.1");
   	cli.sin_port = htons(5678);

    while(1){
        cli.sin_addr.s_addr = inet_addr("224.1.1.1");
        cli.sin_port = htons(5678);
        memset(str, i%10 +'0', sizeof(str));
        sendto(serv_sd, str, strlen(str), 0, (LPSOCKADDR)&cli, cli_len);
        printf("server multicast on port: %s\n", str);

        cli.sin_addr.s_addr = inet_addr("224.1.1.2");
        cli.sin_port = htons(5678);
        memset(str, (i-1)%26 +'a', sizeof(str));
        sendto(serv_sd, str, strlen(str), 0, (LPSOCKADDR)&cli, cli_len);
        printf("server multicast on port: %s\n", str);

        cli.sin_addr.s_addr = inet_addr("224.1.1.3");
        cli.sin_port = htons(5678);
        memset(str, (i-1)%26 +'A', sizeof(str));
        sendto(serv_sd, str, strlen(str), 0, (LPSOCKADDR)&cli, cli_len);
        printf("server multicast on port: %s\n", str);

        Sleep(1000);
        i++;
    }

    closesocket(serv_sd);
    WSACleanup();
}
