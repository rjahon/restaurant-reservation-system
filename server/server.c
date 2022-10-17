#include "functions.h"

int main(int argc, char const *argv[])
{
    initDB();      // Initializing the Mysql database
    initSockets(); // Initializing socketss
    for (;;)
    {
        acceptConnection(); // Accept Connection
        if ((childpid = fork()) == 0)
        {
            close(server_fd);
            for (;;)
            {
                recv(sock, buffer, 1024, 0);
                if (strcmp(buffer, ":exit") == 0)
                {
                    printf("Disconnected from %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    break;
                }
                else
                {
                    printf("Client: %s\n", buffer);
                    send(sock, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                    for (;;)
                    {
                        memset(buffer, 0, sizeof(buffer));
                        valread = read(sock, buffer, 1024);
                        strcpy(query, buffer);
                        int i = 0;
                        while (buffer[i++] != '/')
                            ;
                        buffer[i - 1] = '\0';
                        printf("%s\n", buffer);

                        if (strcmp(buffer, "queryUserCancelReserv") == 0)
                        {
                            queryUserCancelReserv();
                        }
                        else if (strcmp(buffer, "queryUserReservations") == 0)
                        {
                            queryUserReservations();
                        }
                        else if (strcmp(buffer, "queryReservationsAll") == 0)
                        {
                            queryReservationsAll();
                        }
                        else if (strcmp(buffer, "queryNewReservation") == 0)
                        {
                            queryNewReservation();
                        }
                        else if (strcmp(buffer, "queryLoginValidate") == 0)
                        {
                            queryLoginValidate();
                        }
                        else if (strcmp(buffer, "queryAdminCancel") == 0)
                        {
                        }
                        else if (strcmp(buffer, "queryNewUser") == 0)
                        {
                            queryNewUser();
                        }
                        else
                        {
                            printf("Bad Request\n");
                        }
                    }
                }
            }
        }
    }

    return 0;
}
