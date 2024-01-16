#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock2.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#define letzero(s) (void)memset(s, 0, sizeof(s));

int sock;
char name[1024];
char messa[1024];
DWORD WINAPI  spcwrite(LPVOID thread){
while (1)
{
        char buffer[1024];
    letzero(buffer);
    letzero(messa);
    printf("%s : ", name);
    fgets(buffer, sizeof(buffer), stdin);
    sprintf(messa, "%s : %s", name, buffer);
    strtok(messa, "\n");
    // printf("%s\n", messa);
    send(sock, messa, sizeof(messa), 0);
}

}
DWORD WINAPI  spcread(LPVOID thread){
    while(1){
    char mes[1024];
    letzero(mes);
    recv(sock, mes, sizeof(mes), 0);
    printf("\r%s\n", mes);
    printf("%s : ",name);
    }
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            // Handle the close message if needed
            MessageBox(hwnd, "Close button clicked! Window will close.", "Close Message", MB_OK | MB_ICONINFORMATION);
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            // Handle the destroy message (window is being destroyed)
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void MyFunction() {
    // Your function logic goes here
    MessageBox(NULL, "MyFunction called after window close.", "Function After Close", MB_OK | MB_ICONINFORMATION);
}
int main(){
     
    
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
    while (connect(sock,(struct sockaddr*)&ServAddr, sizeof(ServAddr)) != 0)
    {
        Sleep(5);
        
    };
    char first[1024];
    printf("you have to enter your name : ");
    fgets(name, sizeof(name), stdin);
    strtok(name, "\n");
    // letzero()
    sprintf(first, "%s has enter the char", name);
    strtok(first, "\n");
    send(sock, first, sizeof(first), 0);

    HANDLE theardsHa[2];

    theardsHa[0] = CreateThread(NULL, 0, spcwrite, NULL, 0, NULL);
    theardsHa[1] = CreateThread(NULL, 0, spcread, NULL, 0, NULL);

    if (theardsHa[0] == NULL || theardsHa[1] == NULL)
    {
        fprintf(stderr, "404 err hapend ... \n");
    }
    WaitForMultipleObjects(2, theardsHa, TRUE, INFINITE);
    closesocket(sock);
    WSACleanup();
    exit(0);
    MyFunction();
}