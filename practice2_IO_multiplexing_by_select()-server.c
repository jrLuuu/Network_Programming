#include <stdio.h>
#include <winsock.h>
#define MAXRECV 1024

int main(int argc, char *argv[])
{
    SOCKET serv_sd, cli_sd1, cli_sd2;
    struct sockaddr_in serv, cli;
    int max_clients = 30, activity, cli_len, i, n;
    char str[MAXRECV];
    fd_set readfds; // set of socket descriptors

    WSADATA wsadata;
    WSAStartup(0x101, &wsadata);
    serv_sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5678);

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
    listen(serv_sd, 3);

    cli_len = sizeof(cli);
    printf("TCP Server waits for client\n");
    cli_sd1 = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
    printf("Client 1 is connected: socket fd is %d , ip is : %s , port : %d \n", cli_sd1, inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
    cli_sd2 = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
    printf("Client 2 is connected: socket fd is %d , ip is : %s , port : %d \n", cli_sd2, inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

    while(TRUE){
        printf("[1] Clear the socket fd set.\n");
        FD_ZERO(&readfds); // clear the set of socket descriptors

        printf("[2] Add two client sockets to fd set.\n");
        FD_SET(cli_sd1, &readfds); // add client socket into the set of socket descriptors
        FD_SET(cli_sd2, &readfds); // add client socket into the set of socket descriptors

        // waiting for an activity on any of the sockets, timeout is NULL, so wait indefinitely
        printf("[3] Call select() and waiting.\n");
        activity = select(0, &readfds, NULL, NULL, NULL); // start up the listen system

        // if client 1 presend in read socket
        printf("[4] Wake up from select(): %d.\n", activity);

        if(activity == SOCKET_ERROR){
            printf("select call failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
        if(FD_ISSET(cli_sd1, &readfds)){ // confirm the set of socket descriptors
            n = recv(cli_sd1, str, MAXRECV, 0);
            printf("recv from client 1: %s \n", str);
            send(cli_sd1, str, strlen(str)+1, 0);
        }
        if(FD_ISSET(cli_sd2, &readfds)){ // confirm the set of socket descriptors
            n = recv(cli_sd2, str, MAXRECV, 0);
            printf("recv from client 2: %s \n", str);
            send(cli_sd2, str, strlen(str)+1, 0);
        }
    }

    closesocket(serv_sd);
    closesocket(cli_sd1);
    closesocket(cli_sd2);
    WSACleanup();
    system("pause");
}
