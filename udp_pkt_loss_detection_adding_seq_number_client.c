#include <stdio.h>
#include <winsock.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv;

	char str1[100]="I love NP!";
	char str[100];
	int n, i;
	int sn = 1;

	n = WSAStartup(0x101,(WSADATA *) &wsadata);
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(12345);

	int len_serv = sizeof(serv);

    for(sn=1; sn<11; sn++){
		itoa(sn, str, 10);
		strcat(str, "^^");
		strcat(str, str1);
		n = sendto(sd, str, strlen(str)+1, 0, (struct sockaddr*) &serv, len_serv);
		printf("Send:%s (%d)\n", str, n+1);
    }

    for(sn=12; sn<20; sn++){
		itoa(sn, str, 10);
		strcat(str, "^^");
		strcat(str, str1);
		n = sendto(sd, str, strlen(str)+1, 0, (struct sockaddr*) &serv, len_serv);
		printf("Send:%s (%d)\n", str, n+1);
    }

	closesocket(sd);
	WSACleanup();
}
