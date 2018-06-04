#include <gtk/gtk.h>

GtkImage *purple;
GtkImage *red;
GtkImage *yellow;
GtkImage *blue;

int main(int argc, char *argv[])
{
    GtkWidget       *window;
    GtkBuilder      *builder;
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    red = GTK_IMAGE(gtk_builder_get_object(builder, "redHorse"));
    purple = GTK_IMAGE(gtk_builder_get_object(builder, "purpleHorse"));
    yellow = GTK_IMAGE(gtk_builder_get_object(builder, "yellowHorse"));
    blue = GTK_IMAGE(gtk_builder_get_object(builder, "blueHorse"));

    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}
 
 static const gchar *get_image_path_from_name(const gchar *name)
{
        gint length;
        gchar *path;

        static const gchar *path_default = "glade/";

        static gint path_default_length = 26;

        length = path_default_length + strlen(name) + 1;
        path   = g_malloc(sizeof(char) * length);

        strcpy(path, path_default);
        strcat(path, name);

        return path;
}

void on_button_clicked(GtkButton *button, GtkImage *image)
{
    g_print("%s",gtk_button_get_label(button));
    const gchar *path;
    path  = get_image_path_from_name("avatarHorse.png");
    gtk_image_set_from_file(image, path);
}

void on_reset_clicked(GtkButton *button)
{
    const gchar *redpath;
    redpath  = get_image_path_from_name("redHorse.png");
    gtk_image_set_from_file(red, redpath);

    const gchar *purplepath;
    purplepath  = get_image_path_from_name("purpleHorse.png");
    gtk_image_set_from_file(purple, purplepath);

    const gchar *yellowpath;
    yellowpath  = get_image_path_from_name("yellowHorse.png");
    gtk_image_set_from_file(yellow, yellowpath);
    
    const gchar *bluepath;
    bluepath  = get_image_path_from_name("blueHorse.png");
    gtk_image_set_from_file(blue, bluepath);
}
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}