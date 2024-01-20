

int isStringeq(char *str1, char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            return 0;
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}


    // strcpy(client->name ,"");
    // printf("[+] connect established from %s\n", inet_ntoa(client_address.sin_addr));
    // memset(client->name, 0, 1024);
    // // // letzero(buffer);
    // recv(sock, client->name, sizeof(client->name), 0);
    // printf("%s\n", buffer);