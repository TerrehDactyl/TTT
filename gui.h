void pack_boxes(int i)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1); //creates a vbox without autosizing 
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1); //creates a hbox without autosizing 

    switch(i)
    {
        case 0://network scanning 
        gtk_container_add(GTK_CONTAINER(gwidget.nested_frame), vbox);
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.label_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.entry_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.button_box, FALSE, FALSE, 0); 
        break;

        case 1://website scanning
        gtk_container_add(GTK_CONTAINER(gwidget.frame), vbox); 
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.entry_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.button_box, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(gwidget.combo_box), FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.dns_display, FALSE, FALSE, 0); 
        break;

        case 2://raid calculator
        GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1); //boxes inside of boxes
        gtk_container_add(GTK_CONTAINER(gwidget.frame), vbox); 
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), gwidget.label_grid, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), right_vbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(right_vbox), GTK_WIDGET(gwidget.combo_box), FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(right_vbox), gwidget.entry_grid, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.button_box, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.raid_display, FALSE, FALSE, 0); 
        break;

        case 3://password cracking
        gtk_container_add(GTK_CONTAINER(gwidget.frame), vbox);  
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(gwidget.combo_box), FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.button_box, FALSE, FALSE, 0); 
        gtk_box_pack_start(GTK_BOX(vbox), gwidget.pwcrack_display, FALSE, FALSE, 0); 
        break;
    }
}

void network_scanning() //i need to reorder this function, it's still a wreck
{
    gchar *button_labels[] = {"Start Scan", "Cancel Scan"};
    gchar *entry_labels[] = {"Starting Port\n", "Ending Port\n", "Start IP\n", "End IP\n"};
    gwidget.page_label = gtk_label_new("Network Scanning");  
    pscan.label_len = arraysize(entry_labels);  //do these really need to be 
    pscan.btn_len = arraysize(button_labels);   //part of the structure? 
    pscan.entry_len = arraysize(pscan.entries); // or can i make them local and save memory
    void *button_callbacks[] = {start_scan, cancel_scan};
    gwidget.label_grid = create_labels(entry_labels, pscan.label_len);
    gwidget.entry_grid = create_entries(pscan.entry_len,pscan.entries);
    gwidget.button_box = create_single_size_grid(button_labels, button_callbacks, NULL,1, pscan.btn_len);
    gwidget.nested_notebook = create_notebook(gwidget.notebook);
    gwidget.nested_frame = create_frame_with_pagehead(gwidget.nested_notebook, "Network Scanning");
    gwidget.child = gtk_notebook_get_nth_page (GTK_NOTEBOOK(gwidget.notebook), 0);                       
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(gwidget.notebook), gwidget.child, gwidget.page_label);
    pack_boxes(0);
}

void website_scanning()
{
    gchar *combo_labels[] = {"Name Server", "AAAA", "TXT", "MX", "IP", "SSL Expiration", "HTTP","Trace Route","WHOIS", "What's My IP","Domain Expiration"};
    gchar *button_labels[] = {"Run"};
    gwidget.page_label = gtk_label_new("Website Scanning");   
    void *button_callbacks [] = {run_dns}; 
    dns.scan_type_len = arraysize(combo_labels);
    dns.btn_len = arraysize(button_labels);
    dns.entry_len = arraysize(gwidget.dns_entries);
    gwidget.button_box = create_single_size_grid(button_labels, button_callbacks, NULL,1, dns.btn_len);
    gwidget.entry_grid = create_entries(dns.entry_len,gwidget.dns_entries);
    gwidget.frame = create_frame_with_pagehead(gwidget.notebook, "Website Scanning");
    gwidget.combo_box = create_combobox(combo_labels,  dns.scan_type_len, dns_combo_cbk);
    gwidget.dns_display = create_text_display(TRUE, 50, 20);
    gwidget.dns_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (gwidget.dns_display));
    pack_boxes(1);
}

void raid_calculator()
{
    gchar *combo_labels[] = {"0", "1", "5", "6", "10", "50", "60"};
    gchar *entry_labels[] = {"Type\n", "Disks\n", "Size (TB)\n", "Sets\n"};
    gchar *button_labels[] = {"Calculate"};
    gwidget.frame = create_frame_with_pagehead(gwidget.notebook, "Raid Calculator");
    raid.entry_len = arraysize(entry_labels); //this is -1 because type is technically a combobox label
    raid.btn_len = arraysize(button_labels);
    raid.combo_len = arraysize(combo_labels);
    void *button_callbacks[] = {run_raid};
    gwidget.label_grid = create_labels(entry_labels, raid.entry_len);
    gwidget.button_box = create_single_size_grid(button_labels, button_callbacks, NULL,1, raid.btn_len);
    gwidget.combo_box = create_combobox(combo_labels, raid.combo_len, raid_type_cbk); // why no work? 
    gwidget.entry_grid = create_entries(raid.entry_len-1, gwidget.raid_entries);
    gwidget.raid_display = create_text_display(TRUE, 50, 20);
    gwidget.raid_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (gwidget.raid_display));
    pack_boxes(2);
}

void passwd_cracking()
{
    gchar *combo_labels[] = {"Brute Force", "Dictionary", "Rainbow Tables"};
    gchar *button_labels[] = {"Crack", "Cancel"};
    gwidget.frame = create_frame_with_pagehead(gwidget.notebook, "Password Cracking");
    void *button_callbacks[] = {crack};
    pwcrack.combo_label_len = arraysize(combo_labels);
    pwcrack.btn_len = arraysize(button_labels);
    gwidget.button_box = create_single_size_grid(button_labels, button_callbacks, NULL, 1, pwcrack.btn_len);
    gwidget.combo_box = create_combobox(combo_labels,  pwcrack.combo_label_len, pwcrack_combo_cbk);
    gwidget.pwcrack_display = create_text_display(TRUE, 50, 20);
    gwidget.pwcrack_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (gwidget.pwcrack_display));
    pack_boxes(3);
}