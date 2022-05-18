#include <stdio.h>
#include <winsock.h>

int main()
{
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv;
	int i,n,err;
	char str[100]="I love NP!";

	WSAStartup(0x101,&wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sd, (struct sockaddr *)  &serv, sizeof(serv) );
	printf("Connect to server.\n");

	fd_set readfds;
	while(1){
		FD_ZERO(&readfds);
		FD_SET(sd, &readfds);
		n = select( 0 , &readfds , NULL , NULL , NULL);
		if(FD_ISSET( sd, &readfds)){
			n = recv(sd,str, 100, 0);
	        if(n > 0)
	        	printf("(from server): %s\n",str);
	        else{
				err = WSAGetLastError();
				if(n != 0 && err != WSAEWOULDBLOCK)
					break;
			}
		}
	}

    closesocket(sd);
	WSACleanup();
}
