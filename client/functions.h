#include "config.h"

void initSocketConnection()
{
    printf("Creating Client Socket ...\n");
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Defining Client Socket Family, Address & Port ...\n");
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("Invalid address/Address not supported\n");
        exit(EXIT_FAILURE);
    }
    printf("Client Connection on Port 8080 to Communicate with Server ...\n");
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }

    send(sock, "ping", strlen("ping"), 0);
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    memset(buffer, 0, sizeof(buffer));
    // memset(cchat, 0, sizeof(cchat));
}

void initGUI(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("gui.glade");

    // initialize the pages --->
    welcome_page = GTK_WIDGET(gtk_builder_get_object(builder, "welcome_page"));
    admin_authorization_page = GTK_WIDGET(gtk_builder_get_object(builder, "admin_authorization_page"));
    user_authorization_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_authorization_page"));
    user_login_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_page"));
    admin_menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "admin_menu_page"));
    user_menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_menu_page"));
    user_register_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_register_page"));
    bookingsystem_page = GTK_WIDGET(gtk_builder_get_object(builder, "bookingsystem_page"));
    user_reservations_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_reservations_page"));
    user_cancel_reserv_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_reserv_page"));
    admin_reservations_page = GTK_WIDGET(gtk_builder_get_object(builder, "admin_reservations_page"));
    admin_cancel_reserv_page = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_reserv_page"));
    // <---

    // position the pages --->
    gtk_window_move(GTK_WINDOW(welcome_page), 700, 200);
    gtk_window_move(GTK_WINDOW(admin_authorization_page), 700, 250);
    gtk_window_move(GTK_WINDOW(user_authorization_page), 700, 250);
    gtk_window_move(GTK_WINDOW(user_login_page), 700, 250);
    gtk_window_move(GTK_WINDOW(admin_menu_page), 700, 250);
    gtk_window_move(GTK_WINDOW(user_menu_page), 700, 250);
    gtk_window_move(GTK_WINDOW(user_register_page), 700, 250);
    gtk_window_move(GTK_WINDOW(bookingsystem_page), 700, 150);
    gtk_window_move(GTK_WINDOW(user_reservations_page), 400, 150);
    gtk_window_move(GTK_WINDOW(user_cancel_reserv_page), 400, 150);
    gtk_window_move(GTK_WINDOW(admin_reservations_page), 400, 150);
    gtk_window_move(GTK_WINDOW(admin_cancel_reserv_page), 400, 150);
    // <---

    // set up the close 'x' buttons --->
    g_signal_connect(welcome_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(admin_authorization_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(user_authorization_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(user_login_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(admin_menu_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(user_menu_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(user_register_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(bookingsystem_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(user_reservations_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(user_cancel_reserv_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(admin_reservations_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(admin_cancel_reserv_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // <---

    gtk_builder_connect_signals(builder, NULL);

    // initialize the buttons --->
    // Welcome page btns
    user_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_btn"));
    admin_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_btn"));
    // Admin Auth page btns
    admin_login_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_login_btn"));
    admin_auth_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_auth_back_btn"));
    // User Auth page btns
    user_login_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_btn"));
    user_register_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_register_btn"));
    user_auth_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_auth_back_btn"));
    // User Login page btns
    user_login_in_login_page_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_in_login_page_btn"));
    user_login_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_back_btn"));
    // Admin Menu page btns
    admin_cancel_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_reservation_btn"));
    admin_show_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_show_reservation_btn"));
    admin_menu_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_menu_back_btn"));
    // User Menu page btns
    new_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "new_reservation_btn"));
    cancel_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_reservation_btn"));
    show_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "show_reservation_btn"));
    user_menu_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_menu_back_btn"));
    // User Register page btns
    user_register_in_register_page_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_register_in_register_page_btn"));
    user_register_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_register_back_btn"));
    // Booking System page btns
    apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "apply_btn"));
    booking_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "booking_back_btn"));
    // User Reservations page btns
    user_reservations_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_reservations_back_btn"));
    // User Reservations Cancel page btns
    user_cancel_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_reservation_btn"));
    user_cancel_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_back_btn"));
    // Admin Reservations page btns
    admin_reservations_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_reservations_back_btn"));
    // Admin Reservations Cancel page btns
    admin_cancel_reserv_by_id_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_reserv_by_id_btn"));
    admin_cancel_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_back_btn"));
    // <---

    // initialize the entries--->
    //  Admin Auth page entry
    admin_password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "admin_password_entry"));
    // User Login page entries
    user_loginusername_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_loginusername_entry"));
    user_loginpassword_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_loginpassword_entry"));
    // User Register page entries
    user_registerusername_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_registerusername_entry"));
    user_registerpassword_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_registerpassword_entry"));
    // Booking System page entries
    theme_entry = GTK_WIDGET(gtk_builder_get_object(builder, "theme_entry"));
    entertainment_entry = GTK_WIDGET(gtk_builder_get_object(builder, "entertainment_entry"));
    day_entry = GTK_WIDGET(gtk_builder_get_object(builder, "day_entry"));
    month_entry = GTK_WIDGET(gtk_builder_get_object(builder, "month_entry"));
    food_entry = GTK_WIDGET(gtk_builder_get_object(builder, "food_entry"));
    music_entry = GTK_WIDGET(gtk_builder_get_object(builder, "music_entry"));
    // User Reservations Cancel page entry
    user_cancel_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_entry"));
    // Admin Reservations Cancel page enty
    admin_cancel_entry = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_entry"));
    // <---

    // initialize the labels --->
    // User Authorization page label
    user_login_val_label = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_val_label"));
    // Admin Authorization page label
    admin_pas_val_label = GTK_WIDGET(gtk_builder_get_object(builder, "admin_pas_val_label"));
    // User Reservations page label
    user_reservations_content_label = GTK_WIDGET(gtk_builder_get_object(builder, "user_reservations_content_label"));
    // User Reservations Cancel page label
    user_cancel_content_label = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_content_label"));
    // Admin Reservations page label
    admin_reservations_content_label = GTK_WIDGET(gtk_builder_get_object(builder, "admin_reservations_content_label"));
    // Admin Reservations Cancel page label
    admin_cancel_content_label = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_content_label"));
    // <---
}

// Welcome Page functions --->
void on_user_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(welcome_page);
    gtk_widget_show(user_authorization_page);
}

