#include "gtktemplate.h"
struct widgets
{
    GtkWidget *window;
    GtkWidget *notebook;
    GtkWidget *frame;
    GtkWidget *label_grid;
    GtkWidget *button_box;
    GtkWidget *nested_notebook;
    GtkWidget *nested_frame;
    GtkWidget *page_label;
    GtkWidget *child;
    GtkWidget *raid_entries[4];
    GtkComboBox *combo_box;
    GtkWidget *display;
    GtkWidget *raid_display;
    GtkWidget *dns_display;
    GtkTextBuffer *raid_buffer;
    GtkTextBuffer *dns_buffer;
    GtkTextBuffer *buffer;
    GtkWidget *pscan_output;
    GtkWidget *scrolled_window;
    GtkWidget *dns_output;
    GtkWidget *dns_entries[1];
    GtkWidget *entry_grid;
}gwidget;