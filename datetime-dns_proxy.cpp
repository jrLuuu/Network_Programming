#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>
#include <iostream>

int MAXLINE = 1024;
using namespace std;

int main()
{
    cout << "Time port: 7777 / Dns port: 1234" << endl;
    while(1)
    {
        cout << "Input serv: ";
        string proxy_srv;
        cin >> proxy_srv;
        if(proxy_srv == "time")
        {
            WSADATA wsadata;
            SOCKET  serv_sd, cli_sd, sd;
            struct sockaddr_in serv, cli, dest ;
            int cli_len, n;
            char str[MAXLINE];

            if (WSAStartup(0x101,(LPWSADATA) &wsadata) != 0)
            {
                fprintf(stderr,"Daytime_srv: can't use WinSock DLL\n");
                exit(1);
            }

            strcpy(str, "127.0.0.1");

            dest.sin_family       = AF_INET;
            dest.sin_addr.s_addr  = inet_addr(str);
            dest.sin_port         = htons(13);

            if ( (sd=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
            {
                fprintf(stderr,"Daytime_cli: can't open tcp socket\n");
                exit(1);
            }

            if ( connect(sd, (LPSOCKADDR) &dest, sizeof(dest)) == SOCKET_ERROR)
            {
                fprintf(stderr, "Daytime_cli: can't connect to Daytime server\n");
                exit(1);
            }

            if ( (serv_sd=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
            {
                fprintf(stderr, "Daytime_srv: can't open TCP socket\n");
                exit(1);
            }

            serv.sin_family      = AF_INET;
            serv.sin_addr.s_addr = 0;
            serv.sin_port        = htons(7777);

            if ( bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv)) <0)
            {
                fprintf(stderr, "Daytime_srv: can't bind local address\n");
                exit(1);
            }

            if ( listen(serv_sd, 5) < 0)
            {
                fprintf(stderr, "Daytime_srv: listen() error\n");
                exit(1);
            }

            cli_len = sizeof(cli);
            printf("Daytime_srv: waiting for client\n");

            if ( (cli_sd = accept(serv_sd, (struct sockaddr *) &cli, &cli_len)) == SOCKET_ERROR )
            {
                fprintf(stderr, "Daytime_srv: accpet() error\n");
                closesocket(cli_sd);
            }
            else
            {
                while (1)
                {
                    n = recv(sd, str, MAXLINE, 0);
                    if (n == 0)
                    {
                        fprintf(stderr, "Daytime_srv: connection closed\n");
                        break;
                    }
                    else if (n == SOCKET_ERROR)
                    {
                        fprintf(stderr, "Daytime_srv: recv() error!\n");
                        break;
                    }
                    str[n] = '\0';
                    printf("Daytime_srv from dest: %s\n", str);

                    if ( send(cli_sd, str, strlen(str), 0) != SOCKET_ERROR)
                    {
                        fprintf(stderr, "Daytime_srv: connection closed\n");
                        break;
                    }
                    closesocket(cli_sd);
                }
                closesocket(serv_sd);
                closesocket(cli_sd);
                closesocket(sd);
                WSACleanup();
            }
        }
        if(proxy_srv.substr(0,6) == "ask://")
        {
            SOCKET  serv_sd, cli_sd;
            struct sockaddr_in serv, cli, dest;
            int cli_len, n;
            char str[MAXLINE];
            WSADATA wsadata;

            if (WSAStartup(0x101,(LPWSADATA) &wsadata) != 0)
            {
                fprintf(stderr,"Dns_srv: can't use WinSock DLL\n");
                exit(1);
            }

            if ( (serv_sd=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
            {
                fprintf(stderr,"Dns_srv: can't open TCP socket\n");
                exit(1);
            }

            serv.sin_family      = AF_INET;
            serv.sin_addr.s_addr = 0;
            serv.sin_port        = htons(1234);

            if ( bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv)) <0)
            {
                fprintf(stderr, "Dns_srv: can't bind local address\n");
                exit(1);
            }

            if ( listen(serv_sd, 5) < 0)
            {
                fprintf(stderr,"Dns_srv: listen() error\n");
                exit(1);
            }

            cli_len = sizeof(cli);
            printf("Dns_srv: waiting for client\n");

            if ( (cli_sd = accept(serv_sd, (struct sockaddr *) &cli, &cli_len)) == SOCKET_ERROR )
            {
                fprintf(stderr, "Dns_srv: accpet() error\n");
                closesocket(cli_sd);
            }
            else
            {
                while (1)
                {
                    char ip[16];
                    string ipQuery = proxy_srv.substr(6);
                    strcpy(ip, ipQuery.c_str());

                    LPHOSTENT hp;
                    struct in_addr sAddr;
                    sAddr.s_addr = inet_addr(ip);
                    hp = gethostbyaddr((LPSTR)&sAddr, sizeof(sAddr), AF_INET);

                    if(hp != NULL)
                    {
                        strcpy(str, hp->h_name) ;
                    }

                    if ( send(cli_sd, str, strlen(str), 0) != SOCKET_ERROR)
                    {
                        printf("Dns_srv from dest: %s\n", str);
                        fprintf(stderr, "Dns_srv: connection closed\n");
                        break;
                    }
                    closesocket(cli_sd);
                }
                closesocket(serv_sd);
                closesocket(cli_sd);
                WSACleanup();
            }
        }
    }

    return 0;
}
