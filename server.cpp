#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <sstream>

using namespace std;
int main(){
	WSADATA wsadata;
	SOCKET sd, clnt_sd0, clnt_sd1, clnt_sd2, clnt_sd3;
	struct sockaddr_in serv, clnt0, clnt1, clnt2, clnt3;
	int i, n;
	char str[100];

	WSAStartup(0x101,&wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sd, (struct sockaddr *) &serv, sizeof(serv));

	listen(sd,5);
	int clnt_len1 = sizeof(clnt1);
	int clnt_len2 = sizeof(clnt2);
	int clnt_len3 = sizeof(clnt3);
	printf("Server waits.\n");
	clnt_sd1 =  accept(sd, (struct sockaddr *) &clnt1, &clnt_len1 );
	printf("(1) 1 connection.\n");
	clnt_sd2 =  accept(sd, (struct sockaddr *) &clnt2, &clnt_len2 );
	printf("(2) 2 connections.\n");
	clnt_sd2 =  accept(sd, (struct sockaddr *) &clnt3, &clnt_len3 );
	printf("(3) 3 connections.\n");

	int clnt_len0 = sizeof(clnt0);
	while(1){
		clnt_sd0 = accept(sd, (struct sockaddr *) &clnt0, &clnt_len0 );
		n = recv(clnt_sd0,str, 100, 0);
		closesocket(clnt_sd0);
		printf("ser_recv: %s\n",str);
		stringstream ss;
		string stringStr;
		ss << str;
		ss >> stringStr;
		if (stringStr == "bullshit"){
            stringstream sss;
            string stringCleanStr = "bullsxxt";
            stringStr = stringCleanStr;
            sss << stringStr;
            sss >> str;
            stringStr = "";
		}
		else if(stringStr == "bye"){
            break;
        }
		send(clnt_sd1,str, strlen(str)+1, 0);
		send(clnt_sd2,str, strlen(str)+1, 0);
		send(clnt_sd3,str, strlen(str)+1, 0);
	}
	closesocket(sd);
	closesocket(clnt_sd0);
	closesocket(clnt_sd1);
	closesocket(clnt_sd2);
	closesocket(clnt_sd3);
	WSACleanup();
}
