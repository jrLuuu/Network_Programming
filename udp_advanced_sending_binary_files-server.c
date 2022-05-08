#include <stdio.h>
#include <winsock.h>
#define MAXSIZE 1024

int main()
{
	SOCKET sd, clnt_sd;
	struct sockaddr_in serv, clnt;
	int i, n, sum = 0, counter = 0;
	FILE *fout;
	fout = fopen("out.jpg", "w+b");
	char buf[MAXSIZE];

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

	WSADATA wsadata;
	WSAStartup(0x101, (LPWSADATA) &wsadata);
	sd = socket(AF_INET, SOCK_DGRAM,0);

	printf("sd=%d\n", sd);
	int len_serv = sizeof(serv);

    n = bind(sd, (struct sockaddr*) &serv, len_serv);
	printf("bind(): %d\n", n);

	int len_clnt = sizeof(clnt);

    n = recv(sd, buf, MAXSIZE, 0);
	while(n > 0){
        counter++;
        sum += n;
        fwrite(buf, 1, n, fout);
        printf("(%d)read and save: %d(%d) Byte\n", counter, n, sum);
        n = recv(sd, buf, MAXSIZE, 0);
        if(strcmp(buf,"END") == 0){
            printf("File transmission complete. (Sum:%d)\n", sum);
            n = recv(sd, buf, MAXSIZE, 0);
            itoa(sum, buf, 10);
            if(sum != atoi(buf))
                printf("Oops! Pkt number mismatched\n");
            else
                printf("Pkt number matched\n");
            break;
        }
	}

	fclose(fout);
	closesocket(sd);
	closesocket(clnt_sd);
	WSACleanup();
	//system("pause");
}
