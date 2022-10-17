#include "config.h"

void initDB()
{
    con = mysql_init(NULL);
    if (!(mysql_real_connect(con, host, user, pass, dbname, port, unix_socket, flag)))
    {
        fprintf(stderr, "\nError: %s [%d] \n", mysql_error(con), mysql_errno(con));
        exit(1);
    }
}

void acceptConnection()
{
    sock = accept(server_fd, (struct sockaddr *)&address, &addr_size);
    if (socket < 0)
    {
        exit(1);
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
}

void initSockets()
{
    printf("Creating Server Socket ...\n");
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.153.123");

    printf("Binding Server Socket to Port 8080 ...\n");
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Server Listening on Port 8080 for New Connection ...\n");
    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed ");
        exit(EXIT_FAILURE);
    }
    printf("Server Accepted New Connection From a Client on Port 8080 ...\n");
}

void queryNewUser()
{
    printf("Query New User: %s\n\n", query);
    char user_name[20];
    char password[20];
    memset(user_name, 0, 20);
    memset(password, 0, 20);

    int n1 = 0, n2 = 0, n3 = 0;
    for (int i = 0; i < strlen(query); i++)
    {
        if (query[i] == '/')
        {
            if (n1 == 0)
                n1 = i;
            else if (n2 == 0)
                n2 = i;
            else if (n3 == 0)
                n3 = i;
        }
    }
    strncpy(user_name, query + n1 + 1, n2 - n1 - 1);
    strncpy(password, query + n2 + 1, n3 - n2 - 1);
    user_name[strlen(user_name)] = '\0';
    password[strlen(password)] = '\0';

    printf("user_name: %s\n", user_name);
    printf("password: %s\n", password);

    char sqlQuery[500];
    memset(sqlQuery, 0, 500);

    sprintf(sqlQuery, "INSERT INTO users (user_name, password) VALUES ('%s', '%s');", user_name, password);
    printf("SQL: %s\n", sqlQuery);
    mysql_query(con, sqlQuery);
}

void queryLoginValidate()
{
    printf("Query Login Validate: %s\n", query);
    char user_name[20];
    char password[20];
    memset(user_name, 0, 20);
    memset(password, 0, 20);

    int n1 = 0, n2 = 0, n3 = 0;
    for (int l = 0; l < strlen(query); l++)
    {
        if (query[l] == '/')
        {
            if (n1 == 0)
                n1 = l;
            else if (n2 == 0)
                n2 = l;
            else if (n3 == 0)
                n3 = l;
        }
    }
    strncpy(user_name, query + n1 + 1, n2 - n1 - 1);
    strncpy(password, query + n2 + 1, n3 - n2 - 1);
    user_name[strlen(user_name)] = '\0';
    password[strlen(password)] = '\0';

    printf("user_name: %s\n", user_name);
    printf("password: %s\n", password);

    MYSQL_RES *res;
    MYSQL_ROW row;

    char sqlQueryUser[500];
    memset(sqlQueryUser, 0, 500);

    sprintf(sqlQueryUser, "SELECT user_name FROM users WHERE user_name='%s';", user_name);
    printf("SQL: %s\n", sqlQueryUser);
    mysql_query(con, sqlQueryUser);

    res = mysql_store_result(con);

    char user_name_db[20];
    memset(user_name_db, 0, 20);

    while (row = mysql_fetch_row(res))
    {
        sprintf(user_name_db, "%s", (const char *)row[0]);
    }
    mysql_free_result(res);

    char sqlQueryPass[500];
    memset(sqlQueryPass, 0, 500);

    sprintf(sqlQueryPass, "SELECT password FROM users WHERE password='%s';", password);
    printf("SQL: %s\n", sqlQueryPass);
    mysql_query(con, sqlQueryPass);

    res = mysql_store_result(con);

    char password_db[20];
    memset(password, 0, 20);

    while (row = mysql_fetch_row(res))
    {
        sprintf(password_db, "%s", (const char *)row[0]);
    }

    printf("%s == %s ?\n", user_name_db, user_name);
    printf("%s == %s ?\n", password_db, password);

    if (strcmp(user_name_db, user_name) == 0 &&
        strcmp(password_db, password) == 0)
    {
        send(sock, "Right", strlen("Right"), 0);
        printf("Send: Right\n");
    }
    else
    {
        send(sock, "Wrong", strlen("Wrong"), 0);
        printf("Send: Wrong\n");
    }
}

void queryUserCancelReserv()
{
    printf("Query User Cancel Reserv: %s\n", query);

    char reserv_id[12];
    memset(reserv_id, 0, 12);

    int n1 = 0, n2 = 0;
    for (int l = 0; l < strlen(query); l++)
    {
        if (query[l] == '/')
        {
            if (n1 == 0)
                n1 = l;
            else if (n2 == 0)
                n2 = l;
        }
    }
    strncpy(reserv_id, query + n1 + 1, n2 - n1 - 1);
    reserv_id[strlen(reserv_id)] = '\0';

    printf("reserv_id: %s\n", reserv_id);

    char sqlQuery[500];
    memset(sqlQuery, 0, 500);

    sprintf(sqlQuery, "DELETE FROM reserv WHERE reserv_id='%s';", reserv_id);
    printf("SQL: %s\n", sqlQuery);
    mysql_query(con, sqlQuery);
}

