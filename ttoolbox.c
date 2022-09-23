#include "gtktemplate.h"
#include "portscan.h"
#include "pwcrack.h"
#include "DNSstuff.h"
#include "raid.h"
/*
Figure out an elegant way of doing nested notebook pages.
modules to write
=================
-Network Enumeration/fingerprinting - use nmap.
-scraping/subdomains
-subnet calculator
-binary hex dec converter
-cable tester

modules to integrate
=====================
-raid calculator
-dns scanning
-pwcracking 
-traceroute
*/
void packboxes(int i);
//void createnotebookpage(int i, gchar *buttonlabels[], void *buttoncallbacks[], 
//                        size_t butt_size, gchar *chooserlabels[], void *choosercallbacks, 
//                        location *data, size_t chooserarr_size, gchar *labeltext[]);
void create_root_notebook_pages(GtkWidget *notebook, gchar *pageheads[]);
struct widgets
{
    GtkWidget *window;
    GtkWidget *notebook;
    GtkWidget *frame;
    GtkWidget *pscan_entries[4];
    GtkWidget *labelgrid;
    GtkWidget *buttonbox;
    GtkWidget *pscan_entry_grid;
    GtkWidget *nested_notebook;
    GtkWidget *nested_frame;
    GtkComboBox *pwcrack_combo;
    GtkWidget *page_label;
    GtkWidget *child;
    GtkComboBox *raid_type_combo;
    GtkWidget *raid_entry_grid;
    GtkWidget *raid_entries[3];
    GtkComboBox *dns_combo;
}gwidget;