void on_admin_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(welcome_page);
    gtk_widget_show(admin_authorization_page);
}
// <---

// Admin Authorization Page functions --->
void on_admin_login_btn_clicked(GtkButton *b)
{
    char password[20];
    sprintf(password, "%s", gtk_entry_get_text(GTK_ENTRY(admin_password_entry)));
    printf("password: %s\n", password);
    if (strcmp(password, "pass1234") == 0)
    {
        gtk_widget_hide(admin_authorization_page);
        gtk_widget_show(admin_menu_page);
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(admin_pas_val_label), (const gchar *)"Wrong password");
    }
}

void on_admin_auth_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(admin_authorization_page);
    gtk_widget_show(welcome_page);
}
// <---

// User Authorization Page functions --->
void on_user_login_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_authorization_page);
    gtk_widget_show(user_login_page);
}

void on_user_register_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_authorization_page);
    gtk_widget_show(user_register_page);
}

void on_user_auth_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_authorization_page);
    gtk_widget_show(welcome_page);
}
// <---

// User Login Page functions --->
void on_user_login_in_login_page_btn_clicked(GtkButton *b)
{
    char user_name[20];
    char password[20];
    char queryLoginValidate[100];
    sprintf(user_name, "%s", gtk_entry_get_text(GTK_ENTRY(user_loginusername_entry)));
    sprintf(password, "%s", gtk_entry_get_text(GTK_ENTRY(user_loginpassword_entry)));
    printf("user_name: %s\n", user_name);
    printf("password: %s\n", password);

    sprintf(queryLoginValidate, "queryLoginValidate/%s/%s/", user_name, password);
    printf("Query Login Validate: %s\n", queryLoginValidate);
    send(sock, queryLoginValidate, strlen(queryLoginValidate), 0);
    sleep(2);

    memset(buffer, 0, sizeof(buffer));
    valread = read(sock, buffer, 1024);
    printf("Buffer: %s\n", buffer);
    // int i = 0;
    if (strcmp("Wrong", buffer) == 0)
    {
        gtk_label_set_text(GTK_LABEL(user_login_val_label), (const gchar *)"Wrong password!!!");
    }
    else
    {
        // i++;
        strcpy(user_name_cookie, user_name);
        gtk_widget_hide(user_login_page);
        gtk_widget_show(user_menu_page);
    }
    memset(buffer, 0, sizeof(buffer));
}

