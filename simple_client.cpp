#include <iostream>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024
using namespace std;

void welcome_msg();
void result_msg();
void service_func(int);

int main()
{
    welcome_msg();
    int service = 0;
    cin >> service;
    switch (service)
    {
    case 1:
        service_func(7);
        break;
    case 2:
        service_func(9);
        break;
    case 3:
        service_func(13);
        break;
    case 4:
        service_func(17);
        break;
    case 5:
        service_func(19);
        break;
    default:
        cout << "[錯誤] 輸入的格式錯誤，請重新輸入" << endl;
    }

    return 0;
}

void welcome_msg()
{
    cout << "+++++++++++++++++++++++++++++++++++" << endl;
    cout << "| 請輸入服務的代號(1~5)以執行服務 |" << endl;
    cout << "| 1. 回應服務 (Echo)              |" << endl;
    cout << "| 2. 丟棄服務 (Discard)           |" << endl;
    cout << "| 3. 日期時間服務 (Daytime)       |" << endl;
    cout << "| 4. 每日一句 (QUOTE)             |" << endl;
    cout << "| 5. 字元產生器 (CHARGEN)         |" << endl;
    cout << "+++++++++++++++++++++++++++++++++++" << endl;
}

void result_msg()
{
    cout << "++++++++++++++++++" << endl;
    cout << "|    執行結果    |" << endl;
    cout << "++++++++++++++++++" << endl;
}

void service_func(int port)
{
    WSADATA wsadata;
    SOCKET sd;
    struct sockaddr_in serv;
    char send_str[1024] = "I love NCYU CSIE";
    char recv_str[1024];
    int n_bytes = 1; // '\'

    WSAStartup(0x101,(LPWSADATA) &wsadata); // register WinSock DLL
    sd=socket(AF_INET, SOCK_STREAM, 0); // open TCP socket

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(port);

    connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // connect to echo server
    result_msg();

    if(port == 7)
    {
        send(sd, send_str, strlen(send_str)+1, 0); // send str to echo server
        cout << "[傳送內容] " << send_str << endl;
        cout << "[傳送內容長度] " << strlen(send_str) + 1 << "bytes" << endl;
        n_bytes=recv(sd, recv_str, MAXLINE, 0); // receive by echo server
        cout << "[回應內容] " << recv_str << endl;
        cout << "[回應內容長度] " << n_bytes << "bytes" << endl;
    }
    else if(port == 9)
    {
        send(sd, send_str, strlen(send_str)+1, 0);
        cout << "[傳送內容] " << send_str << endl;
        cout << "[傳送內容長度] " << strlen(send_str) + 1 << "bytes" << endl;
        cout << "[回應內容] " << recv_str << endl;
        cout << "[回應內容長度] " << n_bytes << "bytes" << endl;
    }
    else if(port == 13)
    {
        cout << "[傳送內容] " << " " << endl;
        cout << "[傳送內容長度] " << n_bytes << "bytes" << endl;
        n_bytes=recv(sd, recv_str, MAXLINE, 0);
        cout << "[回應內容] " << recv_str;
        cout << "[回應內容長度] " << n_bytes << "bytes" << endl;
    }
    else if(port == 17)
    {
        cout << "[傳送內容] " << " " << endl;
        cout << "[傳送內容長度] " << n_bytes << "bytes" << endl;
        n_bytes=recv(sd, recv_str, MAXLINE, 0);
        cout << "[回應內容] " << recv_str << endl;
        cout << "[回應內容長度] " << n_bytes << "bytes" << endl;
    }
    else if(port == 19)
    {
        cout << "[傳送內容] " << " " << endl;
        cout << "[傳送內容長度] " << n_bytes << "bytes" << endl;
        n_bytes=recv(sd, send_str, MAXLINE, 0);
        cout << "[回應內容] " << send_str << endl;
        cout << "[回應內容長度] " << n_bytes << "bytes" << endl;
    }

    closesocket(sd); // close TCP socket
    WSACleanup(); // finish WinSock DLL
}
