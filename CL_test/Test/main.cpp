#include <stdio.h>
#include <winsock2.h>   /* Socket apis */

#pragma comment(lib,"ws_32.lib")    /* Winsock library */

int main()
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;

    /* Needed for Socket programming on windows */
    printf("\nInitializing Winsock..");
    if( WSAStartup (MAKEWORD(2,2),&wsa) != 0 )
    {
        printf(" Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("\nInitialised. \n");

    int fake_data = 20;
    /* Loop here forever */
    while(1)
    {
        fake_data += 5;
        if(fake_data >= 60)
        {
            fake_data = 20;
        }
        /* Create a socket*/
        if(( s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET )
        {
            printf(" Could not create socket : %d", WSAGetLastError());
        }
        printf("Socket created. \n");


        /* Fill in the Socket descriptor table */
        server.sin_addr.s_addr = inet_addr("184.106.153.149");              /* Thingspeak IP */
        server.sin_family = AF_INET;                                        /* TCP */
        server.sin_port = htons( 80 );                                      /* Port 80 for http */

        /* Connect to the server */
        if( ( connect(s, ( struct sockaddr * ) &server, sizeof(server)) ) < 0 )
        {
            printf("Failed to connect. \n ");
        }
        else
        {
            printf("Connected successfully. \n");
        }

        /* Add the sensor value to the API get request */
        char message[100]; /*Create a buffer to hold the modified string */
        sprintf(message, "GET /update?api_key=XINGNGFF7I8UXCWB&field1=%d\r\n\r\n",fake_data);   /* Place the new string with the sensor data in the buffer */


        /* Send the API write message */
        int count = send(s, message, strlen(message), 0);
        if( count < 0 )
        {
            printf("Sending failed \n");
        }
        else
        {
            printf("Sending sucess, %d bytes sent \n", count);
        }


        char server_reply[2000];
        int recv_size;
        //Receive a reply from the server
        if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
        {
            puts("recv failed");
        }

        /* Print the server reply */
        puts(server_reply);

        closesocket(s);
        Sleep(20000);   /* 15 sec delay for free APIs */
    }

return 0;

}
