#include <stdio.h>
#include <winsock.h>
#define MAXSIZE 1024

int main()
{
	SOCKET sd;
	struct sockaddr_in serv;
	int i, n, sum = 0, counter = 0;
	FILE *fin;
	fin = fopen("in.jpg", "rb");
	char buf[MAXSIZE];

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_DGRAM,0);

	printf("sd=%d\n", sd);
	int len_serv = sizeof(serv);
	n = connect(sd, (struct sockaddr*) &serv, len_serv);
	printf("connect():%d\n", n);

    n = fread(buf, 1, MAXSIZE, fin);
    while(n > 0){
        send(sd, buf, n, 0);
        sum += n;
        counter++;
        printf("(%d)read and send: %d(%d) Byte\n", counter, n, sum);
        n = fread(buf, 1, MAXSIZE, fin);
    }
    send(sd, "END", 4, 0);
    printf("File transmission complete. (Sum:%d)\n", sum);
    itoa(sum, buf, 10);
    send(sd, buf, sizeof(buf), 0);

	fclose(fin);
	closesocket(sd);
	WSACleanup();
	//system("pause");
}