void on_user_login_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_login_page);
    gtk_widget_show(user_authorization_page);
}
// <---

// Admin Menu Page --->
void on_admin_cancel_reservation_btn_clicked(GtkButton *b)
{
    char queryReservationsAll[100] = "queryReservationsAll/";
    send(sock, queryReservationsAll, strlen(queryReservationsAll), 0);
    sleep(2);

    memset(buffer, 0, sizeof(buffer));
    valread = read(sock, buffer, 1024);
    printf("Buffer: %s\n", buffer);

    gtk_label_set_text(GTK_LABEL(admin_cancel_content_label), buffer);
    gtk_widget_hide(admin_menu_page);
    gtk_widget_show(admin_cancel_reserv_page);
}

void on_admin_show_reservations_btn_clicked(GtkButton *b)
{
    char queryReservationsAll[100] = "queryReservationsAll/";
    send(sock, queryReservationsAll, strlen(queryReservationsAll), 0);
    sleep(2);

    memset(buffer, 0, sizeof(buffer));
    valread = read(sock, buffer, 1024);
    printf("Buffer: %s\n", buffer);

    gtk_label_set_text(GTK_LABEL(admin_reservations_content_label), buffer);
    gtk_widget_hide(admin_menu_page);
    gtk_widget_show(admin_reservations_page);
}

void on_admin_menu_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(admin_menu_page);
    gtk_widget_show(admin_authorization_page);
}
// <---

// User Menu Page --->
void on_new_reservation_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_menu_page);
    gtk_widget_show(bookingsystem_page);
}

void on_cancel_reservation_btn_clicked(GtkButton *b)
{
    char queryUserReservations[100];
    sprintf(queryUserReservations, "queryUserReservations/%s/", user_name_cookie);
    printf("Query User Reservations: %s\n", queryUserReservations);
    send(sock, queryUserReservations, strlen(queryUserReservations), 0);
    sleep(2);

    memset(buffer, 0, sizeof(buffer));
    valread = read(sock, buffer, 1024);
    printf("Buffer: %s\n", buffer);

    gtk_label_set_text(GTK_LABEL(user_cancel_content_label), buffer);
    gtk_widget_hide(user_menu_page);
    gtk_widget_show(user_cancel_reserv_page);
}

void on_show_reservations_btn_clicked(GtkButton *b)
{
    char queryUserReservations[500];
    sprintf(queryUserReservations, "queryUserReservations/%s/", user_name_cookie);
    printf("Query User Resservations: %s\n", queryUserReservations);
    send(sock, queryUserReservations, strlen(queryUserReservations), 0);
    sleep(2);

    memset(buffer, 0, sizeof(buffer));
    valread = read(sock, buffer, 1024);
    printf("Buffer: %s\n", buffer);

    gtk_label_set_text(GTK_LABEL(user_reservations_content_label), buffer);
    gtk_widget_hide(user_menu_page);
    gtk_widget_show(user_reservations_page);
    memset(buffer, 0, 1024);
}

void on_user_menu_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_menu_page);
    gtk_widget_show(user_login_page);
}
// <---

// User Register Page --->
void on_user_register_in_register_page_btn_clicked(GtkButton *b)
{
    char user_name[9];
    char password[9];
    char queryNewUser[100];
    sprintf(user_name, "%s", gtk_entry_get_text(GTK_ENTRY(user_registerusername_entry)));
    sprintf(password, "%s", gtk_entry_get_text(GTK_ENTRY(user_registerpassword_entry)));
    printf("user_name: %s\n", user_name);
    printf("password: %s\n", password);

    sprintf(queryNewUser, "queryNewUser/%s/%s/", user_name, password);
    printf("Query New User: %s\n", queryNewUser);
    send(sock, queryNewUser, strlen(queryNewUser), 0);

    gtk_widget_hide(user_register_page);
    gtk_widget_show(user_authorization_page);
}

