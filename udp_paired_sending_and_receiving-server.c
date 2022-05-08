#include <stdio.h>
#include <winsock.h>

int main()
{
	SOCKET sd, clnt_sd;
	struct sockaddr_in serv, clnt;
	int i, n;
	char str[100];

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_DGRAM,0);
	serv.sin_family= AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

    bind(sd, (struct sockaddr*) &serv, sizeof(serv));

	int clnt_len = sizeof(clnt);
	printf("Server waits.\n");
	Sleep(1000);

    while(1){
        n = recv(sd, str, 100, 0);
        printf("Server receive:%s, byte:%d\n", str, n);
        Sleep(1000);
    }

	closesocket(sd);
	WSACleanup();
	//system("pause");
}