void queryUserReservations()
{
    printf("Query User Reservations: %s\n", query);

    char user_name[20];
    memset(user_name, 0, 20);

    int n1 = 0, n2 = 0;
    for (int l = 0; l < strlen(query); l++)
    {
        if (query[l] == '/')
        {
            if (n1 == 0)
                n1 = l;
            else if (n2 == 0)
                n2 = l;
        }
    }
    strncpy(user_name, query + n1 + 1, n2 - n1 - 1);
    user_name[strlen(user_name)] = '\0';

    printf("user_name: %s\n", user_name);

    char userReserv[500];
    memset(userReserv, 0, 500);

    sprintf(userReserv, "SELECT * FROM reserv WHERE user_name='%s';", user_name);
    printf("SQL: %s\n", userReserv);
    mysql_query(con, userReserv);

    MYSQL_RES *res;
    MYSQL_ROW row;

    res = mysql_store_result(con);
    char labelText[2048] = ".";
    while (row = mysql_fetch_row(res))
    {
        for (int i = 0; i < 8; i++)
        {
            strcat(labelText, row[i]);
            strcat(labelText, "\t\t");
        }
        strcat(labelText, "\t\t\t\n");
    }
    printf("Send: %s", labelText);
    send(sock, labelText, strlen(labelText), 0);
}

void queryReservationsAll()
{
    printf("Query Reservations All: %s\n", query);

    char allReserv[100] = "SELECT * FROM reserv;";
    printf("SQL: %s\n", allReserv);
    mysql_query(con, allReserv);

    MYSQL_RES *res;
    MYSQL_ROW row;

    res = mysql_store_result(con);
    char labelText[2048] = ".";
    while (row = mysql_fetch_row(res))
    {
        for (int i = 0; i < 8; i++)
        {
            strcat(labelText, row[i]);
            strcat(labelText, "\t");
        }
        strcat(labelText, "\t\t\n");
    }
    printf("Send: %s\n", labelText);
    send(sock, labelText, strlen(labelText), 0);
}

void queryNewReservation()
{
    printf("Query New Reservation: %s\n", query);

    char user_name[20];
    char theme[32];
    char entertainment[32];
    char day[32];
    char month[32];
    char food[32];
    char music[32];
    memset(user_name, 0, 20);
    memset(theme, 0, 32);
    memset(entertainment, 0, 32);
    memset(day, 0, 32);
    memset(month, 0, 32);
    memset(food, 0, 32);
    memset(music, 0, 32);

    int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0, n7 = 0, n8 = 0;
    for (int i = 0; i < strlen(query); i++)
    {
        if (query[i] == '/')
        {
            if (n1 == 0)
                n1 = i;
            else if (n2 == 0)
                n2 = i;
            else if (n3 == 0)
                n3 = i;
            else if (n4 == 0)
                n4 = i;
            else if (n5 == 0)
                n5 = i;
            else if (n6 == 0)
                n6 = i;
            else if (n7 == 0)
                n7 = i;
            else if (n8 == 0)
                n8 = i;
        }
    }
    strncpy(user_name, query + n1 + 1, n2 - n1 - 1);
    strncpy(theme, query + n2 + 1, n3 - n2 - 1);
    strncpy(entertainment, query + n3 + 1, n4 - n3 - 1);
    strncpy(day, query + n4 + 1, n5 - n4 - 1);
    strncpy(month, query + n5 + 1, n6 - n5 - 1);
    strncpy(food, query + n6 + 1, n7 - n6 - 1);
    strncpy(music, query + n7 + 1, n8 - n7 - 1);
    user_name[strlen(user_name)] = '\0';
    theme[strlen(theme)] = '\0';
    entertainment[strlen(entertainment)] = '\0';
    day[strlen(day)] = '\0';
    month[strlen(month)] = '\0';
    food[strlen(food)] = '\0';
    music[strlen(music)] = '\0';

    printf("user_name: %s\n", user_name);
    printf("theme: %s\n", theme);
    printf("entertainment: %s\n", entertainment);
    printf("day: %s\n", day);
    printf("month: %s\n", month);
    printf("food: %s\n", food);
    printf("music: %s\n", music);

    char sqlQuery[500];
    memset(sqlQuery, 0, 500);

    sprintf(sqlQuery,
            "INSERT INTO reserv "
            "(user_name, theme, entertainment, day, month, food, music) VALUES "
            "('%s', '%s', '%s', '%s', '%s', '%s', '%s');",
            user_name, theme, entertainment, day, month, food, music);
    printf("SQL: %s\n", sqlQuery);
    mysql_query(con, sqlQuery);
}