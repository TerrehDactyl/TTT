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
void network_scanning(gchar *buttonlabels[], void *buttoncallbacks[], gchar *labeltext[]);
void website_scanning();
void passwd_cracking();
void raid_calculator();
void packboxes(int i);
void calc_raid();
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
    GtkWidget *raid_entries[2];
    GtkComboBox *dns_combo;
}gwidget;

int main( int argc, char *argv[] )
{
    gtk_init (&argc, &argv);
    
    gwidget.window = createwindow("TTOOLBOX", GTK_WIN_POS_CENTER, "test.png");
    gwidget.notebook = createnotebook(gwidget.window);

    network_scanning(pscan_btn_labels,pscan_btn_cbks, pscan_labels);
    website_scanning();
    passwd_cracking();
    raid_calculator();

    show_and_destroy(gwidget.window);
}

void network_scanning(gchar *buttonlabels[], void *buttoncallbacks[], gchar *labeltext[])
{
    pscan.label_len = arraysize(pscan_labels);
    pscan.btn_len = arraysize(pscan_btn_labels);
    gwidget.labelgrid = createlabels(labeltext, pscan.label_len);
    gwidget.buttonbox = createsinglesizegrid(buttonlabels, buttoncallbacks, NULL,1, pscan.btn_len);
    gwidget.pscan_entry_grid = create_entries(pscan.label_len, gwidget.pscan_entries);
    gwidget.nested_notebook = createnotebook(gwidget.notebook);
    gwidget.nested_frame = create_frame_with_pagehead(gwidget.nested_notebook, "Network Scanning");
    gwidget.child = gtk_notebook_get_nth_page (GTK_NOTEBOOK(gwidget.notebook), 0);
    gwidget.page_label = gtk_label_new("Network Scanning");                         
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(gwidget.notebook), gwidget.child, gwidget.page_label);
    packboxes(0);
}

void website_scanning()
{
    dns.scan_type_len = arraysize(dns_scan_type);
    gwidget.nested_notebook = createnotebook(gwidget.notebook);
    gwidget.child = gtk_notebook_get_nth_page (GTK_NOTEBOOK(gwidget.notebook), 1);
    gwidget.page_label = gtk_label_new("Website Scanning");                       
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(gwidget.notebook), gwidget.child, gwidget.page_label);
    gwidget.nested_frame = create_frame_with_pagehead(gwidget.nested_notebook, "Website Scanning");
    gwidget.dns_combo = create_combobox(dns_scan_type,  dns.scan_type_len, dns_combo_cbk);
    packboxes(1);
}

void passwd_cracking()
{
    pwcrack.combo_label_len = arraysize(pwcrack_combo_labels);
    gwidget.frame = create_frame_with_pagehead(gwidget.notebook, "Password Cracking");
    gwidget.pwcrack_combo = create_combobox(pwcrack_combo_labels,  pwcrack.combo_label_len, pwcrack_combo_cbk);
    packboxes(2);
}

void raid_calculator()
{
    gchar *buttonlabels[] = {"Calculate"};
    raid.btn_len = arraysize(buttonlabels); 
    raid.type_label_len = arraysize(raid_type_labels);
    raid.entry_len = arraysize(raid_entries);
    void *raid_calc_cbk[] = {calc_raid};
    gwidget.buttonbox = createsinglesizegrid(buttonlabels, raid_calc_cbk, NULL,1, raid.btn_len);
    gwidget.frame = create_frame_with_pagehead(gwidget.notebook, "Raid Calculator");
    gwidget.raid_type_combo = create_combobox(raid_type_labels,  raid.type_label_len, raid_type_cbk);
    gwidget.raid_entry_grid = create_entries(raid.entry_len-1, gwidget.raid_entries);
    packboxes(3);
}

void calc_raid()
{
    const gchar *ascii_entries[raid.entry_len];
    int int_entries[raid.entry_len];
    get_entry_text(gwidget.raid_entries, ascii_entries, raid.entry_len);
    for(int i = 0; i < raid.entry_len-1; i++)
    {
        int_entries[i] = atoi(ascii_entries[i]);
        printf("%d\n", int_entries[i]);
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
        gtk_box_pack_start(GTK_BOX(vbox),  GTK_WIDGET(gwidget.buttonbox), FALSE, FALSE, 0); 
        break;
    }
}