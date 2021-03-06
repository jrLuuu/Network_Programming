#include <stdio.h>
#include <winsock.h>

int main()
{
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv, clnt;

	char str[100]="I love NP!";
	int n, i;

	n = WSAStartup(0x101, (WSADATA *) &wsadata);
	sd = socket(AF_INET, SOCK_DGRAM, 0);

	int len_clnt = sizeof(clnt);

	clnt.sin_addr.s_addr = inet_addr("127.0.0.1");
	clnt.sin_family = AF_INET;
	clnt.sin_port = htons(22222);

	bind(sd, (struct sockaddr*) &clnt, len_clnt);

	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(12345);

	int len_serv = sizeof(serv);

	connect(sd, (struct sockaddr*) &serv, len_serv);

	for(i=0; i<10; i++){
		n = send(sd, str, strlen(str)+1, 0);
		printf("Client 1 sends to 12345:%s (%d)\n", str, n+1);
		Sleep(1000);
	}

	closesocket(sd);
	WSACleanup();
}
