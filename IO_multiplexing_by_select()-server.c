#include <stdio.h>
#include <winsock.h>

int main()
{
	SOCKET sd,clnt_sd;
	WSADATA wsadata;
	struct sockaddr_in serv,clnt;
	int i,n;
	char str[100]="I love NP!";

	WSAStartup(0x101,&wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sd, (struct sockaddr *) &serv, sizeof(serv));

	listen(sd,5);
	int clnt_len=sizeof(clnt);

	while(1){
        printf("Server waits.\n");
        clnt_sd = accept(sd, (struct sockaddr *)  &clnt, &clnt_len );
        printf("Client is connected.\n");
        while(1){
            n = send(clnt_sd,str, strlen(str)+1,0);
            if(n < 0){
                closesocket(clnt_sd);
                break;
            }
            printf("(server send): %s\n",str);
            Sleep(1000);
        }
	}

	closesocket(sd);
	closesocket(clnt_sd);
	WSACleanup();
	system("pause");
}
