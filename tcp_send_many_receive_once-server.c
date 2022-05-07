#include <stdio.h>
#include <winsock.h>
int main(){
	SOCKET sd, clnt_sd;
	WSADATA wsadata;
	struct sockaddr_in serv, clnt;
	int i,n;
	char str[100];

	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_STREAM,0);

	serv.sin_family= AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

    bind(sd,(struct sockaddr*) &serv,sizeof(serv));
	listen(sd,5);

	int clnt_len=sizeof(clnt);
	printf("Server waits.\n");
	clnt_sd = accept(sd,(struct sockaddr*) &clnt,&clnt_len);

	Sleep(1000);
    n = recv(clnt_sd, str, 100,0); // receive one time
    printf("Server receive:%s, byte:%d\n",str,n);

	closesocket(sd);
	closesocket(clnt_sd);
	WSACleanup();
	//system("pause");
}
