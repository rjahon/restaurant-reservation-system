
#include <stdbool.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 4444

// MySQL
static char *host = "localhost";
static char *user = "root";
static char *pass = "MyPassword2.";
static char *dbname = "test";
static MYSQL *con;

// Sockets
unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;

pid_t childpid;

struct sockaddr_in serverAddr;
struct sockaddr_in address;

int server_fd;
int sock;
int valread;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = {0};
char schat[1024];
socklen_t addr_size;

char query[100];