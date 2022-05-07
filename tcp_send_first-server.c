#include <stdio.h>
#include <winsock.h>
#define MAXSIZE 1024
int main(){
	SOCKET sd, clnt_sd;
	WSADATA wsadata;
	struct sockaddr_in serv, clnt;
	int i,n;
	char str[MAXSIZE];
	char str1[MAXSIZE]="I love ALGO!!";

	serv.sin_family= AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_STREAM,0);
	printf("sd=%d\n",sd);
	int len_serv=sizeof(serv);

	n = bind(sd,(struct sockaddr*) &serv,len_serv);
	printf("bind(): %d\n",n);
	n = listen(sd,5);
	printf("listen(): %d\n",n);
	int len_clnt = sizeof(clnt);
	clnt_sd = accept(sd,(struct sockaddr*) &clnt,&len_clnt);

    send(clnt_sd, str1, strlen(str1),0); // send first
	printf("send:%s (%d)\n",str1,n);
	n = recv(clnt_sd, str, MAXSIZE,0); // then receive
	str[n]='\0';
	printf("recv:%s (%d)\n",str,n);

	closesocket(sd);
	closesocket(clnt_sd);
	WSACleanup();
	//system("pause");
}
