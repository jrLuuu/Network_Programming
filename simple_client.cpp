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
        cout << "[���~] ��J���榡���~�A�Э��s��J" << endl;
    }

    return 0;
}

void welcome_msg()
{
    cout << "+++++++++++++++++++++++++++++++++++" << endl;
    cout << "| �п�J�A�Ȫ��N��(1~5)�H����A�� |" << endl;
    cout << "| 1. �^���A�� (Echo)              |" << endl;
    cout << "| 2. ���A�� (Discard)           |" << endl;
    cout << "| 3. ����ɶ��A�� (Daytime)       |" << endl;
    cout << "| 4. �C��@�y (QUOTE)             |" << endl;
    cout << "| 5. �r�����;� (CHARGEN)         |" << endl;
    cout << "+++++++++++++++++++++++++++++++++++" << endl;
}

void result_msg()
{
    cout << "++++++++++++++++++" << endl;
    cout << "|    ���浲�G    |" << endl;
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
        cout << "[�ǰe���e] " << send_str << endl;
        cout << "[�ǰe���e����] " << strlen(send_str) + 1 << "bytes" << endl;
        n_bytes=recv(sd, recv_str, MAXLINE, 0); // receive by echo server
        cout << "[�^�����e] " << recv_str << endl;
        cout << "[�^�����e����] " << n_bytes << "bytes" << endl;
    }
    else if(port == 9)
    {
        send(sd, send_str, strlen(send_str)+1, 0);
        cout << "[�ǰe���e] " << send_str << endl;
        cout << "[�ǰe���e����] " << strlen(send_str) + 1 << "bytes" << endl;
        cout << "[�^�����e] " << recv_str << endl;
        cout << "[�^�����e����] " << n_bytes << "bytes" << endl;
    }
    else if(port == 13)
    {
        cout << "[�ǰe���e] " << " " << endl;
        cout << "[�ǰe���e����] " << n_bytes << "bytes" << endl;
        n_bytes=recv(sd, recv_str, MAXLINE, 0);
        cout << "[�^�����e] " << recv_str;
        cout << "[�^�����e����] " << n_bytes << "bytes" << endl;
    }
    else if(port == 17)
    {
        cout << "[�ǰe���e] " << " " << endl;
        cout << "[�ǰe���e����] " << n_bytes << "bytes" << endl;
        n_bytes=recv(sd, recv_str, MAXLINE, 0);
        cout << "[�^�����e] " << recv_str << endl;
        cout << "[�^�����e����] " << n_bytes << "bytes" << endl;
    }
    else if(port == 19)
    {
        cout << "[�ǰe���e] " << " " << endl;
        cout << "[�ǰe���e����] " << n_bytes << "bytes" << endl;
        n_bytes=recv(sd, send_str, MAXLINE, 0);
        cout << "[�^�����e] " << send_str << endl;
        cout << "[�^�����e����] " << n_bytes << "bytes" << endl;
    }

    closesocket(sd); // close TCP socket
    WSACleanup(); // finish WinSock DLL
}
