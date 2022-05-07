#include <stdio.h>
#include <winsock.h>
int main(){
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv;
	int i,n;
	char str[100]="[CSIE]";
	char str1[100]="[CSIE][CSIE][CSIE][CSIE][CSIE]";

	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_DGRAM,0);

	serv.sin_family= AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sd,(struct sockaddr*) &serv, sizeof(serv));

	for(int i=0; i<5; i++){
        send(sd, str, strlen(str),0);
	}

	closesocket(sd);
	WSACleanup();
	//system("pause");
}

