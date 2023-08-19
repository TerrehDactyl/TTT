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
-subnet calculatord
-binary hex dec converter
-cable tester

modules to integrate
=====================
-raid calculator
-dns scanning
-pwcracking 
-traceroute
*/
void network_scanning();
void website_scanning();
void passwd_cracking();
void raid_calculator();
void pack_boxes(int i); // i may want to restructure this input for better readability
void run_raid();
void run_dns();
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

int main( int argc, char *argv[] )
{
    gtk_init (&argc, &argv);
    
    gwidget.window = create_window("TTOOLBOX", GTK_WIN_POS_CENTER, "test.png");
    gwidget.notebook = create_notebook(gwidget.window);

    network_scanning();
    website_scanning();
    passwd_cracking();
    raid_calculator();
    show_and_destroy(gwidget.window);
}

void network_scanning() //i need to reorder this function, it's still a wreck
{
    gchar *button_labels[] = {"Start Scan", "Cancel Scan"};
    void *button_callbacks[] = {start_scan, cancel_scan};
    gchar *entry_labels[] = {"Starting Port\n", "Ending Port\n", "Start IP\n", "End IP\n"};
    pscan.label_len = arraysize(entry_labels);  //do these really need to be 
    pscan.btn_len = arraysize(button_labels);   //part of the structure? 
    pscan.entry_len = arraysize(pscan.entries); // or can i make them local and save memory
    gwidget.label_grid = create_labels(entry_labels, pscan.label_len);
    gwidget.entry_grid = create_entries(pscan.entry_len,pscan.entries);
    gwidget.button_box = create_single_size_grid(button_labels, button_callbacks, NULL,1, pscan.btn_len);
    gwidget.nested_notebook = create_notebook(gwidget.notebook);
    gwidget.nested_frame = create_frame_with_pagehead(gwidget.nested_notebook, "Network Scanning");
    gwidget.child = gtk_notebook_get_nth_page (GTK_NOTEBOOK(gwidget.notebook), 0);
    gwidget.page_label = gtk_label_new("Network Scanning");                         
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(gwidget.notebook), gwidget.child, gwidget.page_label);
    GtkTextBuffer *buffer = gtk_text_buffer_new (NULL);
    gwidget.scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    const gchar *text = {"Prefilter multiple pictures Preprocess\n"};
    gtk_text_buffer_set_text (buffer, text, -1);
    gwidget.pscan_output = gtk_text_view_new_with_buffer (buffer);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (gwidget.pscan_output), GTK_WRAP_WORD); 
    gtk_text_view_set_editable(GTK_TEXT_VIEW(gwidget.pscan_output), FALSE);
    //gtk_widget_set_sensitive(GTK_WIDGET(gwidget.pscan_output),FALSE);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (gwidget.scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 
    gtk_container_add (GTK_CONTAINER (gwidget.scrolled_window), gwidget.pscan_output);
    pack_boxes(0);
}

void website_scanning()
{
    gchar *combo_labels[] = {"Name Server", "AAAA", "TXT", "MX", "IP", "SSL Expiration", "HTTP","Trace Route","WHOIS", "What's My IP","Domain Expiration"};
    gchar *button_labels[] = {"Run"};
    void *button_callbacks [] = {run_dns}; 
    dns.scan_type_len = arraysize(combo_labels);
    dns.btn_len = arraysize(button_labels);
    dns.entry_len = arraysize(gwidget.dns_entries);
    gwidget.button_box = create_single_size_grid(button_labels, button_callbacks, NULL,1, dns.btn_len);
    gwidget.entry_grid = create_entries(dns.entry_len,gwidget.dns_entries);
    gwidget.nested_notebook = create_notebook(gwidget.notebook);
    gwidget.child = gtk_notebook_get_nth_page (GTK_NOTEBOOK(gwidget.notebook), 1);
    gwidget.page_label = gtk_label_new("Website Scanning");                       
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(gwidget.notebook), gwidget.child, gwidget.page_label);
    gwidget.nested_frame = create_frame_with_pagehead(gwidget.nested_notebook, "Website Scanning");
    gwidget.combo_box = create_combobox(combo_labels,  dns.scan_type_len, dns_combo_cbk);
    GtkTextBuffer *buffer = gtk_text_buffer_new (NULL);//start of scrolled window function
    gwidget.scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    const gchar *text = {"Prefilter multiple pictures Preprocess\n"};
    gtk_text_buffer_set_text (buffer, text, -1);
    gwidget.dns_output = gtk_text_view_new_with_buffer (buffer);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (gwidget.dns_output), GTK_WRAP_WORD); 
    gtk_text_view_set_editable(GTK_TEXT_VIEW(gwidget.dns_output), FALSE);
    //gtk_widget_set_sensitive(GTK_WIDGET(gwidget.pscan_output),FALSE);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (gwidget.scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 
    gtk_container_add (GTK_CONTAINER (gwidget.scrolled_window), gwidget.dns_output); // end of scrolled window function
    pack_boxes(1);
}

