#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main()
{
	SOCKET	serv_sd, cli_sd;
  	struct 	sockaddr_in serv, cli;
  	int cli_len, n, i;
  	char str[MAXLINE];

  	WSADATA wsadata;
    WSAStartup(0x101, &wsadata);

  	serv_sd = socket(AF_INET, SOCK_STREAM, 0);

   	serv.sin_family = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port = htons(5678);

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
   	listen(serv_sd, 5) ;

   	cli_len = sizeof(cli);

   	while(1){
   		printf("server: waiting for client\n");

   		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

        //enable non-blocking mode when iMode=1
        u_long iMode = 1;
        ioctlsocket(cli_sd, FIONBIO, &iMode);

		if(iMode == 0)
            printf("This is blocking mode.\n");
		else
            printf("This is non-blocking mode.\n");

		for(;;){
	        printf("recv() checks.\n");
			n=recv(cli_sd, str, MAXLINE, 0);
			str[n]='\0';

			if(n > 0)
	        	printf("Recv: %s\n",str);

			Sleep(1000);

			int nError = WSAGetLastError();
			if(nError!=WSAEWOULDBLOCK && nError!=0){
				printf("Disconnected! error code:%d\n", nError);
				closesocket(cli_sd);
				break;
			}
        }
    }

   	closesocket(serv_sd);
   	closesocket(cli_sd);
   	WSACleanup();
}
