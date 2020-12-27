#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>
#define PORT 6666
#define SERVER "127.0.0.1"
int main()
{
    int lfd,cfd;
    struct sockaddr_in addr_serv,addr_client;
    socklen_t len;
    int n;
    char BUF[1000]={0};
    lfd = socket(AF_INET,SOCK_STREAM,0);
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(PORT);
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);             //sin_addr shi struct
    bind(lfd,(struct sockaddr*)&addr_serv,sizeof(addr_serv));
    listen(lfd,128);
    len = sizeof(addr_client);
    cfd = accept(lfd,(struct sockaddr*)&addr_client,&len);  //addr_client  out_arg , len in_out_arg

    while(1)
    {
        n=read(cfd,BUF,1000);
        write(STDOUT_FILENO,BUF,n); //write to server screen
        for(int i=0;i<n;i++)
        {
            BUF[i] = toupper(BUF[i]);
        }
        write(cfd,BUF,sizeof(BUF));
       

    }

}