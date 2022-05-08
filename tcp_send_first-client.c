#include <stdio.h>
#include <winsock.h>
#define MAXSIZE 1024

int main()
{
	SOCKET sd;
	struct sockaddr_in serv;
	int i, n;
	char str[MAXSIZE];
	char str1[MAXSIZE]="I love NP!!";

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);

	printf("sd=%d\n", sd);
	int len_serv = sizeof(serv);
	n = connect(sd, (struct sockaddr*) &serv, len_serv);
	printf("connect():%d\n", n);
	n = send(sd, str1, strlen(str1), 0); // send first
	printf("send:%s (%d)\n", str1, n);
	n = recv(sd, str, MAXSIZE, 0); // then receive
	str[n] = '\0';
	printf("recv:%s (%d)\n", str, n);

	closesocket(sd);
	WSACleanup();
	//system("pause");
}
