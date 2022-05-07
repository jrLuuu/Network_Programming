#include <stdio.h>
#include <winsock.h>
#include <time.h>

int main(){
	SOCKET sd;
	struct sockaddr_in serv;
	int i, n;
	char str[100];
	char str1[100];
	clock_t t1, t2;

	WSADATA wsadata;
	WSAStartup(0x101, &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sd, (struct sockaddr *)  &serv,sizeof(serv) );
	printf("Connect to server.\n");

	u_long iMode = 1;
	ioctlsocket(sd, FIONBIO, &iMode);

	printf("Client Name: ");
	gets(str1);
	printf("Time Interval(sec): ");
	int ti;
	scanf("%d",&ti);
	Sleep(5000);

	t2 = 0;
	float time;
	while(1){
		t1 = clock();
		time = (t1-t2)/CLOCKS_PER_SEC;
		if(time > ti){
            strcpy(str, str1);
            printf("[Client]: %s\n", str);
            send(sd, str, strlen(str), 0);
            t2 = clock();
		}

		memset(str, 0, 100);
		n = recv(sd, str, 100, 0);
		if(n > 0){
            str[n] = '\0';
            printf("[Other]: %s\n", str);
		}
		Sleep(100);
	}

	closesocket(sd);
	WSACleanup();
}
