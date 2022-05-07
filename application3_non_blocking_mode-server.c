#include <stdio.h>
#include <winsock.h>
#define MaxClientNum 5

int main(){
	SOCKET sd, clnt_sd[MaxClientNum];
	struct sockaddr_in serv,clnt;
	int i, n;
	char str[100]="I love NP!";

	WSADATA wsadata;
	WSAStartup(0x101, &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sd, (struct sockaddr *) &serv, sizeof(serv));
	listen(sd,5);

	u_long iMode = 1;
	ioctlsocket(sd, FIONBIO, &iMode);

	int clnt_len = sizeof(clnt);
	printf("Server waits.\n");

	for(i=0; i<MaxClientNum; i++)
        clnt_sd[i] = -1;

    int curr_client_num = 0;

    while(1){
        n = accept(sd, (struct sockaddr *) &clnt, &clnt_len );
        if(n != -1){
            clnt_sd[curr_client_num] = n;
            printf("Client[%d] is connected.\n", curr_client_num);
            curr_client_num++;
        }

        for(i=0; i<MaxClientNum; i++){
            if(clnt_sd[i] != -1){
                send(clnt_sd[i], str, strlen(str)+1, 0);
                printf("Send to clnt_sd[%d]: %s\n", i, str);
            }
        }
        Sleep(1000);
    }

	closesocket(sd);
	closesocket(clnt_sd);
	WSACleanup();
}
