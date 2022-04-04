#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

int main()
{
    SOCKET        sd;     /* socket �y�z�l */
    struct sockaddr_in    serv;
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



    /*
     * �}�Ҥ@�� TCP socket.
     */
    for(int i=0; i < 20; i++ )
    {

        strcpy(str,"127.0.0.1");
        if (i%2 ==0 )
            port = 17;
        else
            port = 13;
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

        n=recv(sd, str, MAXLINE, 0);
        while( n!= 0 )
        {
            if (n==SOCKET_ERROR)
            {
                fprintf(stderr,"echo_cli: recv() error!\n");
                break;
            }
            else
                str[n]='\0';
            printf(str);
            n=recv(sd, str, MAXLINE, 0);
        }

        printf("\n==============================\n");
        //printf("\n\necho_cli: connection closed\n");

        /*
         * ���� WinSock DLL ���ϥ�
         */

        closesocket(sd);
    } // end for
    WSACleanup();
    return 0;
}
