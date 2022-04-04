#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

int main()
{
    SOCKET        serv_sd, cli_sd,sd;        /* socket �y�z�l */
    struct sockaddr_in    serv, cli,dest;
    int   cli_len, n,port;
    char  str[MAXLINE];
    WSADATA wsadata;

    /*
     * �I�s WSAStartup() ���U WinSock DLL ���ϥ�
     */

    if (WSAStartup(0x101,(LPWSADATA) &wsadata) != 0)
    {
        fprintf(stderr,"echo_srv: can't use WinSock DLL\n");
        exit(1);
    }
    // add here
    // connect to dest
    strcpy(str,"127.0.0.1");
    port = 7;

    dest.sin_family       = AF_INET;
    dest.sin_addr.s_addr  = inet_addr(str);
    dest.sin_port         = htons(port);

    /*
     * �}�Ҥ@�� TCP socket.
     */

    if ( (sd=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
    {
        fprintf(stderr,"echo_cli: can't open tcp socket\n");
        exit(1);
    }

    /*
     * �s���� echo server
     */

    if ( connect(sd, (LPSOCKADDR) &dest, sizeof(dest))
            == SOCKET_ERROR)
    {
        fprintf(stderr, "echo_cli: can't connect to echo server\n");
        exit(1);
    }

    /*
     * �}�� TCP socket
     */

    if ( (serv_sd=socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
    {
        fprintf(stderr,"echo_srv: can't open TCP socket\n");
        exit(1);
    }

    /*
     * ���w socket �� IP ��}�M port number
     */

    serv.sin_family      = AF_INET;
    serv.sin_addr.s_addr = 0;
    //serv.sin_port        = htons(IPPORT_ECHO);
    serv.sin_port        = htons(7777);
    // ���w IPPORT_ECHO �� echo port

    if ( bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv)) <0)
    {
        fprintf(stderr, "echo_srv: can't bind local address\n");
        exit(1);
    }

    /*
     * �I�s listen() �� socket �i�J�u��ť�v���A�A�ë��w
     * �̦h�i�P�ɱ������s���n�D�]�b��C���^
    */

    if ( listen(serv_sd, 5) < 0)
    {
        fprintf(stderr,"echo_srv: listen() error\n");
        exit(1);
    }

    /*
     * ���� clinet �{�����s���C
     * �`�N�I�ڭ̥u���\�@�� client �{�����s��
     */

    cli_len=sizeof(cli);
    while (1)
    {
        printf("echo_srv: waiting for client\n");
        if ( (cli_sd=accept(serv_sd, (struct sockaddr *)
                            &cli, &cli_len)) == SOCKET_ERROR )
        {
            fprintf(stderr, "echo_srv: accpet() error\n");
            closesocket(cli_sd);
        }
        else
        {
            while (1)
            {
                if ( (n=recv(cli_sd, str, MAXLINE, 0))==0)
                {
                    fprintf(stderr, "echo_srv: connection closed\n");
                    break;
                }
                else if (n==SOCKET_ERROR)
                {
                    fprintf(stderr, "echo_srv: recv() error!\n");
                    break;
                }
                str[n]='\0';
                printf("echo_srv from client: %s\n",str);   // ��ܱq client �ǨӪ��r��
                //add here 2
                //send to dest
                if ( send(sd, str, strlen(str), 0) == SOCKET_ERROR)
                {
                    fprintf(stderr, "echo_srv: connection closed\n");
                    break;
                }
                //recv from dest
                if ( (n=recv(sd, str, MAXLINE, 0))==0)
                {
                    fprintf(stderr, "echo_srv: connection closed\n");
                    break;
                }
                else if (n==SOCKET_ERROR)
                {
                    fprintf(stderr, "echo_srv: recv() error!\n");
                    break;
                }
                str[n]='\0';
                printf("echo_srv from dest: %s\n",str);   // ��ܱq client �ǨӪ��r��

                //add complete
                if ( send(cli_sd, str, strlen(str), 0) == SOCKET_ERROR)
                {
                    fprintf(stderr, "echo_srv: connection closed\n");
                    break;
                }
            }
        }
    }

    /*
     * ���� WinSock DLL ���ϥ�
     */
    closesocket(serv_sd);
    closesocket(cli_sd);
    closesocket(sd);
    WSACleanup();

    return 0;
}
