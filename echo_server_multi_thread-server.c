#include <stdio.h> /* for printf(), fprintf() */
#include <winsock.h> /* for socket(),... */
#include <stdlib.h> /* for exit() */
#define MaxClient 10

void *ThreadMain(void *arg); /* Main program of a thread */

struct ThreadArgs /* Structure of arguments to pass to client thread */
{
	int clntIndex;
    int clntSock[MaxClient]; /* Socket descriptor for client */
    int Totalclnt;
    int Sock;
};

int main(int argc, char *argv[])
{
	struct ThreadArgs *threadArgs; /* Pointer to argument structure for thread */
    DWORD  threadID; /* Thread ID from CreateThread() */

	int servSock; /* Socket descriptor for server */
    int Sock; /* Socket descriptor for client */
    WSADATA wsaData; /* Structure for WinSock setup communication */
	struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
 	int clntLen; /* Length of client address data structure */
 	int i,n;
	//int TotalClnt;

	threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs));
	for(i=0; i<MaxClient; i++){
    	threadArgs -> clntSock[i] = 0;
	}
	threadArgs -> Totalclnt = 0;

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

		for(i=0; i<MaxClient; i++){
			if(threadArgs->clntSock[i] == 0)
				break;
		threadArgs -> clntIndex = i;

	    /* Wait for a client to connect */
	    if (( Sock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) <= 0)
	        printf("accept() failed");
	    threadArgs -> Sock = Sock;
	    threadArgs -> clntSock[i] = Sock;
		threadArgs -> Totalclnt++;

		/* Create separate memory for client argument */
        if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadMain, threadArgs, 0, (LPDWORD) &threadID) == NULL)
            printf("thread_create() failed");

        printf("New client with thread ID: %ld and socket:%d (Current Client:%d)\n", threadID, threadArgs -> clntSock[i], threadArgs -> Totalclnt);
    }
    free(threadArgs);
}

void *ThreadMain(void *threadArgs){
	//int clntSock[MaxClient]; /* Socket descriptor for client connection */
	//int Totalclnt;
	int clntIndex;
	int clntSocki;

    /* Extract socket file descriptor from argument */
    clntSocki = ((struct ThreadArgs *) threadArgs) -> Sock;
    clntIndex = ((struct ThreadArgs *) threadArgs) -> clntIndex;

	char echoBuffer[1000]; /* Buffer for echo string */
	int recvMsgSize; /* Size of received message */

    /* Send received string and receive again until end of transmission */
    while (1){ /* zero indicates end of transmission */
		recvMsgSize = recv(clntSocki, echoBuffer, 1000, 0);
		if(recvMsgSize <= 0){
		    ((struct ThreadArgs *) threadArgs) -> Totalclnt-- ;
		    ((struct ThreadArgs *) threadArgs) -> clntSock[clntIndex] = 0;
			printf("Connection[socket:%d] closed.(Current Client:%d) \n", clntSocki, ((struct ThreadArgs *) threadArgs) -> Totalclnt);
			break;
		}
    	send(clntSocki, echoBuffer, strlen(echoBuffer)+1, 0);
    }

    closesocket(clntSocki); /* Close client socket */
    ((struct ThreadArgs *) threadArgs)-> clntSock[clntIndex] = 0;
    return (NULL);
}
