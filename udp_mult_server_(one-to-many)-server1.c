#include<stdio.h>
#include<winsock.h>
int main(){
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv,clnt;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(12345);
	char str[100];
	char *ip;
	int port;
	int n,i;
	n = WSAStartup(0x101,(WSADATA *) &wsadata);

	sd = socket(AF_INET,SOCK_DGRAM,0);

	int len_serv = sizeof(serv);
	int len_clnt = sizeof(clnt);
	n = bind( sd,(struct sockaddr*) &serv, len_serv );

	printf("Ready to recv on 12345...\n");
	while(1){
		n = recvfrom (sd, str ,100, 0,(struct sockaddr*) &clnt, &len_clnt );
		printf("recv:%s (%d)\n",str,n);
	}
	closesocket(sd);
	WSACleanup();
	system("pause");
}
