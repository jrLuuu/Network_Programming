#include <stdio.h>
#include <winsock.h>

int main()
{
    SOCKET sd, clnt_sd;
    WSADATA wsadata;
    struct sockaddr_in serv, clnt;
    int i, n;
    char str[100];

    WSAStartup(0x101,&wsadata);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sd, (struct sockaddr *) &serv, sizeof(serv));
    listen(sd,5);
    while (1)
    {
        int clnt_len=sizeof(clnt);
        printf("Server waits.\n");
        clnt_sd =  accept(sd, (struct sockaddr *)  &clnt, &clnt_len);

        while (1)
        {
            n = recv(clnt_sd,str, 100, 0);
            if ( n > 0 && str[0]=='.')
                break;
            str[n]='\0';
            printf("Server receive:%s\n",str);
            send(clnt_sd,str, n+1,0);
        }
        closesocket(clnt_sd);
    }
    closesocket(sd);
    WSACleanup();
}
