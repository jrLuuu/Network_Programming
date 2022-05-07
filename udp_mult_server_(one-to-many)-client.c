#include<stdio.h>
#include<winsock.h>
int main(){
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv,serv1;

	char str[100]="I love NP!";
	char str1[100]="I love Algorithm!";
	int n,i;

	n = WSAStartup(0x101,(WSADATA *) &wsadata);

	sd = socket(AF_INET,SOCK_DGRAM,0);

	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(12345);

	serv1.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv1.sin_family = AF_INET;
	serv1.sin_port = htons(12346);

	int len_serv = sizeof(serv);
	int len_serv1 = sizeof(serv1);

	for(i=0;i<10;i++){
		n = sendto(sd,str,strlen(str)+1,0,(struct sockaddr*) &serv, len_serv);
		printf("Send to 12345:%s (%d)\n",str,n+1);
		Sleep(1000);
		n = sendto(sd,str1,strlen(str1)+1,0,(struct sockaddr*) &serv1, len_serv1);
		printf("Send to 12346:%s (%d)\n",str1,n+1);
		Sleep(1000);
	}

	closesocket(sd);
	WSACleanup();
}
