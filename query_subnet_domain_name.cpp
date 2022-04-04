#include <iostream>
#include <winsock.h>
#include <sstream>
using namespace std;

int main()
{
    WSADATA wsadata;
    WSAStartup(0x10l, (LPWSADATA) &wsadata);

    char req_ip[32];
    cout << "Input IP addr: ";
    string IP;
    cin >> IP;
    cout << endl;

    for(int i=1; i<255; i++){
        stringstream ss;
        string result;
        result = IP + "." + to_string(i);
        ss << result;
        ss >> req_ip;

        LPHOSTENT hp;
        struct in_addr sAddr;
        sAddr.s_addr = inet_addr(req_ip);
        hp = gethostbyaddr ((LPSTR) &sAddr, sizeof(sAddr), AF_INET);

        if(hp == NULL)
            cout << "get hp error, code: " << WSAGetLastError() << endl;
        else
            cout << req_ip << "'s host name: " << hp->h_name << endl;
    }

    return 0;
}