void on_user_register_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_register_page);
    gtk_widget_show(user_authorization_page);
}
// <---

// Booking System Page --->
void on_apply_btn_clicked(GtkButton *b)
{
    char theme[32];
    char entertainment[32];
    char day[32];
    char month[32];
    char food[32];
    char music[32];
    memset(theme, 0, 32);
    memset(entertainment, 0, 32);
    memset(day, 0, 32);
    memset(month, 0, 32);
    memset(food, 0, 32);
    memset(music, 0, 32);

    sprintf(theme, "%s", gtk_entry_get_text(GTK_ENTRY(theme_entry)));
    sprintf(entertainment, "%s", gtk_entry_get_text(GTK_ENTRY(entertainment_entry)));
    sprintf(day, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(day_entry)));
    sprintf(month, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(month_entry)));
    sprintf(music, "%s", gtk_entry_get_text(GTK_ENTRY(music_entry)));
    sprintf(food, "%s", gtk_entry_get_text(GTK_ENTRY(food_entry)));
    printf("theme: %s\n", theme);
    printf("entertainment: %s\n", entertainment);
    printf("day: %s\n", day);
    printf("month: %s\n", month);
    printf("music: %s\n", music);
    printf("food: %s\n", food);

    char queryNewReservation[300];
    sprintf(queryNewReservation, "queryNewReservation/%s/%s/%s/%s/%s/%s/%s/", user_name_cookie, theme, entertainment, day, month, music, food);

    printf("Query New Reservation: %s\n", queryNewReservation);
    send(sock, queryNewReservation, strlen(queryNewReservation), 0);
    sleep(1);

    gtk_widget_hide(bookingsystem_page);
    gtk_widget_show(user_reservations_page);
}

void on_booking_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(bookingsystem_page);
    gtk_widget_show(user_menu_page);
}
// <---

// User Reservations Page --->
void on_user_reservations_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_reservations_page);
    gtk_widget_show(user_menu_page);
}
// <---

// User Reservations Cancel Page --->
void on_user_cancel_reservation_btn_clicked(GtkButton *b)
{
    char user_id[12];
    sprintf(user_id, "%s", gtk_entry_get_text(GTK_ENTRY(user_cancel_entry)));
    printf("user_id: %s\n", user_id);

    char queryUserCancelReserv[100];
    sprintf(queryUserCancelReserv, "queryUserCancelReserv/%s/", user_id);
    printf("Query User Cancel Reserv: %s\n", queryUserCancelReserv);
    send(sock, queryUserCancelReserv, strlen(queryUserCancelReserv), 0);
}

void on_user_cancel_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(user_cancel_reserv_page);
    gtk_widget_show(user_menu_page);
}
// <---

// Admin Reservations Page --->
void on_admin_reservations_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(admin_reservations_page);
    gtk_widget_show(admin_menu_page);
}
// <---

// Admin Reservations Cancel Page --->
void on_admin_cancel_back_btn_clicked(GtkButton *b)
{
    gtk_widget_hide(admin_cancel_reserv_page);
    gtk_widget_show(admin_menu_page);
}

void on_admin_cancel_reserv_by_id_btn_clicked(GtkButton *b)
{
    char reserv_id[10];
    sprintf(reserv_id, "%s", gtk_entry_get_text(GTK_ENTRY(admin_cancel_entry)));
    printf("%s\n", reserv_id);

    char queryUserCancelReserv[100];
    sprintf(queryUserCancelReserv, "queryUserCancelReserv/%s/", reserv_id);
    printf("Query User Cancel Reserv: %s\n", queryUserCancelReserv);
    send(sock, queryUserCancelReserv, strlen(queryUserCancelReserv), 0);
    sleep(2);

    gtk_widget_hide(admin_cancel_reserv_page);
    gtk_widget_show(admin_cancel_reserv_page);
}
// <---
