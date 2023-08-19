#include "widgets.h"
#include "portscan.h"
#include "pwcrack.h"
#include "DNSstuff.h"
#include "raid.h"
#include "gui.h"
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

int main( int argc, char *argv[])
{                                
    gtk_init (&argc, &argv);   
    
    gwidget.window = create_window("TTOOLBOX", GTK_WIN_POS_CENTER, "test.png");
    gwidget.notebook = create_notebook(gwidget.window);

    network_scanning();
    website_scanning();
    raid_calculator();
    passwd_cracking();
    show_and_destroy(gwidget.window);
}
