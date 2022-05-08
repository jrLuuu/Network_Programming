#include <stdio.h>
#include <winsock.h>

int main()
{
	SOCKET sd;
	struct sockaddr_in serv;
	int i, n;
	char str[100]="[CSIE][CSIE][CSIE][CSIE][CSIE]";

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sd, (struct sockaddr*) &serv, sizeof(serv));
	send(sd, str, strlen(str), 0); // send one time

	closesocket(sd);
	WSACleanup();
	//system("pause");
}
