#include<stdio.h>
#include <winsock2.h> //sock api's
#pragma comment(lib,"ws2_32.lib") //winscok library

int main()
{
  WSADATA  wsa;
  SOCKET s; //Socket desc
  int status;
  SOCKET s2;
  struct sockaddr client;
  int size = sizeof(client);
  struct sockaddr_in myserver;


   printf("\nInitilialising winsock......");
   if( WSAStartup (MAKEWORD(2,2),&wsa) != 0 )
   {
       printf(" Failed. Error Code: %d", WSAGetLastError());
       return 1;
   }

printf("intialised.\n");
 //creat socket
 if((s = socket(AF_INET, SOCK_STREAM ,0))==INVALID_SOCKET)
 {
     printf(" COULD not craet ,%d", WSAGetLastError());
 }
     printf("socket creat");

 myserver.sin_family=AF_INET;
 myserver.sin_port =htons(5000);
 myserver.sin_addr.s_addr = inet_addr("192.168.3.19");
  printf("f");
 status = bind(s,(struct sockaddr *)&myserver ,sizeof(myserver) );
    if( status < 0 )
    {
        printf("Bind failed");
    }
 int st= listen(s,3);

     printf("%i",st);

      char recv_buf[2000]="";


 s2 = accept(s,(struct sockaddr *)&client,&size);

 while(1)
 {

 //connect(s,(struct sockaddr *)&server,sizeof(server));
 //char massage[50] ="GET /HTTP/1.1\r\n\r\n";

 //send(s,massage,strlen(massage),0);
// printf("B");
 recv(s2,recv_buf,sizeof(recv_buf),0);
printf("%s",recv_buf);
 }

 closesocket(s);
return 0;

}
