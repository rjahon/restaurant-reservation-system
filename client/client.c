#include "functions.h"

int main(int argc, char *argv[])
{
    initSocketConnection(); // initialize socket connection
    initGUI(&argc, &argv);  // initialize GUI

    gtk_widget_show(welcome_page); // display the welcome page
    gtk_main();

    return EXIT_SUCCESS;
}
