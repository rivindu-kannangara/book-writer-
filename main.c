#include <gtk/gtk.h>

static void button_clicked(GtkWidget *widget, gpointer data)
{
    GtkLabel *label = GTK_LABEL(data);
    gtk_label_set_text(label, "Hello! Your C GUI is working.");
}

static void activate(GtkApplication *app, gpointer data)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "My first GTK APP");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_margin_top(box, 50);
    gtk_widget_set_margin_start(box, 30);
    gtk_widget_set_margin_end(box, 30);

    label = gtk_label_new("Welcome to my application");

    button = gtk_button_new_with_label("Click Me");

    g_signal_connect(button, "clicked",
                     G_CALLBACK(button_clicked), label);

    gtk_box_append(GTK_BOX(box), label);
    gtk_box_append(GTK_BOX(box), button);

    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new(
        "com.example.myapp",
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
