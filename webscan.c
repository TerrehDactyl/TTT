#include<stdio.h>
#include <stdlib.h>
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
int main()
{
get_dns_records("google.com");
//traceroute("www.google.com");
}

void get_dns_records(char *domain)
{
char *website = "www.google.com";
//get_name_servers(domain);
//get_txt_records(domain);
//get_mx_records(domain);
//get_ip_address(domain);
//get_aaaa_records(domain);
//whois(domain);
//get_ssl_expiration(domain);
//get_http_status(website);
//whats_my_ip();
get_domain_expiration(domain);
}

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