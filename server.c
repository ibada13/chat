#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<winsock2.h>

int main(){
 WSADATA wsaData; // Windows socket initialization data
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        fprintf(stderr, "Failed to initialize Winsock\n");
        return 1;
    }

    int sock, client_socket;
    char order[1024];
    char response[18384];
  
    struct sockaddr_in server_address, client_address;
   
    int opval = 1;
    int client_length; // Change the type from socklen_t to int
    printf("[+] server is on listen mode \n");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&opval, sizeof(opval)) < 0)
    {
        printf("[-] some problem in tcp protocol connection\n");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.8.101");
    server_address.sin_port = htons(50005);

    if (bind(sock,&server_address, sizeof(server_address)) < 0)
    {
        printf("[-] bind failed\n");
        return 1;
    }

    if (listen(sock, 5) < 0)
    {
        printf("[-] listen failed\n");
        return 1;
    }

    client_length = sizeof(client_address);
    client_socket = accept(sock, (struct sockaddr *)&client_address, &client_length);
    printf("[+] connect established from %s\n", inet_ntoa(client_address.sin_addr));
}