#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv)
{
    SOCKET sd1, sd2;
    struct sockaddr_in serv;
    char str[MAXLINE]="I love NP!!";
    char strRecv[MAXLINE];
    int n;

    WSADATA wsadata;
    WSAStartup(0x101, (LPWSADATA) &wsadata);

    sd1 = socket(AF_INET, SOCK_STREAM, 0);
    sd2 = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5678);

    n = connect(sd1, (LPSOCKADDR) &serv, sizeof(serv));
    if(n < 0) printf("connect1 error!");
    n = connect(sd2, (LPSOCKADDR) &serv, sizeof(serv));
    if(n < 0) printf("connect2 error!");

    while(1){
        strcpy(str, "I love NP.");
        n = send(sd1, str, strlen(str)+1, 0); // send to server
        printf("send:%s\n", str);
        if(n < 0){
            printf("send error!");
            break;
        }

        Sleep(1000);

        n = recv(sd2, strRecv, MAXLINE, 0); // receive data from server
        if(n < 0){
            printf("recv error!");
            break;
        }
        printf("recv:%s\n", strRecv);

        strcpy(str, "I love ALGO.");
        n = send(sd2, str, strlen(str)+1, 0); // send to server
        printf("send:%s\n", str);
        if(n < 0){
            printf("send error!");
            break;
        }

        Sleep(1000);

        n = recv(sd1, strRecv, MAXLINE, 0); // receive data from server
        if(n < 0){
            printf("recv error!");
            break;
        }
        printf("recv:%s\n", strRecv);
    }

    closesocket(sd1);
    closesocket(sd2);
    WSACleanup();
    return 0;
}
