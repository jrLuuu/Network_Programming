#include <stdio.h>
#include <winsock.h>
#include <time.h>
#define maxsize 1024

int main()
{
    clock_t start, end;
    double total_time, rate;
    int total_recv;

	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv,clnt;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_family = AF_INET;
	serv.sin_port = htons(12345);
	char str[maxsize];
	int n, i;

	n = WSAStartup(0x101,(WSADATA *) &wsadata);
	sd = socket(AF_INET,SOCK_DGRAM,0);

	int len_serv = sizeof(serv);
	int len_clnt = sizeof(clnt);
	n = bind( sd,(struct sockaddr*) &serv, len_serv );

	printf("Ready to recv on 12345...\n");

	total_recv = 0;
	total_time = 0.0;

	while(1){
        total_recv = 0;
        n = recvfrom (sd, str, maxsize, 0, (struct sockaddr*) &clnt, &len_clnt );
        start = clock();

        for(i=0; i<4; i++){
            n = recvfrom (sd, str, maxsize, 0, (struct sockaddr*) &clnt, &len_clnt );
            end = clock();
            total_time = (end-start)/1000.0;
            total_recv += n;
            rate = total_recv / total_time;
            printf("recv:%s (%d) rate:%f\n", str, n, rate);
        }
	}

	closesocket(sd);
	WSACleanup();
	system("pause");
}
