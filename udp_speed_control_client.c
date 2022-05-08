#include <stdio.h>
#include <winsock.h>
#define maxsize 1024

int main()
{
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv;

	char str[maxsize]="I love NP!";
	int n, i;
	int rate;

	n = WSAStartup(0x101, (WSADATA *) &wsadata);
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(12345);

	int len_serv = sizeof(serv);
    float t = 1000;

    while(1){
        printf("rate:");
        scanf("%d", &rate);
        t = 1000.0/rate;
        for(i=0; i<10; i++){
            n = sendto(sd, str, maxsize, 0, (struct sockaddr*) &serv, len_serv);
            printf("Send:%s (%d)\n", str, n);
            Sleep((int)t);
        }
	}
	//1024 Bps

	closesocket(sd);
	WSACleanup();
}
