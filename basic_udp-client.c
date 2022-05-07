#include<stdio.h>
#include<winsock.h>
int main(){
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv;

	char str[100]="I love NP!";
	int n,i;

	n = WSAStartup(0x101,(WSADATA *) &wsadata);

	sd = socket(AF_INET,SOCK_DGRAM,0);

	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(12345);

	int len_serv = sizeof(serv);

	n = sendto(sd,str,strlen(str)+1,0,(struct sockaddr*) &serv, len_serv);
	printf("Send:%s (%d)\n",str,n+1);

	closesocket(sd);
	WSACleanup();
}
