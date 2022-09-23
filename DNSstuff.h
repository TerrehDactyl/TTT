void get_dns_records(char *domain);
void get_name_servers(char *domain);
void get_txt_records(char *domain);
void get_mx_records(char *domain);
void get_ip_address(char *domain);
void run_dig(char *domain, char *param);
void traceroute(char *domain);
void get_aaaa_records(char *domain);
void whois(char *domain);
void get_ssl_expiration(char *domain);
void get_http_status(char *website);
void get_domain_expiration(char *domain);
void whats_my_ip();
void dns_combo_cbk(GtkComboBox *combo_box, gpointer user_data);

struct dns_vars
{
	size_t scan_type_len;
}dns;

gchar *dns_scan_type[] = {"Name Server", "AAAA", "TXT", "MX", "IP", "SSL Expiration", "HTTP","Trace Route","WHOIS", "What's My IP","Domain Expiration"};

void get_name_servers(char *domain)
{
	run_dig(domain, "NS");
}

void get_aaaa_records(char *domain)
{
	run_dig(domain, "aaaa");
}

void get_txt_records(char *domain)
{
	run_dig(domain, "txt");	
}

void get_mx_records(char *domain)
{
	run_dig(domain, "MX");	
}

void get_ip_address(char *domain)
{
	run_dig(domain, "");
}

void run_dig(char *domain, char *param)
{
char command[50];
sprintf(command, "dig %s %s +short", param, domain);
system(command);
}

void traceroute(char *domain)
{
char command[50];
sprintf(command, "traceroute %s", domain);
system(command);
}

void whois(char *domain)
{
char command[50];
sprintf(command, "whois %s", domain);
system(command);
}

void get_ssl_expiration(char *domain)
{
char command [256];
sprintf(command, "echo | openssl s_client -servername %s -connect %s:443 | openssl x509 -noout -dates", domain, domain);
system(command);
}

void get_http_status(char *website)
{
char command [256];
sprintf(command, "curl -I %s 2>/dev/null | head -n 1", website);
system(command);
}

void get_domain_expiration(char *domain)
{
char command[50];
sprintf(command, "whois %s | egrep -i 'Expiration Date:'", domain);
system(command);
}

void whats_my_ip()
{
system("dig +short myip.opendns.com @resolver1.opendns.com");
}

void dns_combo_cbk(GtkComboBox *combo_box, gpointer user_data)
{
	if (gtk_combo_box_get_active (combo_box) != 0) 
	{
		gchar *selection = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo_box));
		if(strcmp(selection, "first label") == 0)
		{
			g_print("you selected the first label");
		}
		else if(strcmp(selection, "second label") == 0)
		{
			g_print("you selected the second label");
		}
		else if(strcmp(selection, "third label") == 0)
		{
			g_print("you selected the third label");
		}
	}
}