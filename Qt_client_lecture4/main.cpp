#include <stdio.h>
#include <winsock2.h>   /* Socket apis */

#pragma comment(lib,"ws_32.lib")    /* Winsock library */

int main()
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;

    printf("\nInitializing Winsock..");
    if( WSAStartup (MAKEWORD(2,2),&wsa) != 0 )
    {
        printf(" Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }

    printf("\nInitialised. \n");

    /* Create a socket */
    if(( s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET )
    {
        printf(" Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created .\n");

    server.sin_addr.s_addr = inet_addr("192.168.3.19");
    server.sin_family = AF_INET;    /* IPv4 */
    server.sin_port = htons( 5000 );  /* Port 1000 for http */

    int status = connect(s, ( struct sockaddr * ) &server, sizeof(server));
    if( status <0 )
    {
        printf("Failed \t ");
    }
    char message[50] = "Hello";

    while(1)
{
    printf("Connect here \t");

    printf("Sending\t");
    send(s, message, strlen(message), 0);


/*    char recv_buf[2000] = "";
    printf("Recieving\t");

    recv(s, recv_buf, 2000, 0 );
    puts(recv_buf);
    printf("finished\n");
*/
    Sleep(1000);

}
    closesocket(s);
    return 0;
}

