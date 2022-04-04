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
                    s = "人生如花,愛便是那花蜜。";
                }
                else if(x%5 == 1)
                {
                    s = "重要的事是永遠不要停止發問。";
                }
                else if(x%5 == 2)
                {
                    s = "勝利屬於不屈不撓，堅忍不拔的人。";
                }
                else if(x%5 == 3)
                {
                    s = "生命不是勇於冒險，就是荒廢生命。";
                }
                else if(x%5 == 4)
                {
                    s = "偉大的人,是精神力量強於物質力量。";
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

