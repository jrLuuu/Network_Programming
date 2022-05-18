#include <stdio.h>
#include <winsock.h>
#define MAXRECV 1024
#define MAXCLI 10

int main(int argc, char *argv[])
{
    SOCKET serv_sd, cli_sd[MAXCLI], new_socket;
    struct sockaddr_in serv, cli;
    int activity, cli_len, i, n, client_num = 0;
    int ready_to_send[MAXCLI];
    char str[MAXRECV];
    TIMEVAL timeout;
    fd_set readfds; // set of socket descriptors
    fd_set writefds; // set of socket descriptors

    for(i=0; i<MAXCLI; i++){
        ready_to_send[i] = 0;
        cli_sd[i] = 0;
    }

    WSADATA wsadata;
    WSAStartup(0x101, &wsadata);
    serv_sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5678);

    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));
    listen(serv_sd, 3);

    while(TRUE){
        printf("[1] Clear the socket fd set.\n");
        FD_ZERO(&readfds); // clear the set of socket descriptors
        FD_ZERO(&writefds); // clear the set of socket descriptors

        printf("[2] Add serv_sd[] to fd set.\n");
        FD_SET(serv_sd, &readfds); // add server socket into the set of socket descriptors

        printf("[2] Add cli_sd[] to fd set.\n");
        for(i=0; i<MAXCLI; i++){
            if(cli_sd[i] > 0){
                if(ready_to_send[i] == 0)
                    FD_SET(cli_sd[i], &readfds); // add server socket into the set of socket descriptors
                else
                    FD_SET(cli_sd[i], &writefds); // add server socket into the set of socket descriptors
            }
        }

        // set timeout
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // waiting for an activity on any of the sockets, timeout is NULL, so wait indefinitely
        printf("[3] Call select() and waiting.\n");
        activity = select(0, &readfds, &writefds, NULL, &timeout); // start up the listen system

        printf("[4] Wake up from select().\n");

        if(activity == SOCKET_ERROR){
            printf("select call failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        if(activity == 0){
            printf("No message: select() is waiting for 5 sec.\n");
        }

        // check serv_sd -> accept(), add new client into cli_sd[]
        if(FD_ISSET(serv_sd, &readfds)){ // confirm the set of socket descriptors
            cli_len = sizeof(cli);
            new_socket = accept(serv_sd, (struct sockaddr *) &cli, (int *) &cli_len);
            printf("New connection: socket fd is %d , ip is : %s , port : %d \n", new_socket, inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
            for(i=0; i<MAXCLI; i++){
                if(cli_sd[i] == 0){
                    cli_sd[i] = new_socket;
                    client_num++;
                    printf("The %d client socket is in cli_sd[%d]\n", client_num, i);
                    break;
                }
            }
        }

        // check each cli_sd client 1 presend in read sockets
        for(i=0; i<MAXCLI; i++){
            if(FD_ISSET(cli_sd[i], &readfds)){ // confirm the set of socket descriptors
                n = recv(cli_sd[i], str, MAXRECV, 0);
                if(n == SOCKET_ERROR){
                    int error_code = WSAGetLastError();
                    if(error_code == WSAECONNRESET){
                        // somebody disconnected, get its details and print
                        printf("Host disconnected unexpectedly.\n");
                        closesocket(cli_sd[i]);
                        cli_sd[i] = 0;
                        client_num--;
                    }
                    else{
                        printf("recv failed with error code : %d" , error_code);
                    }
                }
                if(n == 0){
                    // somebody disconnected, get its details and print
                    printf("Host disconnected.\n");
                    closesocket(cli_sd[i]);
                    cli_sd[i] = 0;
                    client_num--;
                }
                if(n > 0){
                    printf("recv from cli_sd[%d]: %s \n", i, str);
                    ready_to_send[i] = 1;
                }
            }
            if(FD_ISSET(cli_sd[i], &writefds)){ // confirm the set of socket descriptors
                send(cli_sd[i], str, strlen(str)+1, 0);
                ready_to_send[i] = 0;
            }
        }
    }

    closesocket(serv_sd);
    WSACleanup();
    system("pause");
}
