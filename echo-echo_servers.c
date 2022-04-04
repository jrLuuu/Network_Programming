#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

int main()
{
    SOCKET        sd,sd2;     /* socket �y�z�l */
    struct sockaddr_in    serv,serv2;
    char  str1[]="123";
    char  str2[]="abc";
    char  str[MAXLINE];
    int   n;
    int port;
    WSADATA wsadata;

    /*
     * �I�s WSAStartup() ���U WinSock DLL ���ϥ�
     */

    if (WSAStartup(0x101,(LPWSADATA) &wsadata) != 0)
    {
        fprintf(stderr,"echo_srv: WSAStartup() fails!");
        exit(1);
    }
    strcpy(str,"127.0.0.1");
    port = 7;

    /*
     * ��g sockaddr_in ���c (serv) �C
     * ���e�]�A�Gserver �� IP ��}�Aport number �����C
     */

    serv.sin_family       = AF_INET;
    serv.sin_addr.s_addr  = inet_addr(str);
    serv.sin_port         = htons(port);


    if ( (sd=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
    {
        fprintf(stderr,"echo_cli: can't open tcp socket\n");
        exit(1);
    }

    /*
     * �s���� echo server
     */

    if ( connect(sd, (LPSOCKADDR) &serv, sizeof(serv))
            == SOCKET_ERROR)
    {
        fprintf(stderr, "echo_cli: can't connect to echo server\n");
        exit(1);
    }



    strcpy(str,"127.0.0.1");
    port = 7;

    serv2.sin_family       = AF_INET;
    serv2.sin_addr.s_addr  = inet_addr(str);
    serv2.sin_port         = htons(port);

    if ( (sd2=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
    {
        fprintf(stderr,"echo_cli: can't open tcp socket\n");
        exit(1);
    }


    /*
     * �s���� echo server
     */

    if ( connect(sd2, (LPSOCKADDR) &serv2, sizeof(serv2))
            == SOCKET_ERROR)
    {
        fprintf(stderr, "echo_cli: can't connect to echo server\n");
        exit(1);
    }


    for(int i=0; i < 10; i++ )
    {
        Sleep(100);
        if ( send(sd, str1, strlen(str1)+1, 0) == SOCKET_ERROR)
        {
            fprintf(stderr, "echo_cli: send() error!\n");
            break;
        }
        if ( (n=recv(sd, str, MAXLINE, 0))==0)
        {
            fprintf(stderr,"echo_cli: connection closed\n");
            break;
        }
        else if (n==SOCKET_ERROR)
        {
            fprintf(stderr,"echo_cli: recv() error!\n");
            break;
        }
        else printf(str);

        printf("\n=====================\n");
        if ( send(sd2, str2, strlen(str2)+1, 0) == SOCKET_ERROR)
        {
            fprintf(stderr, "echo_cli: send() error!\n");
            break;
        }
        if ( (n=recv(sd2, str, MAXLINE, 0))==0)
        {
            fprintf(stderr,"echo_cli: connection closed\n");
            break;
        }
        else if (n==SOCKET_ERROR)
        {
            fprintf(stderr,"echo_cli: recv() error!\n");
            break;
        }
        else printf(str);

        printf("\n=====================\n");



    } // end for
    closesocket(sd);
    closesocket(sd2);
    WSACleanup();
    return 0;
}
