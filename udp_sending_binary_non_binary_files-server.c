#include <stdio.h>
#include <winsock.h>
#define MAXSIZE 1024

int main()
{
	SOCKET sd, clnt_sd;
	struct sockaddr_in serv, clnt;
	int i, n;
	FILE *fout;
	fout = fopen("out.txt", "w+b");
	char buf[MAXSIZE];

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_DGRAM, 0);

	printf("sd=%d\n", sd);
	int len_serv = sizeof(serv);

    n = bind(sd, (struct sockaddr*) &serv, len_serv);
	printf("bind(): %d\n", n);

	int len_clnt = sizeof(clnt);

    n = recv(sd, buf, MAXSIZE, 0);
    printf("recv and save: %d Byte\n", n);
	while(n > 0){
        fwrite(buf, 1, n, fout);
        n = recv(sd, buf, MAXSIZE, 0);
        printf("recv and save: %d Byte\n", n);
	}

	fclose(fout);
	closesocket(sd);
	closesocket(clnt_sd);
	WSACleanup();
	//system("pause");
}
