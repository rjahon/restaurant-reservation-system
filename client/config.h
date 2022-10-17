#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 4444

// Session cookies
char user_name_cookie[20] = "";

int sock = 0;
int valread;
struct sockaddr_in serv_addr;
struct sockaddr_in address;
char buffer[1024] = {0};

GtkBuilder *builder;

GtkWidget *welcome_page;
GtkWidget *user_btn;
GtkWidget *admin_btn;

GtkWidget *admin_authorization_page;
GtkWidget *admin_pas_val_label;
GtkWidget *admin_password_entry;
GtkWidget *admin_login_btn;
GtkWidget *admin_auth_back_btn;

GtkWidget *user_authorization_page;
GtkWidget *user_login_val_label;
GtkWidget *user_login_btn;
GtkWidget *user_register_btn;
GtkWidget *user_auth_back_btn;

GtkWidget *user_login_page;
GtkWidget *user_loginusername_entry;
GtkWidget *user_loginpassword_entry;
GtkWidget *user_login_in_login_page_btn;
GtkWidget *user_login_back_btn;

GtkWidget *admin_menu_page;
GtkWidget *admin_cancel_reservation_btn;
GtkWidget *admin_show_reservation_btn;
GtkWidget *admin_menu_back_btn;

GtkWidget *user_menu_page;
GtkWidget *new_reservation_btn;
GtkWidget *cancel_reservation_btn;
GtkWidget *show_reservation_btn;
GtkWidget *user_menu_back_btn;

GtkWidget *user_register_page;
GtkWidget *user_registerusername_entry;
GtkWidget *user_registerpassword_entry;
GtkWidget *user_register_in_register_page_btn;
GtkWidget *user_register_back_btn;

GtkWidget *user_reservations_page;
GtkWidget *user_reservations_content_label;
GtkWidget *user_reservations_back_btn;

GtkWidget *user_cancel_reserv_page;
GtkWidget *user_cancel_content_label;
GtkWidget *user_cancel_entry;
GtkWidget *user_cancel_reservation_btn;
GtkWidget *user_cancel_back_btn;

GtkWidget *admin_reservations_page;
GtkWidget *admin_reservations_content_label;
GtkWidget *admin_reservations_back_btn;

GtkWidget *admin_cancel_reserv_page;
GtkWidget *admin_cancel_content_label;
GtkWidget *admin_cancel_entry;
GtkWidget *admin_cancel_reserv_by_id_btn;
GtkWidget *admin_cancel_back_btn;

GtkWidget *bookingsystem_page;
GtkWidget *theme_entry;
GtkWidget *entertainment_entry;
GtkWidget *day_entry;
GtkWidget *month_entry;
GtkWidget *food_entry;
GtkWidget *music_entry;
GtkWidget *apply_btn;
GtkWidget *booking_back_btn;
