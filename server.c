
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
#include"lib/common.h"
typedef enum
{

    false,
    true
}
bool;
void exitt(int clisocket){
    
}
typedef struct{
    char name[1024];
    int clisocket;
    int clientlenght;
    struct sockaddr_in client_addres;
    bool err;
}supcli;
typedef struct clilist{
    supcli* val;
    struct clilist* next ;
} clilist;
clilist *head = NULL;
#define letzero(s) (void)memset(s, 0, sizeof(s));
int client_socket,sock ;
void deleteclient(supcli* cli){
    clilist* a = head->next ;
    clilist* b = head ; 
    if(b->val == cli ){
        a = b;
        b = b->next;
        free(a);
    }
    else{

    while(a->val != cli && a->next != NULL){
        a = a->next;
        b = b->next;
    }
    b->next = a->next ;
    a->next = NULL;
    free(a);
    }
}
void clientlist(clilist**thead,supcli* client ){
    clilist *p = (clilist *)malloc(sizeof(clilist));
    if(p==NULL){
        printf("err");
    return;

    }


    p->val = client;
    p->next = *thead;
    *thead = p;
}
void resend(int clisocket,char* buffer){
    clilist *p = head;
    while(p!=NULL){
        if(p->val->clisocket != clisocket){
            send(p->val->clisocket, buffer, strlen(buffer)+1, 0);
        }
        p = p->next;
    }
    //printf("%s\n", buffer);
    //printf("admin : ");
}
    void justsned(char* mes){
     printf("%s\n", mes);

        clilist *p = head;
        while (p != NULL)
        {

            send(p->val->clisocket, mes, strlen(mes)+1, 0);
            p = p->next;
    }
    }
DWORD WINAPI spcread(LPVOID thrd){
    int client_socket = *((int *)thrd);
    char mes[1024];
   do{
    letzero(mes);
    recv(client_socket, mes, sizeof(mes), 0);
    resend(client_socket, mes);
    printf("\r%s\n", mes);
    printf("admin : ");
   } while (isStringeq(mes,"exit"));
}

DWORD WINAPI spcaccept(LPVOID thrd){

   while(true){
    supcli *client = (supcli*)malloc(sizeof(supcli));
    client->clientlenght = sizeof(client->client_addres);
    client->clisocket = accept(sock, (struct sockaddr *)&client->client_addres, &client->clientlenght);
    recv(client->clisocket, client->name, sizeof(client->name), 0);
    // strcpy(recv(client->clisocket , ),client->name );
    clientlist(&head, client);
    printf("%s\n", client->name);

    HANDLE threade;
    threade = CreateThread(NULL, 0, spcread, (LPVOID)&client->clisocket, 0, NULL);
        if (threade = NULL)
    {
        fprintf(stderr, "404 err hapend ... \n");
    }
    WaitForSingleObject( threade,  INFINITE);
    close(client->clisocket);

    }
}
DWORD WINAPI  spcwrite(LPVOID thrd){
do{

    clilist *p = head;
    char messa[1024];
    char buffer[1024];
    letzero(buffer);
    printf("admin : " );
    fgets(buffer, sizeof(buffer), stdin);
    strtok(buffer, "\n");
    sprintf(messa, "admin : %s", buffer);
    strtok(messa, "\n");
    justsned( messa);
} while (head);
}

int main(){
 WSADATA wsaData; // Windows socket initialization data
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        fprintf(stderr, "Failed to initialize Winsock\n");
        return 1;
    }


    char buffer[1024];

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

    if (bind(sock,(struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        printf("[-] bind failed\n");
        return 1;
    }

    if (listen(sock, 5) < 0)
    {
        printf("[-] listen failed\n");
        return 1;
    }


    HANDLE theardsHa[2];

    theardsHa[0] = CreateThread(NULL, 0, spcaccept, NULL, 0, NULL);
    theardsHa[1] = CreateThread(NULL, 0, spcwrite, NULL, 0, NULL);

    if (theardsHa[0] == NULL || theardsHa[1] == NULL)
    {
        fprintf(stderr, "404 err hapend ... \n");
    }
    WaitForMultipleObjects(2, theardsHa, TRUE, INFINITE);
}