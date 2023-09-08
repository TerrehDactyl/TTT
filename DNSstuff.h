#include <openssl/sha.h>
#define AAAA 25765
#define NAMESERVER 2223184069
#define TXT 5749
#define MX 1098
#define IP 1070
#define SSL_EXP 278385825290
#define HTTP 27225
#define TRACEROUTE 2311043731
#define WHOIS 143923
#define MY_IP 11606961370
#define DOMAIN_EXP 33652116294040

struct dns_vars
{
	size_t scan_type_len;
	size_t btn_len;
	size_t entry_len;
	gchar command[256];
	gchar *selection;
	char buffer[256];
}dns;

void run_dig(const char *domain, char *param)
{
sprintf(dns.command, "dig %s %s +short", param, domain);
// system(dns.command);
}

void traceroute(const char *domain)
{
sprintf(dns.command, "traceroute %s", domain);
// system(dns.command);
}

void whois(const char *domain)
{
sprintf(dns.command, "whois %s", domain);
// system(dns.command);
}

void get_ssl_expiration(const char *domain)
{
sprintf(dns.command, "echo | openssl s_client -servername %s -connect %s:443 | openssl x509 -noout -dates", domain, domain);
// system(dns.command);
}

void get_http_status(const char *website)
{
sprintf(dns.command, "curl -I %s 2>/dev/null | head -n 1", website);
// system(dns.command);
}

void get_domain_expiration(const char *domain)
{
sprintf(dns.command, "whois %s | egrep -i 'Expiration Date:'", domain);
// system(dns.command);
}

void whats_my_ip()
{
sprintf(dns.command, "dig +short myip.opendns.com @resolver1.opendns.com");
// system("dig +short myip.opendns.com @resolver1.opendns.com");
}

void dns_combo_cbk(GtkComboBox *combo_box, gpointer user_data)
{
dns.selection = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box));
}

void run_dns()
{
    const gchar *dns_entries[dns.entry_len];
    get_entry_text(gwidget.dns_entries, dns_entries, dns.entry_len);
    const gchar *domain = dns_entries[0];
    FILE *fp;

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
    fp = popen(dns.command, "r");
    if(fp == NULL)
    {
    	perror("popen");
    	exit(EXIT_FAILURE);
    }

    while (fgets(dns.buffer, sizeof(dns.buffer), fp) != NULL) 
    {
        gtk_text_buffer_set_text (gwidget.buffer, dns.buffer, -1);
    }
}