#include <stdio.h> /* for printf(), fprintf() */
#include <winsock.h> /* for socket(),... */
#include <stdlib.h> /* for exit() */
#define MaxClient 10

void *ThreadMain(void *arg); /* Main program of a thread */

struct ThreadArgs /* Structure of arguments to pass to client thread */
{
	int clntSock1; /* Socket descriptor for client */
	int clntSock2; /* Socket descriptor for client */
};

int main(int argc, char *argv[])
{
	struct ThreadArgs *threadArgs; /* Pointer to argument structure for thread */
    DWORD  threadID; /* Thread ID from CreateThread() */

	int servSock; /* Socket descriptor for server */
    int clntSock1, clntSock2; /* Socket descriptor for client */
    WSADATA wsaData; /* Structure for WinSock setup communication */
	struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
 	int clntLen; /* Length of client address data structure */

	/* Load Winsock 2.0 DLL */
	if (WSAStartup(0x101, &wsaData) != 0){
        printf("WSAStartup() failed");
        exit(1);
    }

	/* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("socket() failed");

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
    echoServAddr.sin_family = AF_INET; /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(5678); /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        printf("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, 3) < 0)
        printf("listen() failed");

	printf("Server is waiting for clients.\n");

    for(;;){ /* Run forever */
	    clntLen = sizeof(echoClntAddr);

	    /* Wait for a client to connect */
	    if (( clntSock1 = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) <= 0)
	        printf("accept() failed");
	    if (( clntSock2 = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) <= 0)
	        printf("accept() failed");

		/* Create separate memory for client argument */
		threadArgs = ((struct ThreadArgs *) malloc(sizeof(struct ThreadArgs)));
		threadArgs -> clntSock1 = clntSock1;
		threadArgs -> clntSock2 = clntSock2;

        if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadMain, threadArgs, 0, (LPDWORD) &threadID) == NULL)
            printf("thread_create() failed");

        printf("New client with thread ID: %ld and socket:%d and %d\n", threadID, clntSock1, clntSock2);
    }
}

void *ThreadMain(void *threadArgs){
	int clntSock1, clntSock2; /* Socket descriptor for client */

    /* Extract socket file descriptor from argument */
    clntSock1 = ((struct ThreadArgs *) threadArgs) -> clntSock1;
    clntSock2 = ((struct ThreadArgs *) threadArgs) -> clntSock2;

	char echoBuffer[1000]; /* Buffer for echo string */
	int recvMsgSize; /* Size of received message */

	u_long iMode = 1; /* Non blocking mode */
	ioctlsocket(clntSock1, FIONBIO, &iMode);
	ioctlsocket(clntSock2, FIONBIO, &iMode);

	int nError;
    /* Send received string and receive again until end of transmission */
    while(1){ /* zero indicates end of transmission */
		if((recvMsgSize = recv(clntSock1, echoBuffer, 1000, 0)) > 0){
            send(clntSock2, echoBuffer, strlen(echoBuffer)+1, 0);
		}

		nError = WSAGetLastError();
		if(nError!=WSAEWOULDBLOCK && nError!=0){
            printf("Disconnected! error code:%d\n", nError);
            break;
		}

		if((recvMsgSize = recv(clntSock2, echoBuffer, 1000, 0)) > 0){
            send(clntSock1, echoBuffer, strlen(echoBuffer)+1, 0);
		}

		nError = WSAGetLastError();
		if(nError!=WSAEWOULDBLOCK && nError!=0){
            printf("Disconnected! error code:%d\n", nError);
            break;
		}

		Sleep(1000);
    }

    closesocket(clntSock1); /* Close client socket */
    closesocket(clntSock2); /* Close client socket */
    free(threadArgs);
    return (NULL);
}
