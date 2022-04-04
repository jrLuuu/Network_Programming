#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>
#include <time.h>

#define MAXLINE 1024

int main()
{
    WSADATA wsadata;
    SOCKET discard_socket, chargen_socket;
    struct sockaddr_in discard_server, chargen_server;
    char str[MAXLINE];
    int n, port, total = 0;
    time_t start, in_loop;

    if (WSAStartup(0x101,(LPWSADATA) &wsadata) != 0) {
        fprintf(stderr,"Echo_srv: WSAStartup() fails!");
        exit(1);
    }

    discard_server.sin_family = AF_INET;
    discard_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    discard_server.sin_port = htons(9);

    if( (discard_socket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR){
        fprintf(stderr,"Discard_cli: can't open tcp socket\n");
        exit(1);
    }
    if(connect(discard_socket, (struct sockaddr *) &discard_server, sizeof(discard_server)) == SOCKET_ERROR){
        fprintf(stderr, "Discard_cli: can't connect to echo server\n");
        exit(1);
    }

    chargen_server.sin_family = AF_INET;
    chargen_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    chargen_server.sin_port = htons(19);

    if( (chargen_socket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR){
        fprintf(stderr,"Chargen_cli: can't open tcp socket\n");
        exit(1);
    }
    if( connect(chargen_socket, (struct sockaddr *) &chargen_server, sizeof(chargen_server)) == SOCKET_ERROR){
        fprintf(stderr, "Chargen_cli: can't connect to echo server\n");
        exit(1);
    }

    start = time(NULL); // set the start timer
    while(1){
        if( (n = recv(chargen_socket, str, MAXLINE, 0)) == SOCKET_ERROR){
            fprintf(stderr,"Chargen_cli: recv() error!\n");
            break;
        }
        else if(n == 0){
            fprintf(stderr, "Chargen_cli: connection closed\n");
            break;
        }
        n = send(discard_socket, str, strlen(str)+1, 0);
        if(n == SOCKET_ERROR){
            fprintf(stderr, "Discard_cli: send() error\n");
            break;
        }
        total += n;
        in_loop = time(NULL); // since every time runs the loop we'll get the current time
        if(difftime(in_loop, start) > 1.0){ // the times where the while loop ran for one second
            printf("Bytes per second sending to discard server: %d (bytes)\n", total);
            total = 0;
            start = time(NULL);
        }
    }
    closesocket(discard_socket);
    closesocket(chargen_socket);
    WSACleanup();

    return 0;
}
