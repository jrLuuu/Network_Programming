#include <iostream>
#include <string.h>
#include <winsock.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>

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
        service_func(1);
        break;
    case 2:
        service_func(2);
        break;
    case 3:
        service_func(3);
        break;
    case 4:
        service_func(4);
        break;
    case 5:
        service_func(5);
        break;
    default:
        cout << "error input" << endl;
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

void service_func(int service)
{
    WSADATA wsadata;
    SOCKET sd, clnt_sd;
    struct sockaddr_in serv, clnt;
    int n_bytes = 1; // '\'
    char str[100];

    WSAStartup(0x101,(LPWSADATA) &wsadata); // register WinSock DLL
    sd=socket(AF_INET, SOCK_STREAM, 0); // open TCP socket

    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *) &serv, sizeof(serv)); // bind the port for socket

    result_msg();

    while(1)
    {
        listen(sd,5); // waiting for connection
        int clnt_len = sizeof(clnt);

        cout << "Server waits." << endl;
        clnt_sd = accept(sd, (struct sockaddr *) &clnt, &clnt_len); // accept the connection

        while(1)
        {
            if(service == 1)
            {
                n_bytes = recv(clnt_sd, str, 100, 0);
                if(n_bytes>0 && str[0]=='.')
                    break;
                str[n_bytes] = '\0'; // in order to print out the string correctly
                cout << "Server receive: " << str << endl;
                send(clnt_sd, str, n_bytes+1, 0);
            }

            else if(service == 2)
            {
                n_bytes = recv(clnt_sd, str, 100, 0);
                if(n_bytes>0 && str[0]=='.')
                    break;
                str[n_bytes] = '\0';
                cout << "Server receive: " << str << endl;
            }

            else if(service == 3)
            {
                time_t rawtime;
                struct tm * timeinfo;
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                cout << "Server sends time: " << asctime(timeinfo) << endl;
                send(clnt_sd, asctime(timeinfo), strlen(asctime(timeinfo))+1, 0);
                break;
            }

            else if(service == 4)
            {
                srand(time(NULL));
                int x = rand();
                string s;

                if(x%5 == 0)
                {
                    s = "�H�ͦp��,�R�K�O����e�C";
                }
                else if(x%5 == 1)
                {
                    s = "���n���ƬO�û����n����o�ݡC";
                }
                else if(x%5 == 2)
                {
                    s = "�ӧQ�ݩ󤣩}�����A��Ԥ��ު��H�C";
                }
                else if(x%5 == 3)
                {
                    s = "�ͩR���O�i��_�I�A�N�O��o�ͩR�C";
                }
                else if(x%5 == 4)
                {
                    s = "���j���H,�O�믫�O�q�j�󪫽�O�q�C";
                }

                stringstream ss;
                ss << s;
                ss >> str;

                cout << "Server sends goodwords: " << str << endl;
                send(clnt_sd, str, s.length(), 0);
                break;
            }

            else if(service == 5)
            {
                string s = "!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefg";
                stringstream ss;
                ss << s;
                ss >> str;

                cout << "Server sends: " << str << endl;
                send(clnt_sd, str, s.length(), 0);
            }
        }
        closesocket(clnt_sd);
    }
    closesocket(sd);
    WSACleanup();
}

