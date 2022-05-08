#include <stdio.h>
#include <winsock.h>
#define MAXSIZE 1024

int main()
{
	SOCKET sd;
	struct sockaddr_in serv;
	int i, n;
	FILE *fin;
	fin = fopen("in.txt", "rb");
	char buf[MAXSIZE];

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_STREAM,0);

	printf("sd=%d\n", sd);
	int len_serv = sizeof(serv);
	n = connect(sd, (struct sockaddr*) &serv, len_serv);
	printf("connect():%d\n", n);

    n = fread(buf, 1, MAXSIZE, fin);
    while(n > 0){
        send(sd, buf, n, 0);
        printf("read and send: %d Byte\n", n);
        n = fread(buf, 1, MAXSIZE, fin);
    }

	fclose(fin);
	closesocket(sd);
	WSACleanup();
	//system("pause");
}
