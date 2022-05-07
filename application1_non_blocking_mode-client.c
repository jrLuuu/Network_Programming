#include <stdio.h>
#include <winsock.h>

int main(){
	SOCKET sd;
	struct sockaddr_in serv;
	int i, n;
	char str[100]="I love NP!";

	WSADATA wsadata;
	WSAStartup(0x101, &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sd, (struct sockaddr *) &serv,sizeof(serv) );
	printf("Connect to server.\n");

	u_long iMode = 1;
	ioctlsocket(sd, FIONBIO, &iMode);

	while(1){
        strcpy(str,"I miss you!");
        printf("(clietn): %s\n", str);

		send(sd,str, strlen(str), 0);
		Sleep(500);

        memset(str, 0, 100);
        n = recv(sd, str, 100, 0);
        if(n > 0){
            str[n] = '\0';
            printf("(server): %s\n", str);
        }
	}

	closesocket(sd);
	WSACleanup();
}
