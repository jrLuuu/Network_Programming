#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024

int main(int argc, char** argv)
{
   SOCKET sd;
   struct sockaddr_in serv;
   int n,i;
   char str[1024]="How are you?";
   char str1[1024];

   WSADATA wsadata;
   WSAStartup(0x101,(LPWSADATA) &wsadata);

   sd = socket(AF_INET, SOCK_STREAM, 0);

   serv.sin_family = AF_INET;
   serv.sin_addr.s_addr = inet_addr("127.0.0.1");
   serv.sin_port = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv));
   printf("Client has connectted to Server.\n");
   printf("Waiting 10 secs on purpose...\n");
   Sleep(10000);

	for(;;){
        Sleep(3000);
	   	send(sd, str, strlen(str)+1, 0);

        int nError = WSAGetLastError();
        if(nError!=WSAEWOULDBLOCK && nError!=0){
            printf("Winsock error code:%d\n", nError);
            printf("Disconnected!");
            // close our socket entirely
            closesocket(sd);
            break;
        }
	    printf("Send every 3 secs: %s\n" ,str);
    }

    closesocket(sd);
    WSACleanup();
}
