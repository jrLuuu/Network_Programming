#include <stdio.h>
#include <winsock.h>

int main(){
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv;
	int i, n;
	char str[100]="I love NP!";

	WSAStartup(0x101,&wsadata);

	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	while(1){
		sd = socket(AF_INET, SOCK_STREAM, 0);
		printf("Input: ");
		gets(str);
		connect(sd, (struct sockaddr *)  &serv,sizeof(serv) );
		send(sd, str, strlen(str)+1, 0);
		printf("Send: %s\n", str);
		closesocket(sd);
	}
	WSACleanup();
}
