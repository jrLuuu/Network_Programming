#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv)
{
    SOCKET sd;
    struct sockaddr_in serv;
    char str[MAXLINE]="I love NP!!";
    int n;

    WSADATA wsadata;
    WSAStartup(0x101, (LPWSADATA) &wsadata);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5678);

    connect(sd, (LPSOCKADDR) &serv, sizeof(serv));

    while(1){
       strcpy(str, "How are you?");
       n = send(sd, str, strlen(str)+1, 0); // send to server
       printf("send:%s\n", str);
       if(n < 0) break;

       Sleep(1000);

       n = recv(sd, str, MAXLINE, 0); // receive data from server
       if(n <= 0) break;
       printf("recv:%s\n", str);
    }

    closesocket(sd);
    WSACleanup();
    return 0;
}