gchar *pageheads[] = {"Network Scanning", "Website Scanning", "Password Cracking", "Raid Calculator"};
gchar *nested_pageheads[] = {"Port Scan", "Protocol Analyzer", "Network Enumeration/Fingerprinting", "Raid Calculator"};
size_t nested_len = arraysize(nested_pageheads);
size_t pagehead_len = arraysize(pageheads);
int main( int argc, char *argv[] )
{
    gtk_init (&argc, &argv);
    
    gwidget.window = createwindow("TTOOLBOX", GTK_WIN_POS_CENTER, "test.png");
    gwidget.notebook = createnotebook(gwidget.window);
    pscan.label_len = arraysize(pscan_labels);
    pscan.btn_len = arraysize(pscan_btn_labels);
    pwcrack.combo_label_len = arraysize(pwcrack_combo_labels);
    raid.type_label_len = arraysize(raid_type_labels);
    raid.entry_len = arraysize(raid_entries);
    dns.scan_type_len = arraysize(dns_scan_type);

  //  for(int i = 0; i < pagehead_len; i++)
   //     create_frame_with_pagehead(notebook, pageheads[i]); 
    //create_root_notebook_pages(gwidget.notebook, pageheads);
    createnotebookpage(0, pscan_btn_labels, pscan_btn_cbks, pscan.btn_len, NULL, NULL, NULL, pscan.label_len, pscan_labels);
    createnotebookpage(1, NULL, NULL, 0, NULL, NULL, NULL, 0, NULL);
    createnotebookpage(2, NULL, NULL, 0, NULL, NULL, NULL, 0, NULL);
    createnotebookpage(3, NULL, NULL, 0, NULL, NULL, NULL, raid.entry_len, raid_entries);
    createnotebookpage(4, NULL, NULL, 0, NULL, NULL, NULL, 0, NULL);

    show_and_destroy(gwidget.window);
}
/*
void create_root_notebook_pages(GtkWidget *notebook, gchar *pageheads[])
{
    GtkWidget *frame;
    for(int i = 0; i < pagehead_len; i++)
    {
        frame = create_frame_with_pagehead(notebook, pageheads[i]);
        populate_notebook_pages(frame, pageheads[i]);
    }
}
void populate_notebook_pages(GtkWidget *frame, gchar *pagehead)
{
    
}

*/
void createnotebookpage(int i, gchar *buttonlabels[], void *buttoncallbacks[], 
                        size_t butt_size, gchar *chooserlabels[], void *choosercallbacks, 
                        location *data, size_t chooserarr_size, gchar *labeltext[])
{
    gwidget.labelgrid = createlabels(labeltext, chooserarr_size);
    gwidget.buttonbox = createsinglesizegrid(buttonlabels, buttoncallbacks, data,1, butt_size);
    switch(i)
    {
        case 0:
        gwidget.pscan_entry_grid = create_entries(pscan.label_len, gwidget.pscan_entries);
        gwidget.nested_notebook = createnotebook(gwidget.notebook);
        gwidget.nested_frame = create_frame_with_pagehead(gwidget.nested_notebook, pageheads[i]);
        gwidget.child = gtk_notebook_get_nth_page (GTK_NOTEBOOK(gwidget.notebook), 0);
        gwidget.page_label = gtk_label_new("Network Scanning");                         
        gtk_notebook_set_tab_label(GTK_NOTEBOOK(gwidget.notebook), gwidget.child, gwidget.page_label);
        packboxes(i);
        break;

        case 1: 
        gwidget.nested_notebook = createnotebook(gwidget.notebook);
        gwidget.child = gtk_notebook_get_nth_page (GTK_NOTEBOOK(gwidget.notebook), 1);
        gwidget.page_label = gtk_label_new("Website Scanning");                       
        gtk_notebook_set_tab_label(GTK_NOTEBOOK(gwidget.notebook), gwidget.child, gwidget.page_label);
        gwidget.nested_frame = create_frame_with_pagehead(gwidget.nested_notebook, pageheads[i]);
        gwidget.dns_combo = create_combobox(dns_scan_type,  dns.scan_type_len, dns_combo_cbk);
        packboxes(i);
        break;

        case 2:
        gwidget.frame = create_frame_with_pagehead(gwidget.notebook, pageheads[i]);
        gwidget.pwcrack_combo = create_combobox(pwcrack_combo_labels,  pwcrack.combo_label_len, pwcrack_combo_cbk);
        packboxes(i);
        break;

        case 3:
        gwidget.frame = create_frame_with_pagehead(gwidget.notebook, pageheads[i]);
        gwidget.raid_type_combo = create_combobox(raid_type_labels,  raid.type_label_len, raid_type_cbk);
        gwidget.raid_entry_grid = create_entries(raid.entry_len-1, gwidget.raid_entries);
        packboxes(i);
    }
}

void packboxes(int i)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1); //creates a vbox without autosizing 
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1); //creates a vbox without autosizing 

    switch(i)
    {
        case 0:
        gtk_container_add(GTK_CONTAINER(gwidget.nested_frame), vbox);
        gtk_box_pack_start(GTK_BOX(vbox),  hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox),  gwidget.labelgrid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox),  gwidget.pscan_entry_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox),  gwidget.buttonbox, FALSE, FALSE, 0); 
        break;

        case 1:
        gtk_container_add(GTK_CONTAINER(gwidget.nested_frame), vbox); 
        gtk_box_pack_start(GTK_BOX(vbox),  hbox, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox),  GTK_WIDGET(gwidget.dns_combo), FALSE, FALSE, 0); 
        break;

        case 2:
        gtk_container_add(GTK_CONTAINER(gwidget.frame), vbox);  
        gtk_box_pack_start(GTK_BOX(vbox),  hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox),  GTK_WIDGET(gwidget.pwcrack_combo), FALSE, FALSE, 0); 
        break;

        case 3:
        gtk_container_add(GTK_CONTAINER(gwidget.frame), vbox); 
        gtk_box_pack_start(GTK_BOX(vbox),  hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox),  gwidget.labelgrid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox),  gwidget.raid_entry_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox),  GTK_WIDGET(gwidget.raid_type_combo), FALSE, FALSE, 0); 
        break;
    }
}