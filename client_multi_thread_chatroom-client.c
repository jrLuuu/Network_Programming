#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

void *ThreadMain(void *arg); /* Main program of a thread */

struct ThreadArgs /* Structure of arguments to pass to client thread */
{
	SOCKET sd;
};

int main(int argc, char **argv)
{
    SOCKET sd;
    struct sockaddr_in serv;
    struct ThreadArgs *threadArgs; /* Pointer to argument structure for thread */
    DWORD  threadID; /* Thread ID from CreateThread() */
    char str[MAXLINE];
    int n;

    WSADATA wsadata;
    WSAStartup(0x101, (LPWSADATA) &wsadata);
    sd = socket(AF_INET, SOCK_STREAM, 0);

    threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs));
    threadArgs -> sd = sd;

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5678);

    connect(sd, (LPSOCKADDR) &serv, sizeof(serv));

    if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadMain, threadArgs, 0, (LPDWORD) &threadID) == NULL)
        printf("CreateThread() failed");
	while(1){
        gets(str);
        n = send(sd, str, strlen(str)+1, 0); // send to server
        if(n < 0) printf("send error\n");
	}

	return 0;
}

void *ThreadMain(void *threadArgs){
    SOCKET sd;
    char str[MAXLINE];
    int n;

    sd = ((struct ThreadArgs *) threadArgs) -> sd;
	while(1){
		n = recv(sd, str, MAXLINE, 0); // receive data from echo server
        if(n < 0) break;
        printf("recv:%s\n", str);
	}

	closesocket(sd);
	WSACleanup();
    return NULL;
}
