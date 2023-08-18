#include <openssl/sha.h>
void run_dig(const char *domain, char *param);
void traceroute(const char *domain);
void whois(const char *domain);
void get_ssl_expiration(const char *domain);
void get_http_status(const char *website);
void get_domain_expiration(const char *domain);
void whats_my_ip();
void dns_combo_cbk(GtkComboBox *combo_box, gpointer user_data);
void run_dns();
void clr_dns_sel();
void prnt_dns_sel();

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
}dns;

void run_dig(const char *domain, char *param)
{
sprintf(dns.command, "dig %s %s +short", param, domain);
system(dns.command);
}

void traceroute(const char *domain)
{
sprintf(dns.command, "traceroute %s", domain);
system(dns.command);
}

void whois(const char *domain)
{
sprintf(dns.command, "whois %s", domain);
system(dns.command);
}

void get_ssl_expiration(const char *domain)
{
sprintf(dns.command, "echo | openssl s_client -servername %s -connect %s:443 | openssl x509 -noout -dates", domain, domain);
system(dns.command);
}

void get_http_status(const char *website)
{
sprintf(dns.command, "curl -I %s 2>/dev/null | head -n 1", website);
system(dns.command);
}

void get_domain_expiration(const char *domain)
{
sprintf(dns.command, "whois %s | egrep -i 'Expiration Date:'", domain);
system(dns.command);
}

void whats_my_ip()
{
system("dig +short myip.opendns.com @resolver1.opendns.com");
}

void dns_combo_cbk(GtkComboBox *combo_box, gpointer user_data)
{
dns.selection = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box));
}