void raid_calculator()
{
    gchar *combo_labels[] = {"0", "1", "5", "6", "10", "50", "60"};
    gchar *entry_labels[] = {"Type", "Disks", "Size", "Sets"};
    gchar *button_labels[] = {"Calculate"};
    raid.entry_len = arraysize(entry_labels); //do these really need to be 
    raid.btn_len = arraysize(button_labels);  //part of the structure? 
    raid.combo_len = arraysize(combo_labels); // or can i make them local and save memory
    void *button_callbacks[] = {run_raid};
    gwidget.label_grid = create_labels(entry_labels, raid.entry_len);
    gwidget.button_box = create_single_size_grid(button_labels, button_callbacks, NULL,1, raid.btn_len);
    gwidget.frame = create_frame_with_pagehead(gwidget.notebook, "Raid Calculator");
    gwidget.combo_box = create_combobox(combo_labels,  raid.combo_len, raid_type_cbk);
    gwidget.entry_grid = create_entries(raid.entry_len-1, gwidget.raid_entries);
    gwidget.display = create_text_display(TRUE, 50, 20);
    gwidget.buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW ( gwidget.display));
    pack_boxes(2);
}

void passwd_cracking()
{
    gchar *combo_labels[] ={"Brute Force", "Dictionary", "Rainbow Tables"};
    gchar *button_labels[] = {"Crack", "Cancel"};
    void *button_callbacks[] = {crack};
    pwcrack.combo_label_len = arraysize(combo_labels);
    pwcrack.btn_len = arraysize(button_labels);
    gwidget.button_box = create_single_size_grid(button_labels, button_callbacks, NULL,1, pwcrack.btn_len);
    gwidget.frame = create_frame_with_pagehead(gwidget.notebook, "Password Cracking");
    gwidget.combo_box = create_combobox(combo_labels,  pwcrack.combo_label_len, pwcrack_combo_cbk);
    pack_boxes(3);
}

void pack_boxes(int i)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1); //creates a vbox without autosizing 
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1); //creates a vbox without autosizing 

    switch(i)
    {
        case 0://network scanning 
        gtk_container_add(GTK_CONTAINER(gwidget.nested_frame), vbox);
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.label_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.entry_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.button_box, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.scrolled_window, FALSE, FALSE, 0); 
        break;

        case 1://website scanning
        gtk_container_add(GTK_CONTAINER(gwidget.nested_frame), vbox); 
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.entry_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.button_box, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(gwidget.combo_box), FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.scrolled_window, FALSE, FALSE, 0); 
        break;

        case 2://raid calculator
        gtk_container_add(GTK_CONTAINER(gwidget.frame), vbox); 
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.label_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.entry_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(gwidget.combo_box), FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(gwidget.button_box), FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(gwidget.display), FALSE, FALSE, 0); 
        break;

        case 3://password cracking
        gtk_container_add(GTK_CONTAINER(gwidget.frame), vbox);  
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(gwidget.combo_box), FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.button_box, FALSE, FALSE, 0); 
        break;
    }
}

void run_raid() //this whole functions is a lot of wtf, i'm sure i can do this like, WAY better.
{
    const gchar *ascii_entries[raid.entry_len];
    int int_entries[raid.entry_len]; //wtf
    get_entry_text(gwidget.raid_entries, ascii_entries, raid.entry_len);

    for(int i = 0; i < raid.entry_len-1; i++) // segfaults without this....wtf why?!?!
        int_entries[i] = atoi(ascii_entries[i]);

    if(&raid.type == NULL) //wtf this is dumb
        raid.type = 0;
    calculate_raid(raid.type, int_entries[0], int_entries[1], int_entries[2]);
    gtk_text_buffer_set_text ( gwidget.buffer, raid.buffer, -1); //displays input.num1 
}

void run_dns()
{
    const gchar *dns_entries[dns.entry_len];
    get_entry_text(gwidget.dns_entries, dns_entries, dns.entry_len);
    const gchar *domain = dns_entries[0];
    if(dns.selection == NULL)
        dns.selection = "Name Server";
    
    switch(hash(dns.selection))
    {
        case AAAA: run_dig(domain, "aaaa");
        break;
        case NAMESERVER: run_dig(domain, "NS");
        break;
        case TXT: run_dig(domain, "txt"); 
        break;
        case MX: run_dig(domain, "MX");
        break;
        case IP: run_dig(domain, "");
        break;
        case SSL_EXP: get_ssl_expiration(domain);
        break;
        case HTTP: get_http_status(domain);
        break;
        case TRACEROUTE: traceroute(domain);
        break;
        case WHOIS: whois(domain);
        break;
        case MY_IP: whats_my_ip();
        break;
        case DOMAIN_EXP: get_domain_expiration(domain);
        break;
    }
}
