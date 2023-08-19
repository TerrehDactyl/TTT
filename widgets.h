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
    GtkWidget *raid_entries[2];
    GtkComboBox *combo_box;
    GtkWidget *display;
    GtkTextBuffer *buffer;
    GtkWidget *pscan_output;
    GtkWidget *scrolled_window;
    GtkWidget *dns_output;
    GtkWidget *dns_entries[1];
    GtkWidget *entry_grid;
}gwidget;