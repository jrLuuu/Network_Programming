#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024

int main(int argc, char* argv)
{
    SOCKET sd;
    struct sockaddr_in serv;
    char str[MAXLINE]="How are you?", str_r[MAXLINE];
    int n, i;

    WSADATA wsadata;
    WSAStartup(0x101,(LPWSADATA) &wsadata);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5678);

    connect(sd, (LPSOCKADDR) &serv, sizeof(serv));
    printf("Client has connected to Server.\n");

	for(;;){
	    Sleep(10000);
	   	send(sd, str, strlen(str)+1, 0);
	    printf("Send: %s (in 10 secs)\n", str);
	    recv(sd, str_r, MAXLINE, 0);
	    printf("Recv: %s \n", str);
	}

    closesocket(sd);
    WSACleanup();
}
