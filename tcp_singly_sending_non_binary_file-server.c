#include <stdio.h>
#include <winsock.h>
#define MAXSIZE 1024

int main()
{
	SOCKET sd, clnt_sd;
	struct sockaddr_in serv, clnt;
	int i, n;
	FILE *fout;
	fout = fopen("out.txt", "w+t");
	char str[MAXSIZE];

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);

	printf("sd=%d\n", sd);
	int len_serv = sizeof(serv);

    n = bind(sd, (struct sockaddr*) &serv, len_serv);
	printf("bind(): %d\n", n);
	n = listen(sd, 5);
	printf("listen(): %d\n", n);
	int len_clnt = sizeof(clnt);
	clnt_sd = accept(sd, (struct sockaddr*) &clnt, &len_clnt);
	n = recv(clnt_sd, str, MAXSIZE, 0);
	str[n] = '\0';
	printf("recv:%s (%d)\n", str, n);

	fputs(str, fout);
	fclose(fout);

	closesocket(sd);
	WSACleanup();
	//system("pause");
}
